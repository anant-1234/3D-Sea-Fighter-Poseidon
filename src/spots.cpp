#include "spots.h"
#include "main.h"

Spots::Spots(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->alpha = 0;
    GLfloat vertex_buffer_data[10008],vertex_buffer_data2[108];
    int k=0,k1=0;
    double n=100;
    in_rad = 0.3f;
    height = 0;
    for(double i=0;i<=360;i+=360/n)
    {
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++]=in_rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=in_rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
    }
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_SKY, GL_FILL);    
}



void Spots::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Spots::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Spots::tick() {
    
}

