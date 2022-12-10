#include "../../utils/fileutils.h"
#include "../../graphics/window.h"
#include "../../graphics/shader.h"
#include <iostream>
#include <math.h>

int main (void){

    graphx::Window win("Hello james", 640, 480);

    graphx::Shader shader("../shaders/basics.loccol.vert", "../shaders/basics.loccol.frag");

    shader.compile();

    ///////////////////////////////////////////////////////////////////
    //              Create Vertext Buffer Object VBO
    ///////////////////////////////////////////////////////////////////

    // definition of the triangle vertices // Position and color attributes
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    // lower left corner
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // lower right corner
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    // create a vertex buffer object VBO
    GLuint VBO;
    glGenBuffers(1 , &VBO);

    // create Vertex Attribute Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // bind VAO 
    glBindVertexArray(VAO);

    // bind VBO to the current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // this copies the data of the vertices into the currently bound array buffer i.e. VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell OpenGL how to interpret the vertex attributes

    // position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    // color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));


    // enables the vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);



    while (!win.closed()){
        win.clear();

        // generate a variable color
        GLfloat time = glfwGetTime();
        GLfloat redChannel = sin(time)/2.0f + 0.5f;
        
        // retrieve uniform location
        GLint colorLoc = glGetUniformLocation(shader.getShader(), "myColor");
        
        // render loop
        shader.activate();
        glUniform4f(colorLoc, redChannel, 0.5f, 0.2f, 1.0f);
        shader.setFloat("xOffset", redChannel);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        win.update();
    }

    return 0;
}