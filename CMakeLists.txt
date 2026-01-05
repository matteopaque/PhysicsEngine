cmake_minimum_required(VERSION 4.0)
project(openglSetup)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
set(CMAKE_CXX_STANDARD 20)
add_library(glad STATIC ${PROJECT_SOURCE_DIR}/glad/src/glad.c ${PROJECT_SOURCE_DIR}/glad/include/glad/glad.h)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/glad/include)

add_executable(openglSetup main.cpp
        Shader.cpp
        Shader.h
        stb_image.h
        Texture.cpp
        Texture.h
        Sphere.cpp
        Sphere.h
        Particle.cpp
        Particle.h
        Timer.cpp
        Timer.h
        ParticleForceGenerator.h
        ParticleForceRegistry.cpp
        ParticleForceRegistry.h
        ParticleSpring.cpp
        ParticleSpring.h
)
target_link_libraries(openglSetup glfw)
target_link_libraries(openglSetup glad)
target_link_libraries(openglSetup glm::glm)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vertexShader.glsl ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fragmentShader.glsl ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wall.jpg ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
