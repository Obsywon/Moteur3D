#include "Node.h"

Node::Node(const float x, const float y, const float z): _x{x}, _y{y}, _z{z}{

}

Node::~Node(){}


void Node::resize(const int width, const int height){
    int w = width / 2;
    int h = height / 2;
    _x = (_x * w) + w;
    _y = (_y * h) + h;
}

float Node::getX(){
    return _x;
}

float Node::getY(){
    return _y;
}

float Node::getZ(){
    return _z;
}

std::ostream& operator <<(std::ostream &s, const Node& node){
    return s << "(" << node._x << ", " << node._y << ", " << node._z << ") " << std::endl;
}