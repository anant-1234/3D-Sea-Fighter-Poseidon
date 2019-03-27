#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z, color_t color);
    glm::vec3 position;
    float in_rad, out_rad,height;
    float alpha;
    float rotation;
    void draw(glm::mat4 VP, float value);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // COMPASS_H
