#include "main.h"

#ifndef RINGS_H
#define RINGS_H


class Rings {
public:
    Rings() {}
    Rings(float x, float y, float z, color_t color);
    glm::vec3 position;
    float in_rad, out_rad;
    float height;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // RINGS_H
