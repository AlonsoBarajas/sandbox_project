#pragma once

#include <GLFW/glfw3.h>

namespace graphx{
    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
}

namespace input
{
    constexpr int MAX_KEYS = 1024;

    class Keyboard{
        public:
            Keyboard();

            inline bool isKeyPressed(int key){ return m_Keys[key]; }

        private:
            bool m_Keys[MAX_KEYS];
            void clearKeys();

            friend void graphx::key_callback(GLFWwindow * win, int key, int scancode, int action, int mods);
    };
}

