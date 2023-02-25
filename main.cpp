#include "Parser.h"

constexpr int HEIGHT{1000};
constexpr int WIDTH{1000};

const double dist_z = 10.;
const Vecteur camera = {1., 1., 3.};
const Vecteur center = {0., 0., 0.};
const Vecteur haut = {0., 1., 0.};
Vecteur light_dir = {0., 0., 1.};
Matrix modelview = Matrix::generateModelview(camera, center, haut);
Matrix viewport = Matrix::generateViewport(WIDTH / 8, HEIGHT / 8, WIDTH * 3 / 4, HEIGHT * 3 / 4);
Matrix projection = Matrix::generateProjection(camera, center);

/**
 * @brief Interface définissant les shader
 * 
 */
struct IShader
{
    /**
     * @brief Transformation à appliquer à un triangle
     * 
     * @param v vertex modifiable
     * @param indice indice
     */
    virtual void vertex(Vertex &v, int indice) = 0;

    /**
     * @brief Rastérisation d'un pixel
     * 
     * @param normal Valeur normale au pixel
     * @param color Couleur de la texture à appliquer au pixel
     * @param baryo Valeurs baryocentriques
     * @return false pour coloriser le pixel
     */
    virtual bool fragment(TGAColor &normal, TGAColor &color, Vecteur &baryo) = 0;
};

struct GouraudShader : public IShader
{
    Vecteur varying_intensity;

    void vertex(Vertex &v, int indice) override
    {
        Vecteur temp = v.toVecteur();
        Matrix gl_Vertex = Matrix(temp);

        Vecteur prod = Vecteur::produitCroix(temp, light_dir);
        varying_intensity[indice] = std::max(0., Vecteur::norm(prod));
        Matrix result = viewport * projection * modelview * gl_Vertex;
        Vecteur res = result.matrixToVector();
        v = Vertex(res);
    }

    bool fragment(TGAColor &normal, TGAColor &color, Vecteur &baryo) override
    {
        Vecteur norm, rgb, light;
        norm.x = normal.r * 2. / 255. - 1.;
        norm.y = normal.g * 2. / 255. - 1.;
        norm.z = normal.b * 2. / 255. - 1.;
        norm = Vecteur::normalize(norm);
        light = Vecteur::normalize(light_dir);

        // float intensity = Vecteur::norm(light_dir);

        rgb.x = color.r;
        rgb.y = color.g;
        rgb.z = color.b;

        double diffuse = std::min(1., std::max(0., rgb * norm) / 255.);
        // diffuse *= (intensity * baryo.x + intensity * baryo.y + intensity * baryo.z);
        color.r *= diffuse;
        color.g *= diffuse;
        color.b *= diffuse;
        return false;
    }
};


/**
 * @brief Gère les entrées utilisateurs
 * 
 * @param argc Nombre d'arguments reçus par le programme
 * @param argv Tableau d'arguments
 * @param base_path Chemin de base non nul
 * @param diffuse_path Chemin de la texture
 * @param normal_path Chemin vers la texture normalisée
 */
void userInput(int argc, char **argv, std::string &base_path, std::string &diffuse_path, std::string &normal_path)
{
    const std::string diffuse_path_modifier = "_diffuse.tga";
    const std::string normal_path_modifier = "_nm.tga";

    if (argc == 2)
    {
        base_path = argv[1];
        std::cout << "Chemin vers fichier .obj fourni: " << base_path << std::endl;
    }
    else
    {
        std::cout << "Chemin vers cible manquant. Par défaut, sera utilisé: " << base_path << std::endl;
        std::cout << "Pour afficher une image, veuillez fournir le chemin vers le fichier .obj correspondant." << std::endl;
    }

    int dot = base_path.find_last_of('.');
    diffuse_path = base_path.substr(0, dot) + diffuse_path_modifier;
    normal_path = base_path.substr(0, dot) + normal_path_modifier;
}

int main(int argc, char **argv)
{

    // Gestion des entrées de l'utilisateur
    std::string base_path = "../obj/african_head/african_head.obj";
    std::string diffuse_path = "";
    std::string normal_path = "";

    userInput(argc, argv, base_path, diffuse_path, normal_path);


    // Initialisation du z buffer (gestion de la profondeur)
    double *z_buffer = new double[WIDTH * HEIGHT];
    for (int i = WIDTH * HEIGHT; i--; z_buffer[i] = -std::numeric_limits<double>::max())
        ;

    // Initialisation des textures et normales
    TGAImage texture = TGAImage();
    texture.read_tga_file(diffuse_path.c_str());
    texture.flip_vertically();

    TGAImage normal_map = TGAImage();
    normal_map.read_tga_file(normal_path.c_str());
    normal_map.flip_vertically();

    // Parsage + redimension de texture
    Parser parser(base_path, texture);
    std::vector<Face> faces = parser.getFaces();
    // Initialisaiton du shader et de la structure de l'image à remplir
    GouraudShader shader;
    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

    for (Face &face : faces)
    {

        // Déformation de chaque triangles
        for (int i = 0; i < 3; i++)
            shader.vertex(face.getVertex(i), i);

        // Chargement du rectangle à remplir
        std::array<int, 4> box = face.load_bounding_box();

        // Structure contenant les coef baryocentriques + bazyo de z
        std::array<double, 4> baryo;

        double intensity = face.color_intensity(light_dir);
        TGAColor color;

        // Remplir le rectangle
        for (int x = box[0]; x <= box[2]; x++)
        {
            for (int y = box[1]; y <= box[3]; y++)
            {
                // Evite de traiter des pixels hors de l'image
                if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
                    continue;


                // Récupération des coefs pour interpoler la couleur d'un pixel dans le triangle (la face)
                baryo = face.baryocentric_values(x, y);
                int indice = int(x + y * WIDTH);

                // Teste si un pixel doit être colorié
                if (!(baryo[0] > -0.0001 && baryo[1] > -0.0001 && baryo[2] > -0.0001))
                    continue;
                if (z_buffer[indice] < baryo[3])
                {
                    // calcul z-index pour choisir ce que le pixel doit représenter
                    z_buffer[indice] = baryo[3];

                    TGAColor color = face.getColor(texture, baryo);
                    TGAColor normal = face.getColor(normal_map, baryo);
                    Vecteur bar;
                    bar.x = baryo[0];
                    bar.y = baryo[1];
                    bar.z = baryo[2];


                    bool discard = shader.fragment(normal, color, bar);

                    if (!discard)
                    {
                        image.set(x, y, color);
                    }
                }
            }
        }
    }

    image.flip_vertically();
    image.write_tga_file("../output.tga");

    return 0;
}
