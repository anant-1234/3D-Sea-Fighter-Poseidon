#include "ball.h"
#include "main.h"

using namespace std;

Ball::Ball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation_x = 0;
    this->rotation_y = 0;
    this->rotation_z = 0;
    this->mv_speed = 0;
    this->rotation_prop = 0;
    scale_fact = 3;
    width = 1.0f/4;
    out_rad = 0.45f/4;
    wing_rad = 0.6f/4;
    in_rad = out_rad;
    speed = 0.5;
    GLfloat vertex_buffer_data[100008];
    GLfloat color_buffer_data[100008];
    int k=0,k1=0;
    double n=100;
    for(double i=0;i<360;i+=360/n)
    {
    	// Circle-1
	   	vertex_buffer_data[k++]=0.0f;
	   	vertex_buffer_data[k++]=0.0f;
	   	vertex_buffer_data[k++]=width;
	   	vertex_buffer_data[k++]=in_rad*cos((M_PI*i)/180);
	   	vertex_buffer_data[k++]=in_rad*sin((M_PI*i)/180);
	   	vertex_buffer_data[k++]=width;
	   	vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=width;
	   	// Color
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	// Circle-2
	   	vertex_buffer_data[k++]=0.0f;
	   	vertex_buffer_data[k++]=0.0f;
	   	vertex_buffer_data[k++]=-width;
	   	vertex_buffer_data[k++]=out_rad*cos((M_PI*i)/180);
	   	vertex_buffer_data[k++]=out_rad*sin((M_PI*i)/180);
	   	vertex_buffer_data[k++]=-width;
	   	vertex_buffer_data[k++]=out_rad*cos(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=out_rad*sin(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=-width;
	   	// Color
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	// Cone 
	   	vertex_buffer_data[k++]=out_rad*cos((M_PI*i)/180);
	   	vertex_buffer_data[k++]=out_rad*sin((M_PI*i)/180);
	   	vertex_buffer_data[k++]=-width;
	   	vertex_buffer_data[k++]=out_rad*cos(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=out_rad*sin(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=-width;
	   	vertex_buffer_data[k++]=0;
	   	vertex_buffer_data[k++]=0;
	   	vertex_buffer_data[k++]=-scale_fact*width;
	   	// Color
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	// Triangle-1
	   	vertex_buffer_data[k++]=in_rad*cos((M_PI*i)/180);
	   	vertex_buffer_data[k++]=in_rad*sin((M_PI*i)/180);
	   	vertex_buffer_data[k++]=width;
	   	vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=width;
	   	vertex_buffer_data[k++]=out_rad*cos((M_PI*i)/180);
	   	vertex_buffer_data[k++]=out_rad*sin((M_PI*i)/180);
	   	vertex_buffer_data[k++]=-width;
	   	// Color
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	// Triangle-2
	   	vertex_buffer_data[k++]=out_rad*cos((M_PI*i)/180);
	   	vertex_buffer_data[k++]=out_rad*sin((M_PI*i)/180);
	   	vertex_buffer_data[k++]=-width;
	   	vertex_buffer_data[k++]=out_rad*cos(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=out_rad*sin(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=-width;
	   	vertex_buffer_data[k++]=in_rad*cos(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=in_rad*sin(M_PI*((i+360/n)/180));
	   	vertex_buffer_data[k++]=width;
	   	// Color
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.99f;
	   	color_buffer_data[k1++]=0.0f;
	   	color_buffer_data[k1++]=0.0f;
    }
    GLfloat vertex_buffer_data2[10008];
    GLfloat color_buffer_data2[10008];
    int k2 = 0,k3 = 0;
    for(float i=0;i<90;i+=360/n)
    {
    	vertex_buffer_data2[k2++]=0.0f;
    	vertex_buffer_data2[k2++]=0.0f;
    	vertex_buffer_data2[k2++]=-scale_fact*width;
    	vertex_buffer_data2[k2++]=wing_rad*cos((M_PI*i)/180);
    	vertex_buffer_data2[k2++]=wing_rad*sin((M_PI*i)/180);
    	vertex_buffer_data2[k2++]=-scale_fact*width;
    	vertex_buffer_data2[k2++]=wing_rad*cos(M_PI*((i+360/n)/180));
    	vertex_buffer_data2[k2++]=wing_rad*sin(M_PI*((i+360/n)/180));
    	vertex_buffer_data2[k2++]=-scale_fact*width;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.99f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.99f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.99f;
    	color_buffer_data2[k3++]=0.0f;
    }
    for(float i=180;i<270;i+=360/n)
    {
    	vertex_buffer_data2[k2++]=0.0f;
    	vertex_buffer_data2[k2++]=0.0f;
    	vertex_buffer_data2[k2++]=-scale_fact*width;
    	vertex_buffer_data2[k2++]=wing_rad*cos((M_PI*i)/180);
    	vertex_buffer_data2[k2++]=wing_rad*sin((M_PI*i)/180);
    	vertex_buffer_data2[k2++]=-scale_fact*width;
    	vertex_buffer_data2[k2++]=wing_rad*cos(M_PI*((i+360/n)/180));
    	vertex_buffer_data2[k2++]=wing_rad*sin(M_PI*((i+360/n)/180));
    	vertex_buffer_data2[k2++]=-scale_fact*width;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.99f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.99f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.0f;
    	color_buffer_data2[k3++]=0.99f;
    	color_buffer_data2[k3++]=0.0f;
    }
    // Right Flap
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=width/2;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=-width/2;
    vertex_buffer_data[k++]=2*width;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    // Left Flap
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=width/2;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=-width/2;
    vertex_buffer_data[k++]=-2*width;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    // Top Flap
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=width/16;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=0.0f;
    vertex_buffer_data[k++]=width;
    vertex_buffer_data[k++]=0.1f;
    vertex_buffer_data[k++]=2*in_rad;
    vertex_buffer_data[k++]=0.75*width;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.0f;
    color_buffer_data[k1++]=0.99f;
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, color_buffer_data, GL_FILL);    
    this->object2 = create3DObject(GL_TRIANGLES, k2/3, vertex_buffer_data2, color_buffer_data2, GL_FILL);    
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x  = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y  = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z  = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_prop  = glm::rotate((float) (this->rotation_prop * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate_x * rotate_y * rotate_z);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model *= rotate_prop;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Ball::clockwise() {
    this->rotation_z += 1;
}
void Ball::anticlockwise() {
    this->rotation_z -= 1;
}
void Ball::left() {
    this->rotation_y += 1;
    // this->rotation_z += 1;
}
void Ball::right() {
    this->rotation_y -= 1;
    // this->rotation_z -= 1;
}
void Ball::move_fwd() {
    // float theta = this->rotation_y * M_PI / 180.0f;
    // // printf("%f\n",theta);
    // this->position.z -= 0.03*cos(theta);
    // this->position.x -= 0.03*sin(theta);
    this->mv_speed += 0.001;
}
void Ball::move_backward() {
    // float theta = this->rotation_y * M_PI / 180.0f;
    // // printf("%f\n",theta);
    // this->position.z += 0.01*cos(theta);
    // this->position.x += 0.01*sin(theta);
    this->mv_speed -= 0.001;
}
void Ball::ascend() {
    this->position.y += 0.01;
}
void Ball::descend() {
    this->position.y -= 0.01;
}
void Ball::tick() {
    float theta = this->rotation_y * M_PI / 180.0f;
    // printf("%f\n",theta);
    this->position.z -= this->mv_speed*cos(theta);
    this->position.x -= this->mv_speed*sin(theta);
    this->rotation_prop += 10;

}

void Ball::loop() {
    this->rotation_x += 1;
    float theta = this->rotation_x * M_PI / 180.0f;
    this->position.z -= 0.05 * cos(theta);
    this->position.y += 0.05 * sin(theta);
    this->rotation_prop += 10;

}

void Ball::roll() {
    this->rotation_z += 2;
    float theta = this->rotation_z * M_PI / 180.0f;
    this->position.x += 0.05 * cos(theta);
    this->position.y += 0.05 * sin(theta);
    this->position.z -= 0.05;
    this->rotation_prop += 10;
}

