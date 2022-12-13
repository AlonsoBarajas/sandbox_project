CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)
PROJECT(sandbox)

# Find and link required packages


find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)




# Add executable files
SET(SOURCE_FILES src/main.cpp 
    src/graphics/window.cpp 
    src/input/input.cpp 
    src/graphics/shader.cpp  
    src/utils/fileutils.cpp 
    src/utils/stb_image.cpp)

    
SET(EXERCISE_FILES src/exercises/1.getting_started/hello_triangle_exercise3.cpp src/graphics/window.cpp)
# Exercises
# src/exercises/1.getting_started/hello_triangle_exercise2.cpp

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


# Linking libraries
target_link_libraries(${PROJECT_NAME}     
    GLEW
    glfw
    OpenGL::GL
)
