#include "arrow.h"
#include "main.h"
using namespace std;
Arrow::Arrow(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat vertex_buffer_data[10008];
    int k = 0;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = -0.4f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.2f;
    vertex_buffer_data[k++] = -0.4f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.2f;
    vertex_buffer_data[k++] = -0.4f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.2f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    // Triangle
    vertex_buffer_data[k++] = 0.4f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.4f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.6f;
    vertex_buffer_data[k++] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_PRED, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);    
}
    
void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object2);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick(float x1, float z1, float x2, float z2, float rot) {
    double theta = atan((z2-z1)/(x2-x1))*(180.00/M_PI);
    rot = -rot;
    // cerr << z2 << " z2 " << z1 << " z1" << endl; 
    if(z2 >= z1)
    {
        if(theta >= 0)
            this->rotation = rot - 90 + theta;
        else
            this->rotation = rot + 90 + theta;
    }
    else
    {
        if(theta >= 0)
            this->rotation = rot + theta + 90;
        else
            this->rotation = rot + theta - 90;
    }
}

