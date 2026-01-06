#include <cmath>
#include <cstring>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iterator>
#define STB_IMAGE_IMPLEMENTATION
#include <algorithm>

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Sphere.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ParticleSpring.h"
#include "Timer.h"
#include "LineVertexLoader.h"
#include "Render2D.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow * window,double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, double deltaTime);


const unsigned int SCR_WIDTH {800};
const unsigned int SCR_HEIGHT { 600};

    std::vector<LineVertexLoader> Lines;
float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
};
float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[]
{
    0, 1, 2,
    1, 2, 3
};

glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 3.f);
glm::vec3 cameraFront = glm::vec3(0.f, 0.f, -1.f);
glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

float yaw = -90.f, pitch = 0.0f;
float fov = 90.f;


std::vector <glm::vec3> cubePositons {
    glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -5.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -2.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -5.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

bool Init(GLFWwindow*& window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "windows fucked\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window );
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "glads fucked\n";
        return false;
    }
    return true;
}
std::pair<int, int> operator+=(std::pair<int,int> &first, std::pair<int,int> const & second)
{
    first.first += second.first;
    first.second += second.second;
    return first;
}

std::pair<int, int> getNthSpiralPath(int n)
{
    std::vector<std::pair<int, int>> movements{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    std::pair<int, int> position {0, 0};
    for (int i =0; i<n; i++)
    {
        position += movements.at((
            (int)std::floor(std::sqrt(4*(i)+1))
            )%4);
    }
    return position;
}
using particleID = unsigned int;
std::map<particleID, Particle> particleArray;

    auto bouncy = Particle({0.f, 5.f, 0.f}, {4.f, 0.f, 0.f}, 1.f);
int main()
{
    // init
    GLFWwindow* window;

    if (!Init(window))
        return -1;

    //shader class
    Shader shader {"vertexShader.glsl", "fragmentShader.glsl"};
    shader.use();
    shader.setInt("ourTexture", 0);
    shader.setInt("ourTexture2", 1);
    //texture
    Texture textureContext;
    textureContext.loadTexture(0, "wall.jpg", GL_RGB, false);
    textureContext.loadTexture(1, "awesomeface.png", GL_RGBA, true);

    // vertex stuff plane
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer( GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    //vertex stuff cube
    unsigned int cubeVao;
    glGenVertexArrays(1, &cubeVao);
    glBindVertexArray(cubeVao);

    unsigned int cubeVbo;
    glGenBuffers(1, &cubeVbo);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int sphereVao;
    glGenVertexArrays(1, &sphereVao);
    glBindVertexArray(sphereVao);

    Sphere sphere{};
    sphere.buildVertices(40, 40);

    unsigned int sphereVbo;
    glGenBuffers(1, &sphereVbo);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sphere.getVerticesSize(), (void*)sphere.getVertices(), GL_STATIC_DRAW);

    unsigned int sphereEbo;
    glGenBuffers(1, &sphereEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*sphere.getIndicesSize(), (void*)sphere.getIndices(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //coord space matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view;
    glm::mat4 projection;

    //turn on depth test
    glEnable(GL_DEPTH_TEST);

    double lastTime = glfwGetTime();
    double thisTime, deltaTime;

    Timer timer;
    ParticleForceRegistry forceRegistry;
   /* timer.addTask(0.05, [&](int Times)
    {
        particleArray.push_back(Particle({0.f, 0.f, 0.f}, {glm::cos(glfwGetTime())*5, 10.f, glm::sin(glfwGetTime())*5}, 1.f));
        return true;
    });*/

    ParticleSpring spring({4.f, 5.f, 0.f}, 0.99f, 2.f);


    forceRegistry.addRegistration(bouncy, spring);

    LineVertexLoader lineLoader{};
    lineLoader.Initialize(glm::vec3(0.f), glm::vec3(0.f));
    Render2D vertices2D;
    vertices2D.InitializeSquare({400.f, 300.f}, 100.f);


    while (!glfwWindowShouldClose(window))
    {
        thisTime = glfwGetTime();
        deltaTime = thisTime - lastTime;
        lastTime = thisTime;

        //input
        processInput(window, deltaTime);

        //update world
        timer.update(deltaTime);
        forceRegistry.updateForces(deltaTime);
        for (auto & particle : particleArray)
        {
            particle.second.integrate(deltaTime);
        }
        bouncy.integrate(deltaTime);


        //clear buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // set right shader and textures and vertex array
        shader.use();
        textureContext.use();
        glBindVertexArray(sphereVao);


        // set right transformation matrices
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.setMat4("view", glm::value_ptr(view));
        projection = glm::perspective(glm::radians(fov), 800.f/600.f, 0.1f, 100.f);
        shader.setMat4("projection", glm::value_ptr(projection));

        for (auto particle : particleArray)
        {
            model = glm::translate(glm::mat4(1.f), particle.second.getPosition());
            model = glm::scale(model, glm::vec3(1.f)*particle.second.radius);
            shader.setMat4("model", glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, sphere.getIndicesSize(), GL_UNSIGNED_INT, 0);
        }
        model = glm::translate(glm::mat4(1.f), bouncy.getPosition());
        model = glm::scale(model, glm::vec3(1.f)*bouncy.radius);
        shader.setMat4("model", glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, sphere.getIndicesSize(), GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.f);
        shader.setMat4("model", glm::value_ptr(model));
        lineLoader.newLine(spring.getAnchor(), bouncy.getPosition());
        lineLoader.useVertexArray();
        glDrawArrays(GL_LINES, 0, 2);
        for (auto & line : Lines)
        {
            line.useVertexArray();
            glDrawArrays(GL_LINES, 0, 2);
        }
        // 2D FROM HERE


        glClear(GL_DEPTH_BUFFER_BIT);

        vertices2D.use();
        projection = glm::ortho(0, 800, 0, 600, -500, 500);
        shader.setMat4("projection", glm::value_ptr(projection));

        view = glm::mat4(1.f);
        shader.setMat4("view", glm::value_ptr(view));
        glDrawArrays(GL_LINES, 0, 6);




        // loop through cubes
        const int circleAmount = 0;
        for (int k=1; k<=circleAmount; k++)
        for (int j=1; j<=circleAmount; j++)
        {
            for (std::size_t i = 0; i < cubePositons.size(); i++)
            {
                model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f*k, 0.f));
                model = glm::rotate(model, (float)j, glm::normalize(glm::vec3(1.f, 0.f, 0.f)));
                model = glm::translate(model, cubePositons.at(i) - glm::vec3(std::sin(glfwGetTime()-0.25*k)*5*j, 1.f, std::cos(glfwGetTime()-0.25*k)*5*j));
                model = glm::rotate(model, (float)(glfwGetTime()-0.25*k), glm::normalize(glm::vec3(1.f, 2.f, 0.f)));

                shader.setMat4("model", glm::value_ptr(model));
                glDrawElements(GL_TRIANGLES, sphere.getIndicesSize(), GL_UNSIGNED_INT, 0);
            }
        }
        glBindVertexArray(VAO);


        int floorCount = 50; //std::floor(std::abs(1 - 2*std::fmod(glfwGetTime()/10.f, (double)1))*100);
        for (int i = 0; i < floorCount; i++)
        {
            int offset = (i%20)*5;

            std::pair<int, int> position = getNthSpiralPath(i);
         model = glm::translate(glm::mat4(1.f), glm::vec3(position.first*4, -50.f, position.second*4));
            model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
            model = glm::scale(model, glm::vec3(4.f, 4.f, 1.f));
            shader.setMat4("model", glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        // show screen and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
        while (!(glfwGetTime()- thisTime > 1.f/60.f)){}
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, double deltaTime)
{
    glm::mat3 xzProjection {
            1, 0, 0,
            0, 0, 0,
            0, 0, 1};
    glm::vec3 frontLateral = glm::normalize(xzProjection * cameraFront);
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed *frontLateral;
    }
    if (glfwGetKey(window, GLFW_KEY_R)== GLFW_PRESS)
        cameraPos -= cameraSpeed *frontLateral;
    if (glfwGetKey(window, GLFW_KEY_S)== GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(frontLateral, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A)== GLFW_PRESS)

        cameraPos -= glm::normalize(glm::cross(frontLateral, cameraUp)) * cameraSpeed;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        //particleArray.push_back(Particle(cameraPos + cameraFront - 0.6f *glm::cross(glm::cross(cameraFront, cameraUp), cameraFront),
         //   cameraFront*5.f + glm::vec3({0.f, 4.f, 0.f}), 0.5f));

        Line ray {cameraPos, cameraPos + 5.f*cameraFront};
        Lines.emplace_back(ray);
        bouncy.addForce(50.f*ray.IntersectWithSphere(bouncy.getPosition(), bouncy.radius));

    }

}
float lastX = 400, lastY = 300;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    yaw += xoffset*sensitivity;
    pitch += yoffset*sensitivity;
    if (pitch > 89.f)
        pitch = 89.f;
    if (pitch < -89.f)
        pitch= -89.f;
    cameraFront.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    cameraFront.y = std::sin(glm::radians(pitch));
    cameraFront.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 90.f)
        fov = 90.f;
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
     if (height > width*(600.f/800.f))
         glViewport(0,(height-width*(600.f/800.f))/2.f, width, width*(600.f/800.f));
     else
         glViewport((width - height*(800.f/600.f))/2.f,0, height*(800.f/600.f), height);
}
