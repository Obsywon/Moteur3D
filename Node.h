#ifndef __NODE_H__
#define __NODE_H__


#include <iostream>


class Node
{
private:
    float _x;
    float _y;
    float _z;

    friend std::ostream& operator <<(std::ostream &s, const Node& node);
    
public:
    
    Node(const float x, const float y, const float z);
    ~Node();

    float getX();
    float getY();
    float getZ();

    void resize(const int width, const int height);
};






#endif //__NODE_H__