
#include "../../graphics/window.h"
#include <iostream>

int main (void){


    graphx::Window win("Hello Triangle ex.2", 640, 480);

    // Hello Triangle

    ///////////////////////////////////////////////////////////////////
    //                      Shaders
    ///////////////////////////////////////////////////////////////////

    // most basic vertex shader | Calculates the vertex atributes
    const char * vertexShaderSource = "#version 330 core\n"     // defines the OpenGL version
    "layout (location = 0) in vec3 aPos;\n"                     // creates an input vertex atribute named aPos
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"       // sets the gl_position to aPos which will be the output of the shader
    "}\n";

    // fragment shader | Calculates the final color of the pixels
    const char * fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    ///////////////////////////////////////////////////////////////////
    //              Create shader objects
    ///////////////////////////////////////////////////////////////////

    // create vertex shader object
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // attach the shader source to the vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // compile the shader
    glCompileShader(vertexShader);


    // create a fragment shader object
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // attach shader source to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // compile shader
    glCompileShader(fragmentShader);


    //check for compilation errors
    GLint success_vertex;
    GLint success_fragment;

    GLchar infoLogV[512];
    GLchar infoLogF[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragment);

    if(!success_vertex){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogV);
std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
          << infoLogV << std::endl;
     }
    if(!success_fragment){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogF);
std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
          << infoLogF << std::endl;

    }


    ///////////////////////////////////////////////////////////////////
    //              Create and link shader progrm
    ///////////////////////////////////////////////////////////////////

    // creating a shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    // attach the previously created shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // link shaders 
    glLinkProgram(shaderProgram);

    // check link success
    GLint success_program;
    GLchar infoLogP[512];

    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &success_program);

    if(!success_program){
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLogP);
std::cerr << "ERROR::SHADER::PROGRAM::LINKER_FAILED\n"
          << infoLogP << std::endl;

    }

    // delete objects since they are already linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ///////////////////////////////////////////////////////////////////
    //              Create VBO and VAO
    ///////////////////////////////////////////////////////////////////

    GLfloat tri_1[9] = {
        -0.5f, -0.5f, 0.0f,     // bottom left
         0.5f, -0.5f, 0.0f,     // bottom right
        -0.5f,  0.5f, 0.0f,     // top left
    };

    GLfloat tri_2[9] = {
         0.5f, -0.5f, 0.0f,     // bottom right
         0.5f,  0.5f, 0.0f,     // top right
        -0.5f,  0.5f, 0.0f      // top left
    };

    // create VBOs
    GLuint VBO[2];
    glCreateBuffers(2,VBO);

    // bind VBO1
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    // create VAOs
    GLuint VAO[2];
    glCreateVertexArrays(2, VAO);

    // bind VAO1
    glBindVertexArray(VAO[0]);

    // send data to the VBOs
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), tri_1, GL_STATIC_DRAW);

    // tell opengl how to interpret our data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);

    // enable vertex attribute pointer
    glEnableVertexAttribArray(0);

    // bind VBO2
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

    // bind VAO2
    glBindVertexArray(VAO[1]);

    // send data to the VBOs
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), tri_2, GL_STATIC_DRAW);

    // tell opengl how to interpret our data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);

    // enable vertex attribute pointer
    glEnableVertexAttribArray(0);

  
    // draw in wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!win.closed()){
        win.clear();

        // render loop
        glUseProgram(shaderProgram);

        for (GLuint id : VAO){
            glBindVertexArray(id);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        win.update();
    }

    return 0;
}