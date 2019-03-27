#include "fuel.h"
#include "main.h"
#define dim 0.1f
Fuel::Fuel(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = { 
        -dim,-dim,-dim,
        -dim,-dim, dim,
        -dim, dim, dim,
         dim, dim,-dim,
        -dim,-dim,-dim,
        -dim, dim,-dim,
         dim,-dim, dim,
        -dim,-dim,-dim,
         dim,-dim,-dim,
         dim, dim,-dim,
         dim,-dim,-dim,
        -dim,-dim,-dim,
        -dim,-dim,-dim,
        -dim, dim, dim,
        -dim, dim,-dim,
         dim,-dim, dim,
        -dim,-dim, dim,
        -dim,-dim,-dim,
        -dim, dim, dim,
        -dim,-dim, dim,
         dim,-dim, dim,
         dim, dim, dim,
         dim,-dim,-dim,
         dim, dim,-dim,
         dim,-dim,-dim,
         dim, dim, dim,
         dim,-dim, dim,
         dim, dim, dim,
         dim, dim,-dim,
        -dim, dim,-dim,
         dim, dim, dim,
        -dim, dim,-dim,
        -dim, dim, dim,
         dim, dim, dim,
        -dim, dim, dim,
         dim,-dim, dim
    };
    float ut = 8.65;
    static const GLfloat vertex_buffer_data2[] = { 
        -ut*dim,-ut*dim,-ut*dim,
        -ut*dim,-ut*dim, ut*dim,
        -ut*dim, ut*dim, ut*dim,
         ut*dim, ut*dim,-ut*dim,
        -ut*dim,-ut*dim,-ut*dim,
        -ut*dim, ut*dim,-ut*dim,
         ut*dim,-ut*dim, ut*dim,
        -ut*dim,-ut*dim,-ut*dim,
         ut*dim,-ut*dim,-ut*dim,
         ut*dim, ut*dim,-ut*dim,
         ut*dim,-ut*dim,-ut*dim,
        -ut*dim,-ut*dim,-ut*dim,
        -ut*dim,-ut*dim,-ut*dim,
        -ut*dim, ut*dim, ut*dim,
        -ut*dim, ut*dim,-ut*dim,
         ut*dim,-ut*dim, ut*dim,
        -ut*dim,-ut*dim, ut*dim,
        -ut*dim,-ut*dim,-ut*dim,
        -ut*dim, ut*dim, ut*dim,
        -ut*dim,-ut*dim, ut*dim,
         ut*dim,-ut*dim, ut*dim,
         ut*dim, ut*dim, ut*dim,
         ut*dim,-ut*dim,-ut*dim,
         ut*dim, ut*dim,-ut*dim,
         ut*dim,-ut*dim,-ut*dim,
         ut*dim, ut*dim, ut*dim,
         ut*dim,-ut*dim, ut*dim,
         ut*dim, ut*dim, ut*dim,
         ut*dim, ut*dim,-ut*dim,
        -ut*dim, ut*dim,-ut*dim,
         ut*dim, ut*dim, ut*dim,
        -ut*dim, ut*dim,-ut*dim,
        -ut*dim, ut*dim, ut*dim,
         ut*dim, ut*dim, ut*dim,
        -ut*dim, ut*dim, ut*dim,
         ut*dim,-ut*dim, ut*dim
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3 , vertex_buffer_data, vertex_buffer_data2, GL_FILL);    

}



void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate  = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {
    this->position.y -= 0.01;
}

