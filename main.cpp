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

struct IShader
{
    virtual void vertex(Vertex &v, int indice) = 0;
    virtual bool fragment(Vecteur bar, TGAColor &color) = 0;
};

struct GouraudShader : public IShader
{
    Vecteur varying_intensity;


    void vertex(Vertex &v, int indice) override
    {
        Vecteur temp = v.toVecteur();
        Matrix gl_Vertex = Matrix(temp);
        Vecteur prod = Vecteur::produitCroix(temp, light_dir);
        varying_intensity[indice] = std::max(0.,Vecteur::norm(prod));
        Matrix result = viewport * projection * modelview * gl_Vertex;
        Vecteur res = result.matrixToVector();
        v = Vertex(res);
    }

    bool fragment(Vecteur norm, TGAColor &color) override
    {
        double diffuse = varying_intensity * norm;
        std::cout << diffuse << std::endl;
        color = TGAColor(color.r * diffuse, color.g * diffuse, color.b * diffuse, 255); // well duh
        return false;
    }
};

int main(int argc, char **argv)
{

    double *z_buffer = new double[WIDTH * HEIGHT];
    for (int i = WIDTH * HEIGHT; i--; z_buffer[i] = -std::numeric_limits<double>::max())
        ;

    TGAImage texture = TGAImage();
    texture.read_tga_file("./obj/african_head/african_head_diffuse.tga");
    texture.flip_vertically();

    Parser parser("./obj/african_head/african_head.obj", WIDTH, HEIGHT, texture);

  

    std::vector<Face> faces = parser.getFaces();

    GouraudShader shader;

    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

    for (Face &face : faces)
    {

        // face.transform(viewport, modelview, projection);
        for (int i = 0; i < 3; i++)
            shader.vertex(face.getVertex(i), i);

        std::array<int, 4> box = face.load_bounding_box();
        std::array<double, 4> baryo;
        Vecteur light_source = {0, 0, -1.};
        double intensity = face.color_intensity(light_source);
        TGAColor color;

        // Remplir le rectangle
        for (int x = box[0]; x <= box[2]; x++)
        {
            for (int y = box[1]; y <= box[3]; y++)
            {
                // Evite de traiter des pixels hors de l'image
                if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
                    continue;

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
                    Vecteur norm;
                    norm.x = color.r * 2. / 255. -1.;
                    norm.y = color.g * 2. / 255. -1.;
                    norm.z = color.b * 2. / 255. -1.;

                    norm.x = baryo[0];
                    norm.y = baryo[1];
                    norm.z = baryo[2];

                    

                    bool discard = shader.fragment(norm, color);
                    if (!discard)
                    {
                        image.set(x, y, color);
                    }

                }
            }
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");

    return 0;
}
