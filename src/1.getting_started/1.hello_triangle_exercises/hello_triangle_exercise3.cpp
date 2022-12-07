
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
    const char * fragmentShaderSourceO = "#version 330 core\n"      // orange fragment shader
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    const char * fragmentShaderSourceY = "#version 330 core\n"      // yellow fragment shader 
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
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


    // orange fragment shader
    GLuint fragmentShaderO;
    fragmentShaderO = glCreateShader(GL_FRAGMENT_SHADER);

    // attach shader source to the fragment shader object
    glShaderSource(fragmentShaderO, 1, &fragmentShaderSourceO, NULL);

    // compile shader
    glCompileShader(fragmentShaderO);

    // yellow fragment shader
    GLuint fragmentShaderY;
    fragmentShaderY = glCreateShader(GL_FRAGMENT_SHADER);

    // upload source for yellow shader
    glShaderSource(fragmentShaderY, 1, &fragmentShaderSourceY, NULL);

    // compile yellow shader
    glCompileShader(fragmentShaderY);


    //check for compilation errors
    GLint success_vertex;
    GLint success_fragment;

    GLchar infoLogV[512];
    GLchar infoLogF[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);
    glGetShaderiv(fragmentShaderO, GL_COMPILE_STATUS, &success_fragment);

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
    //              Create and link shader program
    ///////////////////////////////////////////////////////////////////

    // creating a shader program
    GLuint shaderProgram[2];
    shaderProgram[0] = glCreateProgram();

    // attach the previously created shaders
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShaderO);

    // link shaders 
    glLinkProgram(shaderProgram[0]);

    // check link success
    GLint success_program;
    GLchar infoLogP[512];

    glGetProgramiv(shaderProgram[0],GL_LINK_STATUS, &success_program);

    if(!success_program){
        glGetShaderInfoLog(shaderProgram[0], 512, NULL, infoLogP);
std::cerr << "ERROR::SHADER::PROGRAM::LINKER_FAILED\n"
          << infoLogP << std::endl;

    }

    // New shader program for yellow triangle
    shaderProgram[1] = glCreateProgram();

    // attach shaders to program    
    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShaderY);

    // link program
    glLinkProgram(shaderProgram[1]);

    // delete objects since they are already linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderO);
    glDeleteShader(fragmentShaderY);

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

  
    while (!win.closed()){
        win.clear();

        // render loop


        for (size_t i = 0 ; i < 2 ; ++i){
            glUseProgram(shaderProgram[i]);
            glBindVertexArray(VAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        win.update();
    }

    return 0;
}