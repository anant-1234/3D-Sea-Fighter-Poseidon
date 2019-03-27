#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color, float speed_y);
    glm::vec3 position;
    float rad;
    float height;
    float rotation;
    float speed_y;
    float alpha;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object2;
};

#endif // PARACHUTE_H
