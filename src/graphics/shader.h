# pragma once

#include "../utils/fileutils.h"
#include <GL/glew.h>

class Shader{

public:
    Shader(const char * vertexFile, const char * fragmentFile);
    ~Shader();

    bool compile();

    inline void activate() { glUseProgram(m_ShaderProgram); }


private:
    const char * m_VertexContents;
    const char * m_FragmentContents;

    GLuint m_VertexShader;
    GLuint m_FragmentShader;

    GLuint m_ShaderProgram;

    bool init(const char * vertexFile, const char * fragmentFile);
    bool errorCheck(GLuint shaderID, GLenum status);


};
