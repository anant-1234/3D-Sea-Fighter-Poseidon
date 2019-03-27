#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(double x, double y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP,float trans_x,float trans_y, float rot_f);
    void set_position(double x, double y);
    void tick();
private:
    VAO *object;
};

#endif // SCORE_H
