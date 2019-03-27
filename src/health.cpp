#include "health.h"
#include "main.h"

Health::Health(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    // this->rotation = -90;
    width = 1.0f;
    this->limit = 1.0f;
    
}
void Health::update() {
    GLfloat vertex_buffer_data[108];
    int k = 0;
    vertex_buffer_data[k++] = -width;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -width;
    vertex_buffer_data[k++] = 0.6f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = this->limit;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = this->limit;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = this->limit;
    vertex_buffer_data[k++] = 0.6f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -width;
    vertex_buffer_data[k++] = 0.6f;
    vertex_buffer_data[k++] = 0.0f;
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, COLOR_DRAGON, GL_FILL); 
}
void Health::draw(glm::mat4 VP) {
    this->update();
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate  = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Health::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Health::tick() {
    
}

