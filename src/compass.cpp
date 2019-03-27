#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->alpha = 0;
    GLfloat vertex_buffer_data[10008],vertex_buffer_data2[108],vertex_buffer_data3[109];
    int k=0,k1=0,k2=0;
    double n=100;
    in_rad = 1.0f;
    out_rad = 1.1f;
    height = 0;
    for(double i=0;i<=360;i+=360/n)
    {
        vertex_buffer_data[k++]=in_rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=in_rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=out_rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=out_rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        // Triangle 2
        vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=out_rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=out_rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=out_rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=out_rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=-height;
        // Knob
    }
    for(double i=0;i<360;i+=360/n)
    {
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=0.1f*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=0.1f*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=0.1f*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=0.1f*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=-height;
    }
    vertex_buffer_data2[k1++]=0.1f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=-0.1f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.9f;
    vertex_buffer_data2[k1++]=0.0f;
    // 
    vertex_buffer_data3[k2++]=0.1f;
    vertex_buffer_data3[k2++]=0.0f;
    vertex_buffer_data3[k2++]=0.0f;
    vertex_buffer_data3[k2++]=-0.1f;
    vertex_buffer_data3[k2++]=0.0f;
    vertex_buffer_data3[k2++]=0.0f;
    vertex_buffer_data3[k2++]=0.0f;
    vertex_buffer_data3[k2++]=-0.9f;
    vertex_buffer_data3[k2++]=0.0f;
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_ORANGE, GL_FILL);    
    this->object2 = create3DObject(GL_TRIANGLES, k1/3, vertex_buffer_data2, COLOR_RED, GL_FILL);    
    this->object3 = create3DObject(GL_TRIANGLES, k2/3, vertex_buffer_data3, COLOR_DBLUE, GL_FILL);    
}



void Compass::draw(glm::mat4 VP, float value) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate  = glm::rotate((float) (value * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);
    Matrices.model *= rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    Matrices.model = translate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick() {
    
}

