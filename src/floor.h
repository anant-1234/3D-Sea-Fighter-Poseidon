#include "main.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floor {
public:
    Floor() {}
    Floor(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void anticlockwise();
    void clockwise();
    void left();
    void right();
private:
    VAO *object;
    VAO *object2;
};

#endif // FLOOR_H
