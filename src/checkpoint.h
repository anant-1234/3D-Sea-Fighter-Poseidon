#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float active;
    float rad, height;
    float rotate_x, rotate_y, rotate_z;
    void draw(glm::mat4 VP, double beta, double gamma, int flag);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // CHECKPOINT_H
