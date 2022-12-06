
#include "graphics/window.h"
#include <iostream>

int main (void){


    graphx::Window win("Hello james", 640, 480);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, NULL, 3*sizeof(GLfloat), (void*)0);

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

        // render loop
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        win.update();
    }

    return 0;
}