#include "shader.h"
#include "../utils/fileutils.h"
#include <iostream>
Shader::Shader(const char * vertexFile,const char * fragmentFile){
    if(!init(vertexFile, fragmentFile)){
std::cerr<<"SHADER::INIT_FAILED\n";
        exit(1);
    }

}

bool Shader::init(const char * vertexFile,const char * fragmentFile){

    m_VertexContents = read_file(vertexFile).c_str();
    m_FragmentContents = read_file(fragmentFile).c_str();

    if(m_VertexContents == ""){
std::cerr<<"Vertex shader not found in " << vertexFile << "\n";
    }

    if(m_FragmentContents == ""){
std::cerr<<"Fragment shader not found in " << fragmentFile << "\n";
    }

    if(m_VertexContents == "" || m_FragmentContents == "") return false;

}

bool Shader::compile(){

    // ..:: Vertex shader ::..
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);

    if(!m_VertexShader){
std::cerr << "Error creating vertex shader\n";
    return false;
    }

    glShaderSource(m_VertexShader, 1, &m_VertexContents, NULL);
    glCompileShader(m_VertexShader);

    // check for compile errorssS
    if(errorCheck(m_VertexShader, GL_COMPILE_STATUS)) return false;


    // ..:: Fragment shader ::..
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if(!m_FragmentShader){
std::cerr << "Error creating fragment shader\n";
    return false;
    }

    glShaderSource(m_FragmentShader, 1, &m_FragmentContents, NULL);
    glCompileShader(m_FragmentShader);

    if(errorCheck(m_FragmentShader, GL_COMPILE_STATUS)) return false;

    // ..:: Create shader program ::..

    m_ShaderProgram = glCreateProgram();

    if(!m_ShaderProgram){
std::cerr << "Error creating shader program\n";
    return false;
    }

    // attach shaders to the program
    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);

    // link program
    glLinkProgram(m_ShaderProgram);

    if(errorCheck(m_ShaderProgram, GL_LINK_STATUS)) return false;

    // delete shaders
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);

    return true;
}


bool Shader::errorCheck(GLuint shaderID, GLenum status){
    GLint success;

    glGetShaderiv(shaderID, status, &success);

    if(success) return false;

    GLchar infoLog[512];

    glGetShaderInfoLog(shaderID, 512, NULL, infoLog);

std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<< infoLog << std::endl;

    return true;
}