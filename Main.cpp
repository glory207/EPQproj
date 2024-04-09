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
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLfloat vertices[] =
    {
        -0.5f,-0.5f,0.0f,
        0.0f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.25f,0.0f,0.0f,
        0.0f,0.5f,0.0f,
        -0.25f,0.0f,0.0f,

    };

    GLuint indices[] = {
        0,1,5,
        1,2,3,
        5,3,4,

    };

    GLFWwindow* window = glfwCreateWindow(800, 800, "win", NULL, NULL);

    if (window == NULL)
    {
        cout << "RIP BOZO" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("default.vert", "default.frag");
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
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




