#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x1, float z1, float x2, float z2, float rot);
    void anticlockwise();
    void clockwise();
    void left();
    void right();
private:
    VAO *object;
    VAO *object2;
};

#endif // ARROW_H
