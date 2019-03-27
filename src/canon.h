#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y, float z, float angle, float speed_x, float speed_y, float speed_z);
    glm::vec3 position;
    float in_rad;
    float height;
    float trajectory;
    float init_theta;
    float rotation;
    float speed_x, speed_y, speed_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // CANON_H
