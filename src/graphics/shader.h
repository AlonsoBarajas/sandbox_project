# pragma once

#include "../utils/fileutils.h"
#include <GL/glew.h>

namespace graphx{

    class Shader{

    public:
        Shader(const char * vertexFile, const char * fragmentFile);
        ~Shader();

        bool compile();

        inline void activate() { glUseProgram(m_ShaderProgram); }
        inline GLuint getShader() { return m_ShaderProgram; }

    private:
        std::string m_VertexSource;
        std::string m_FragmentSource;

        GLuint m_ShaderProgram;

        bool init(const char * vertexFile, const char * fragmentFile);
        bool errorCheck(GLuint ID, GLenum status);


    };

}

