#include "main.h"

#ifndef BULLETS_H
#define BULLETS_H


class Bullets {
public:
    Bullets() {}
    Bullets(float x, float y, float z, color_t color,float angle);
    glm::vec3 position;
    float in_rad;
    float height;
    float trajectory;
    float init_theta;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // BULLETS_H
