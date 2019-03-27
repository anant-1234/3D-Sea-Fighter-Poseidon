#include "main.h"

#ifndef FUELBAR_H
#define FUELBAR_H


class FuelBar {
public:
    FuelBar() {}
    FuelBar(float x, float y, float z, color_t color);
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
};

#endif // FUELBAR_H
