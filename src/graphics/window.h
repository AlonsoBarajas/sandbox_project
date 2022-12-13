#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../input/input.h"


namespace input{
    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
}

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
            inline bool isKeyPressed(int key){ return m_Keyboard.isKeyPressed(key); }
        private:
            bool init();


        private:
            GLFWwindow * m_Window;

            int m_Width;
            int m_Height;
            const char * m_Title;

            input::Keyboard m_Keyboard;

            friend void input::key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
            friend void window_resize_callback(GLFWwindow * win, int widht, int height);
    }; // Window

    void window_resize_callback(GLFWwindow * win, int widht, int height);

}