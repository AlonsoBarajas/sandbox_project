#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/window.h"

namespace input
{
    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);

    constexpr int MAX_KEYS = 1024;

    class Keyboard{
        public:
            Keyboard();

            inline bool isKeyPressed(int key){ return m_Keys[key]; }

        private:
            bool m_Keys[MAX_KEYS];
            void clearKeys();

            friend void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
    };

    class Mouse{
        public:
            Mouse();
        
        private:

    };

    class Controller{
        public:
            Controller();

        private:


    };
}

