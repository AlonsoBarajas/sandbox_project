#include "utils/fileutils.h"
#include "utils/stb_image.h"
#include "graphics/window.h"
#include "graphics/shader.h"
#include <iostream>
#include <math.h>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

float globMix = 0.2;

int main (void){

    graphx::Window win("Hello james", 640, 480);

    //glfwSetKeyCallback( win.getWindowPointer(), key_callback);


    graphx::Shader shader("../shaders/texture.vs", "../shaders/texture.fs");

    shader.compile();



  
    ///////////////////////////////////////////////////////////////////
    //              Create Vertext Buffer Object VBO
    ///////////////////////////////////////////////////////////////////

    // definition of the triangle vertices // Position and color attributes
    GLfloat vertices[] = {
        // Position          // Color           // Texture
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.45f, 0.45f,     // lower left
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.55f, 0.45f,     // lower right
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.45f, 0.55f,     // top left
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.55f, 0.55f      // top right
    };

    GLint indices[] = {
        0,1,2,
        1,3,2
    };

    // create a vertex buffer object VBO
    GLuint VBO;
    glGenBuffers(1 , &VBO);

    // create an element buffer object
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // create Vertex Attribute Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // bind VAO 
    glBindVertexArray(VAO);

    // bind VBO to the current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // this copies the data of the vertices into the currently bound array buffer i.e. VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind EBO to the current array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // pass the indeces to the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLfloat), indices, GL_STATIC_DRAW);


    // tell OpenGL how to interpret the vertex attributes
    // position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    // color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    // texture attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6*sizeof(GLfloat)));

    // enables the vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

        
    // Create texture ID
    GLuint texture[2];
    glGenTextures(2, texture);
    
    // Bind texture  
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // Texture options wrapping/filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image
    GLint width, height, nrChannels;
    unsigned char * data = stbi_load("../assets/container.jpg", &width, &height, &nrChannels, 0);

    if(data){
        // Load the texture to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else 
std::cerr<<"Failed to load texture\n";


    // Release data memory from image
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // Texture options wrapping/filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../assets/awesomeface.png", &width, &height, &nrChannels, 0);

    if(data){
        // Load the texture to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else 
std::cerr<<"Failed to load texture\n";

    // Release data memory from image
    stbi_image_free(data);

    shader.activate();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    float posx = 0.0f;
    float posy = 0.0f;

    while (!win.closed()){
        win.clear();

        // generate a variable color
        GLfloat time = glfwGetTime();
        GLfloat redChannel = sin(time)/2.0f + 0.5f;
        
        // retrieve uniform location
        GLint colorLoc = glGetUniformLocation(shader.getShader(), "myColor");
        
        

        glUniform4f(colorLoc, redChannel, 0.5f, 0.2f, 1.0f);
        

        if(win.isKeyPressed(GLFW_KEY_W))
            posy += 0.01f;
        if(win.isKeyPressed(GLFW_KEY_S))
            posy -= 0.01f;        
        if(win.isKeyPressed(GLFW_KEY_D))
            posx += 0.01f;
        if(win.isKeyPressed(GLFW_KEY_A))
            posx -= 0.01f;
        
        int loc = glGetUniformLocation(shader.getShader(), "pos");
        glUniform2f(loc, posx, posy);

        shader.setFloat("linearBlend", globMix);

        shader.activate();

        for (size_t i = 0; i < 2 ; ++i){
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, texture[i]);
        }

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        win.update();
    }

    return 0;
}



void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_W && action == GLFW_PRESS)
        globMix = globMix < 1.0f ? globMix + 0.1 : 1.0f;
    if(key == GLFW_KEY_S && action == GLFW_PRESS)
        globMix = globMix > 0.0f ? globMix - 0.1 : 0.0f;
    return;
}