#include <iostream>
#include <string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
using namespace glm;
using namespace std;
#include<list>
#include "ShaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLfloat vertices[] =
    {
        -0.5f,-0.5f,0.0f,   1.0f, 0.5f, 0.2f, 
        0.0f,-0.5f,0.0f,   0.6f, 0.8f, 0.3f,
        0.5f,-0.5f,0.0f,   1.0f, 0.5f, 0.2f, 
        0.25f,0.0f,0.0f,   0.6f, 0.8f, 0.3f,
        0.0f,0.5f,0.0f,   1.0f, 0.5f, 0.2f, 
        -0.25f,0.0f,0.0f,   0.6f, 0.8f, 0.3f, 

    };

    GLuint indices[] = {
        0,1,5,
        1,2,3,
        5,3,4,

    };

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "win", NULL, NULL);

    if (window == NULL)
    {
        cout << "RIP BOZO" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGL();
    glViewport(0, 0, 800, 600);

    Shader shaderProgram("default.vert", "default.frag");
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    VAO1.LinkAttrib(VBO1, 0,3,GL_FLOAT,6 * sizeof(float),(void*)0);
    VAO1.LinkAttrib(VBO1, 1,3,GL_FLOAT,6 * sizeof(float),(void*)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    glDepthFunc(GL_LESS);

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID,pow(sin((float)glfwGetTime()),2));
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


