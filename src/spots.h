#include "main.h"

#ifndef SPOTS_H
#define SPOTS_H


class Spots {
public:
    Spots() {}
    Spots(float x, float y, float z, color_t color);
    glm::vec3 position;
    float in_rad, out_rad,height;
    float alpha;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object2;
};

#endif // SPOTS_H
