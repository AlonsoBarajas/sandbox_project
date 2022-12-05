CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)
PROJECT(sandbox)

# Find and link required packages

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)




# Add executable files
SET(SOURCE_FILES src/main.cpp src/graphics/window.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


# Linking libraries
target_link_libraries(${PROJECT_NAME}     
    GLEW
    glfw
    OpenGL::GL
)
