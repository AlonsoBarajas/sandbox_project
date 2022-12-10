#include "shader.h"
#include "../utils/fileutils.h"
#include <iostream>

namespace graphx{

    Shader::Shader(const char * vertexFile,const char * fragmentFile){
        if(!init(vertexFile, fragmentFile)){
    std::cerr<<"SHADER::INIT_FAILED\n";
            exit(1);
        }
    }

    Shader::~Shader(){ glDeleteProgram(m_ShaderProgram); }

    bool Shader::init(const char * vertexFile,const char * fragmentFile){

        m_VertexSource = read_file(vertexFile);
        m_FragmentSource = read_file(fragmentFile);

        if(m_VertexSource == ""){
    std::cerr<<"Vertex shader not found in " << vertexFile << "\n";
        }

        if(m_FragmentSource == ""){
    std::cerr<<"Fragment shader not found in " << fragmentFile << "\n";
        }

        if(m_VertexSource == "" || m_FragmentSource == "") return false;

        return true;
    }

    bool Shader::compile(){

        const char * vertexSource = m_VertexSource.c_str();
        const char * fragmentSource = m_FragmentSource.c_str();

        // ..:: Vertex and fragment shader ::..
        GLuint vertex;
        GLuint fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        if(!vertex){
std::cerr << "Error creating vertex shader\n";
        return false;
        }

        if(!fragment){
std::cerr << "Error creating fragment shader\n";
        return false;
        }

        glShaderSource(vertex, 1, &vertexSource, NULL);
        glShaderSource(fragment, 1, &fragmentSource, NULL);

        glCompileShader(vertex);
        glCompileShader(fragment);

        if(errorCheck(vertex, GL_COMPILE_STATUS)){
std::cerr << "Vertex compilation failed!\n"; 
            glDeleteShader(vertex);
            return false;
        }    
        if(errorCheck(fragment, GL_COMPILE_STATUS)){
std::cerr << "Fragment compilation failed!\n"; 
            glDeleteShader(fragment);
            return false;
        }

        // ..:: Create shader program ::..
        m_ShaderProgram = glCreateProgram();

        if(!m_ShaderProgram){
std::cerr << "Error creating shader program\n";
        return false;
        }

        // attach shaders to the program
        glAttachShader(m_ShaderProgram, vertex);
        glAttachShader(m_ShaderProgram, fragment);

        // link program
        glLinkProgram(m_ShaderProgram);

        if(errorCheck(m_ShaderProgram, GL_LINK_STATUS)){
std::cerr << "Linker failed!\n"; 
            glDeleteProgram(m_ShaderProgram);
            return false;
        } 

        // delete shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return true;
    }

    void Shader::setBool(const char * name, bool value){
        GLint uniformLoc = glGetUniformLocation(m_ShaderProgram, name);

        if(uniformLoc == -1){
std::cerr << "Attribute " << name << "was not found\n";
            return;
        }

        glUniform1i(uniformLoc, value);
    }

    void Shader::setFloat(const char * name, float value){
        GLint uniformLoc = glGetUniformLocation(m_ShaderProgram, name);

        if(uniformLoc == -1){
std::cerr << "Attribute " << name << "was not found\n";
            return;
        }

        glUniform1f(uniformLoc, value);
    }

    bool Shader::errorCheck(GLuint ID, GLenum status){
        GLint success;
        GLchar infoLog[512];


        switch (status)
        {
        case GL_COMPILE_STATUS:

            glGetShaderiv(ID, status, &success);

            if(success != GL_FALSE) return false;

            glGetShaderInfoLog(ID, 512, NULL, infoLog);
std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"<< infoLog << std::endl;

            break;
        case GL_LINK_STATUS:

            glGetProgramiv(ID, status, &success);

            if(success != GL_FALSE) return false;

            glGetProgramInfoLog(ID, 512, NULL, infoLog);
std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"<< infoLog << std::endl;

            break;
        default:
            std::cout << "Wrong status input!\n";

            break;
        }

        return true;
    }

}
