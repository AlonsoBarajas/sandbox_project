#include "window.h"

Window::Window(char * title, int width, int height):
    m_Title(title), m_Width(width), m_Height(height)
{
    if(!init()) glfwTerminate;
}

bool Window::init(){
    
    // initialize GLFW
    if(!glfwInit()) 
        return false;

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

    // check if the window was properly created
    if(!m_Window){
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // initialize GLEW
    if(glewInit() != GLEW_OK)
        return false;


    return true;
}

void Window::update(){

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_Window);

    glfwPollEvents();
}

Window::~Window(){
    glfwTerminate();
}