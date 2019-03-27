#include "main.h"
#include "score.h"

using namespace std;
Score::Score(double x, double y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data[]={
        0.1f, 0.025f, 0.0f,
        0.1f, -0.025f, 0.0f,
        -0.1f, -0.025f, 0.0f,
        -0.1f, -0.025f, 0.0f,
        -0.1f, 0.025f, 0.0f,
        0.1f, 0.025f, 0.0f,
    }; 
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Score::draw(glm::mat4 VP,float trans_x, float trans_y, float rot_f) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate2 = glm::translate (glm::vec3(trans_x, trans_y, 0)); 
    glm::mat4 rotate    = glm::rotate((float) (rot_f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate2 * translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Score::set_position(double x, double y) {
    this->position = glm::vec3(x, y, 0);
}

