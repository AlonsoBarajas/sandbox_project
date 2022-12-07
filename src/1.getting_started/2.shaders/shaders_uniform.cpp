#include "../../utils/fileutils.h"
#include "../../graphics/window.h"
#include "../../graphics/shader.h"
#include <iostream>
#include <math.h>

int main (void){

    graphx::Window win("Hello james", 640, 480);

    graphx::Shader shader("../../../shaders/basics.vert", "../../../shaders/basics.uniform.frag");

    shader.compile();

    ///////////////////////////////////////////////////////////////////
    //              Create Vertext Buffer Object VBO
    ///////////////////////////////////////////////////////////////////

    // definition of the triangle vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,     // lower left corner
         0.5f, -0.5f, 0.0f,     // lower right corner
         0.0f,  0.5f, 0.0f      // top
    };

    // create a vertex buffer object VBO
    GLuint VBO[2];
    glGenBuffers(2 , VBO);

    // create Vertex Attribute Object
    GLuint VAO[2];
    glGenVertexArrays(2, VAO);

    // bind VAO 
    glBindVertexArray(VAO[0]);


    // bind VBO to the current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    // this copies the data of the vertices into the currently bound array buffer i.e. VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell OpenGL how to interpret the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);

    // enables the vertex attribute
    glEnableVertexAttribArray(0);

    // ..:: Exercise 1.- Draw two triangles next to each other with glDrawArrays
    // Vertices of both triangles, no Element Buffer Object
    GLfloat square[18] = {
        -0.5f, -0.5f, 0.0f,     // bottom left
         0.5f, -0.5f, 0.0f,     // bottom right
        -0.5f,  0.5f, 0.0f,     // top left

         0.5f, -0.5f, 0.0f,     // bottom right
         0.5f,  0.5f, 0.0f,     // top right
        -0.5f,  0.5f, 0.0f      // top left
    };

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

    // bind VAO
    glBindVertexArray(VAO[1]);

    // copy data into VBO
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), square, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void *)0);

    glEnableVertexAttribArray(0);


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

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        win.update();
    }

    return 0;
}