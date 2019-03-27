#include "fuelbar.h"
#include "main.h"

FuelBar::FuelBar(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->alpha = 0;
    GLfloat vertex_buffer_data[10008],vertex_buffer_data2[108];
    int k=0,k1=0;
    double n=100;
    in_rad = 1.0f;
    out_rad = 1.1f;
    height = 0;
    for(double i=0;i<=180-3.6;i+=360/n)
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
    vertex_buffer_data2[k1++]=0.05f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=-0.05f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.0f;
    vertex_buffer_data2[k1++]=0.9f;
    vertex_buffer_data2[k1++]=0.0f;
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_PBLACK, GL_FILL);    
    this->object2 = create3DObject(GL_TRIANGLES, k1/3, vertex_buffer_data2, COLOR_PRED, GL_FILL);    
}



void FuelBar::draw(glm::mat4 VP, float value) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate  = glm::rotate((float) (value * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model *= rotate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void FuelBar::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void FuelBar::tick() {
    
}

