#include "window.h"
#include <iostream>

namespace graphx{

    Window::Window(const char * title, int width, int height):
        m_Title(title), m_Width(width), m_Height(height)
    {
        if(!init()) 
            glfwTerminate();
    }

    Window::~Window(){
        glfwTerminate();
    }

    bool Window::init(){
        
        // initialize GLFW
        if(!glfwInit()){
    std::cerr << "GLFW was not loaded correctly. Exiting ...\n";
            return false;
        }

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

        // check if the window was properly created
        if(!m_Window){
    std::cerr << "Window was not succesfully created. Exiting ...\n";
            glfwTerminate();
            return false;
        }


        glfwSetWindowSizeLimits(m_Window, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glViewport(0,0,m_Width, m_Height);

        glfwSetWindowUserPointer(m_Window, this);
        glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);
        glfwSetKeyCallback(m_Window, input::key_callback);
        glfwSetCursorPosCallback(m_Window, input::cursor_position_callback);

        glfwMakeContextCurrent(m_Window);

        if(glewInit() != GLEW_OK){
    std::cerr << "GLEW was not loaded correctly. Exiting ...\n";
            return false;
        }

        return true;
    }

    void Window::clear() const{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::update(){
        glfwSwapBuffers(m_Window);

        glfwPollEvents();
    }

    void Window::getCursorPosition(float & x, float & y)
    {
        m_Mouse.getXY(x,y);
        x = 2 * (x/m_Width) - 1;
        y = (1 - 2 * (y/m_Height));
    }
    
    void window_resize_callback(GLFWwindow * win, int width, int height){
        Window* window = (Window*)glfwGetWindowUserPointer(win);

        window->m_Height = height;
        window->m_Width = width;

        glViewport(0,0, width, height);        
    }

}