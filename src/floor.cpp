#include "floor.h"
#include "main.h"

long long int sp = 10000.0f;
Floor::Floor(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        100.0f,0,100.0f,
        100.0f,0,-100.0f,
        -100.0f,0,-100.0f,
        -100.0f,0,-100.0f,
        -100.0f,0,100.0f,
        100.0f,0,100.0f,
    };
    // GLfloat vertex_buffer_data2[100000];
    // int k = 0;
    // for(int i=0;i<100;i+=2)
    //     for(int j=0;j<100;j+=2)
    //     {        
    //     vertex_buffer_data2[k++]=2.0+i;
    //     vertex_buffer_data2[k++]=1.0f;
    //     vertex_buffer_data2[k++]=2.0+j;
    //     vertex_buffer_data2[k++]=2.0+i;
    //     vertex_buffer_data2[k++]=1.0f;
    //     vertex_buffer_data2[k++]=-2.0+j;
    //     vertex_buffer_data2[k++]=-2.0+i;
    //     vertex_buffer_data2[k++]=1.0f;
    //     vertex_buffer_data2[k++]=-2.0+j;
    //     vertex_buffer_data2[k++]=-2.0+i;
    //     vertex_buffer_data2[k++]=1.0f;
    //     vertex_buffer_data2[k++]=2.0+j;
    //     vertex_buffer_data2[k++]=-2.0+i;
    //     vertex_buffer_data2[k++]=1.0f;
    //     vertex_buffer_data2[k++]=-2.0+j;
    //     vertex_buffer_data2[k++]=2.0+i;
    //     vertex_buffer_data2[k++]=1.0f;
    //     vertex_buffer_data2[k++]=2.0+j;
        // }
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);    
}
    
void Floor::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object2);
}

void Floor::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Floor::tick() {
}

