#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z, color_t color, float speed_y) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 45.0f;
    this->alpha = 0.0f;
    this->speed_y = speed_y;
    height = 0.05f;
    rad = 0.4f;
    GLfloat vertex_buffer_data[10008], vertex_buffer_data2[10004];
    int k = 0,k1 = 0;
    double n=100;
    for(double i=0;i<90;i+=360/n)
    {
        // Triangle - 1
    	vertex_buffer_data[k++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=height;
        vertex_buffer_data[k++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=height;
        // Triangle - 2
        vertex_buffer_data[k++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=height;
        vertex_buffer_data[k++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=-height;
        vertex_buffer_data[k++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=-height;
    }
    for(double i=0;i<360;i+=360/n)
    {
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=0.05*cos((M_PI*i)/180);
        vertex_buffer_data2[k1++]=0.05*sin((M_PI*i)/180);
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=0.05*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=0.05*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_PBLACK, GL_FILL);    
    this->object2 = create3DObject(GL_TRIANGLES, k1/3, vertex_buffer_data2, COLOR_PBLACK , GL_FILL);    
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate  = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    glm::mat4 rotate2  = glm::rotate((float) (this->alpha * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= rotate2;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    this->alpha += 1;
    if(this->position.y <= -1.0f)
    {
        this->speed_y *= -1;
        this->position.y = -0.99f;
    }    
    if(this->position.y >= 1.0f)
    {
        this->speed_y *= -1;
        this->position.y = 0.99f;
    }
    this->position.y -= this->speed_y;
}

