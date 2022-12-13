#include "input.h"

#include "../graphics/window.h"

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


    Mouse::Mouse()
    {
        clearMouse();
    }

    void Mouse::clearMouse()
    {
        for (bool& button: m_Buttons)
            button = false;
    }

    // Input callbacks

    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods)
    {
        graphx::Window* window = (graphx::Window*)glfwGetWindowUserPointer(win);

        if(action == GLFW_PRESS)
            window->m_Keyboard.m_Keys[key] = true;
        else if(action == GLFW_RELEASE)
            window->m_Keyboard.m_Keys[key] = false;
    }

    void cursor_position_callback(GLFWwindow * win, double xpos, double ypos){
        graphx::Window* window = (graphx::Window*)glfwGetWindowUserPointer(win);

        window->m_Mouse.m_X = xpos;
        window->m_Mouse.m_Y = ypos;
    }
}