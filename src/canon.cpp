#include "canon.h"
#include "main.h"

Canon::Canon(float x, float y, float z,float angle, float speed_x, float speed_y, float speed_z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0 ;
    this->trajectory = 0;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
    this->speed_z = speed_z;
    this->init_theta = angle;
    height = 0.1f;
    in_rad = 0.05f;
    GLfloat vertex_buffer_data[100008];
    int k=0;

    double n=100;
    for(double i=0;i<360;i+=360/n)
    {   
        // Base 
    	vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=in_rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=in_rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
        // Triangles
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=height;
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=in_rad*cos((M_PI*i)/180);
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=in_rad*sin((M_PI*i)/180);
        vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
        vertex_buffer_data[k++]=0.0f;
        vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
    }
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_PYELLOW, GL_FILL);    

}



void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate  = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate2  = glm::rotate((float) (this->init_theta * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate2 * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Canon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Canon::tick() {
    this->position.x += 0.01*this->speed_x;
    this->position.y += 0.01*this->speed_y;
    this->position.z += 0.01*this->speed_z;
}

