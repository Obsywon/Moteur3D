#include "Parser.h"



const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);


const TGAColor randomize_color (std::uniform_int_distribution<int> &distr, 
std::default_random_engine &engine){
    return TGAColor(distr(engine), distr(engine), distr(engine), 255);
}


int main(int argc, char** argv) {

    //double z_buffer[HEIGHT * WIDTH] = {-std::numeric_limits<double>::max()};

    double *z_buffer = new double[WIDTH*HEIGHT];
    for (int i=WIDTH*HEIGHT; i--; z_buffer[i] = -std::numeric_limits<double>::max());

    Parser parser("./obj/african_head/african_head.obj", WIDTH, HEIGHT);

    // Générateur aléatoire de couleur
    /*
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distr(0, 255);
    */


    std::vector <Face> faces = parser.getFaces();

	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);


    for (Face &face: faces){
        face.draw_triangle(image, green, z_buffer);
        //face.draw_line_triangle(image, green);
    }

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	return 0;
}

