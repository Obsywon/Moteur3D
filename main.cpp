#include "Parser.h"

const TGAColor VERT = TGAColor(0, 255, 0, 255);

constexpr int HEIGHT{1000};
constexpr int WIDTH{1000};

const double dist_z = 10.;
const Vecteur camera = {1., 1., 3.};
const Vecteur center = {0., 0., 0.};
const Vecteur haut = {0., 1., 0.};
const Vecteur light_dir = {1., 1., 1.};

struct IShader
{
    virtual void vertex(Matrix &viewport, Matrix &projection, Matrix &modelview, Face &face, int indice) = 0;
    virtual bool fragment(Vecteur bar, TGAColor &color) = 0;
};

struct GouraudShader : public IShader
{
    Vecteur varying_intensity; // written by vertex shader, read by fragment shader

    void vertex(Matrix &viewport, Matrix &projection, Matrix &modelview, Face &face, int indice) override
    {
        Vertex v = face.getVertex(indice);
        Matrix gl_Vertex = v.toVecteur();

        NormalVector nv = face.getNormal(indice);
        Vecteur normal = {nv.getX(), nv.getY(), nv.getZ()};
        float normalized_light = Vecteur::normalize(normal) * light_dir;
        varying_intensity.x = std::max(0.f, normalized_light); // get diffuse lighting intensity
        Matrix result = viewport * projection * modelview * gl_Vertex; 
        Vecteur res = result.matrixToVector();
        v = Vertex(res);
        face.setVertex(v, indice);
        
    }

    bool fragment(Vecteur bar, TGAColor &color) override
    {
        float intensity = varying_intensity * bar; // interpolate intensity for the current pixel
        color = TGAColor(255 * intensity, 255 * intensity, 255 * intensity, 255); // well duh
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

    auto modelview = Matrix::generateModelview(camera, center, haut);
    auto viewport = Matrix::generateViewport(WIDTH / 8, HEIGHT / 8, WIDTH * 3 / 4, HEIGHT * 3 / 4);
    auto projection = Matrix::generateProjection(camera, center);
    std::vector<Face> faces = parser.getFaces();

    GouraudShader shader;

    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

    for (Face &face : faces)
    {

        // face.transform(viewport, modelview, projection);
        for (int i = 0; i < 3; i++)
            shader.vertex(viewport, projection, modelview, face, i);

        std::array<int, 4> box = face.load_bounding_box();
        std::array<double, 4> baryo = {0};
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
                if (baryo[0] > -0.0001 && baryo[1] > -0.0001 && baryo[2] > -0.0001)
                {

                    if (z_buffer[indice] < baryo[3])
                    {
                        // calcul z-index pour choisir ce que le pixel doit représenter
                        z_buffer[indice] = baryo[3];

                        TGAColor color = face.getColor(texture, baryo);
                        /* color = TGAColor(255, 255, 255, 255); */
                        // coloration du pixel
                        if (intensity > 0)
                            image.set(x, y, TGAColor(color.r * intensity, color.g * intensity, color.b * intensity, color.a));
                    }
                }
            }
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");

    return 0;
}
