#include "input.h"


namespace input
{
    Keyboard::Keyboard()
    {
        clearKeys();
    }

    void Keyboard::clearKeys()
    {
        for (bool& key: m_Keys)
            key = false;
    }


    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods)
    {
        graphx::Window* window = (graphx::Window*)glfwGetWindowUserPointer(win);

        if(action == GLFW_PRESS)
            window->m_Keyboard.m_Keys[key] = true;
        else if(action == GLFW_RELEASE)
            window->m_Keyboard.m_Keys[key] = false;
    }

}