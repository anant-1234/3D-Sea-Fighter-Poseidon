#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float rotation_prop;
    int scale_fact;
    float mv_speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void anticlockwise();
    void clockwise();
    void left();
    void right();
    void move_fwd();
    void move_backward();
    void ascend();
    void descend();
    void loop();
    void roll();
    double width,out_rad,speed,in_rad,wing_rad;
private:
    VAO *object;
    VAO *object2;
};


#endif // BALL_H
