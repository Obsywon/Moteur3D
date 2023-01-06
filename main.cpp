#include "Parser.h"


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

constexpr int HEIGHT = 500;
constexpr int WIDTH = 500;




void line (int x0, int x1, int y0, int y1, TGAImage &img, TGAColor color){
	bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t; 
        if (steep) { 
            img.set(y, x, color); // if transposed, de−transpose 
        } else { 
            img.set(x, y, color); 
        } 
    }  
}


int main(int argc, char** argv) {
    Parser parser("./obj/african_head/african_head.obj");
    std::vector<Vertex> vertices = parser.buildVertexes(WIDTH, HEIGHT);

    std::vector <Face> faces = parser.buildFaces(vertices);

	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
    for (Vertex &vertex: vertices){
        image.set(vertex.getX(), vertex.getY(), red);
    }

    for (Face &face: faces){
        face.draw_triangle(image, red);
    }
	//image.set(52, 41, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

