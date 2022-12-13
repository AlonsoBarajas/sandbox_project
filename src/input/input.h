#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace input
{
    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
    void cursor_position_callback(GLFWwindow * win, double xpos, double ypos);

    constexpr int MAX_KEYS = 1024;
    constexpr int MAX_BUTTONS = 32;

    class Keyboard{
        public:
            Keyboard();

            inline bool isKeyPressed(int key) const { return m_Keys[key]; }

        private:
            bool m_Keys[MAX_KEYS];
            void clearKeys();

            friend void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
    };

    class Mouse{
        public:
            Mouse();

            inline float getX() const { return m_X; }
            inline float getY() const { return m_Y; }
            inline void getXY(float &x, float&y) { x = m_X; y = m_Y; }
            inline bool isButtonPressed(int button) const { return m_Buttons[button]; }

        private:
            float m_X;
            float m_Y;
            bool m_Buttons[MAX_BUTTONS];

            void clearMouse();

            friend void cursor_position_callback(GLFWwindow * win, double xpos, double ypos);
    };

    class Controller{
        public:
            //Controller();

        private:


    };
}

