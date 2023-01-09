#include "Parser.h"


const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);


constexpr int HEIGHT {500};
constexpr int WIDTH {500};







int main(int argc, char** argv) {
    Parser parser("./obj/african_head/african_head.obj", WIDTH, HEIGHT);
    
    std::vector<Vertex> vertices = parser.getVertexes();
    std::vector <Face> faces = parser.getFaces();

	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);


    for (Face &face: faces){
        face.draw_line_triangle(image, blue);
        face.draw_triangle(image, green);
    }

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

