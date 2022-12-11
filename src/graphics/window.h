#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphx{

    constexpr int MIN_WINDOW_HEIGHT = 480;
    constexpr int MIN_WINDOW_WIDTH = 640;
    class Window{

        public:
            Window(const char * title, int width, int height);
            ~Window();

            void update();
            void clear() const;
            inline bool closed() const { return glfwWindowShouldClose(m_Window); }

            // setters
            inline void setHeight(int height){ m_Height = height; }
            inline void setWidth(int width){ m_Width = width; }

            // getters
            inline GLFWwindow * getWindowPointer() { return m_Window; }
        private:
            bool init();

        private:
            GLFWwindow * m_Window;

            int m_Width;
            int m_Height;
            const char * m_Title;

    }; // Window

    void window_resize_callback(GLFWwindow * win, int widht, int height);

}