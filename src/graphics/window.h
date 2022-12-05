#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{
    private:
        GLFWwindow * m_Window;

        int m_Width, m_Height;
        const char * m_Title;

    // public member functions
    public:
        Window(const char * title, int width, int height);
        ~Window();
        void update();

        inline bool closed() const { return glfwWindowShouldClose(m_Window); }

    // private member functions
    private:
        bool init();

};