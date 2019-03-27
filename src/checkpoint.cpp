#include "checkpoint.h"
#include "main.h"
#define dim 0.7f
using namespace std;

Checkpoint::Checkpoint(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    int k = 0, k1 = 0;
    rad = 0.1f;
    height = 0.6f;
    this->rotate_x = 0;
    this->rotate_y = 0;
    this->rotate_z = 0;
    GLfloat vertex_buffer_data[108], vertex_buffer_data2[10008];
    vertex_buffer_data[k++] = dim;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = dim;
    vertex_buffer_data[k++] = dim;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -dim;
    vertex_buffer_data[k++] = -dim;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -dim;
    vertex_buffer_data[k++] = dim;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = dim;
    vertex_buffer_data[k++] = -dim;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -dim;
    vertex_buffer_data[k++] = -dim;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = dim;
    //  Cylindrical Canon
    double n = 100;
    for(double i=0;i<360;i+=3.6)
    {
        // Circle 1
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data2[k1++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*sin(M_PI*((i+360/n)/180));
        // Circle 2
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=height;
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data2[k1++]=height;
        vertex_buffer_data2[k1++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data2[k1++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=height;
        vertex_buffer_data2[k1++]=rad*sin(M_PI*((i+360/n)/180));
        // Triangle 1
        vertex_buffer_data2[k1++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data2[k1++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data2[k1++]=height;
        vertex_buffer_data2[k1++]=rad*sin((M_PI*i)/180);
        // Triangle 2
        vertex_buffer_data2[k1++]=rad*cos((M_PI*i)/180);
        vertex_buffer_data2[k1++]=height;
        vertex_buffer_data2[k1++]=rad*sin((M_PI*i)/180);
        vertex_buffer_data2[k1++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=height;
        vertex_buffer_data2[k1++]=rad*sin(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data2[k1++]=0.0f;
        vertex_buffer_data2[k1++]=rad*sin(M_PI*((i+360/n)/180));
    }
    this->object = create3DObject(GL_TRIANGLES, k/3 , vertex_buffer_data, {153, 0, 153}, GL_FILL);    
    this->object2 = create3DObject(GL_TRIANGLES, k1/3 , vertex_buffer_data2, COLOR_PBLACK, GL_FILL);  
    this->object3 = create3DObject(GL_TRIANGLES, k1/3 , vertex_buffer_data2, COLOR_ORANGE, GL_FILL);  
}

void Checkpoint::draw(glm::mat4 VP, double beta, double gamma,int flag) {
    
    Matrices.model = glm::mat4(1.0f);
    float alpha = M_PI/2;
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate  = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotate1  = glm::rotate((float) (alpha), glm::vec3(1, 0, 0));
    // glm::mat4 rotate2  = glm::rotate((float) (gamma), glm::vec3(0, 1, 0));
    // glm::mat4 rotate3  = glm::rotate((float) (beta), glm::vec3(0, 0, 1));

    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    if(flag)
    {
        glm::mat4 rotate1  = glm::rotate((float) (45.0 * M_PI / 180.0f), glm::vec3(1, 0, 0));
        glm::mat4 rotate2  = glm::rotate((float) (this->active * M_PI / 180.0f), glm::vec3(0, 1, 0));
        Matrices.model *= (rotate2 * rotate1);
        MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object3);
    }
}

void Checkpoint::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Checkpoint::tick() {
    this->active += 3;
}

