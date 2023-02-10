#include "Parser.h"
#include "Model.h"

const TGAColor VERT = TGAColor(0, 255, 0, 255);


int main(int argc, char** argv) {

    const double dist_z = 10.;
    const Vecteur eyeCenter = {1., 1., 3.};
    const Vecteur center = {0., 0., 0.};
    const Vecteur haut = {0., 1., 0.};




    double *z_buffer = new double[WIDTH*HEIGHT];
    for (int i=WIDTH*HEIGHT; i--; z_buffer[i] = -std::numeric_limits<double>::max());

    TGAImage texture = TGAImage();
    texture.read_tga_file("./obj/african_head/african_head_diffuse.tga");
    texture.flip_vertically();

    
    Parser parser("./obj/african_head/african_head.obj", WIDTH, HEIGHT, texture);
    Model model = Model();

    model.generateModelview(eyeCenter, center, haut);
    model.generateViewport(WIDTH/8, HEIGHT/8, WIDTH*3/4, HEIGHT*3/4);
    model.generateProjection(eyeCenter, center);
    std::vector <Face> faces = parser.getFaces();

	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);


    for (Face &face: faces){
        model.transform(face);
        face.draw_triangle(image, z_buffer, texture);
    }

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	return 0;
}

