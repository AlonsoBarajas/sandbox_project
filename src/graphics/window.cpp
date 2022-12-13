#include "window.h"
#include <iostream>

namespace graphx{

    Window::Window(const char * title, int width, int height):
        m_Title(title), m_Width(width), m_Height(height)
    {
        if(!init()) 
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

        // set minimum window size
        glfwSetWindowSizeLimits(m_Window, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

        // tell OpenGL what is the window size
        glViewport(0,0,m_Width, m_Height);

        // bind GLFW window to an object of the Window class
        glfwSetWindowUserPointer(m_Window, this);

        // bind resize function to GLFW callback
        glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);

        // bind key callback function
        glfwSetKeyCallback(m_Window, key_callback);

        // make the window the current OpenGL context
        glfwMakeContextCurrent(m_Window);

        // initialize GLEW
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

    Window::~Window(){
        glfwTerminate();
    }

    void window_resize_callback(GLFWwindow * win, int width, int height){
        Window* window = (Window*)glfwGetWindowUserPointer(win);

        window->m_Height = height;
        window->m_Width = width;

        glViewport(0,0, width, height);        
    }

    void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods){
        Window* window = (Window*)glfwGetWindowUserPointer(win);

        if(action == GLFW_PRESS)
            window->m_Keyboard.m_Keys[key] = true;
        else if(action == GLFW_RELEASE)
            window->m_Keyboard.m_Keys[key] = false;
    }


}