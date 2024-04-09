#include <iostream>
#include <string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<stb/stb_image.h>
using namespace glm;
using namespace std;
#include<list>
#include "ShaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float SCR_WIDTH = 800;
float SCR_HEIGHT = 600;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
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
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram("default.vert", "default.frag");
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    
    Texture Wall("Wall.jpg",GL_TEXTURE_2D,GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    Wall.texUnit(shaderProgram, "tex0", 0);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();


        mat4 model = mat4(1.0f);
        mat4 view = mat4(1.0f);
        mat4 proj = mat4(1.0f);
        model = rotate(model, radians((float)glfwGetTime() * 100), vec3(1.0f,1.0f,0.0f));
        view = translate(view, vec3(0.0f,-0.5f,-2.0f));
        proj = perspective(radians(45.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
        GLuint modelID = glGetUniformLocation(shaderProgram.ID, "model");
        GLuint viewID = glGetUniformLocation(shaderProgram.ID, "view");
        GLuint projID = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(modelID,1,GL_FALSE, value_ptr(model));
        glUniformMatrix4fv(viewID ,1,GL_FALSE, value_ptr(view ));
        glUniformMatrix4fv(projID ,1,GL_FALSE, value_ptr(proj));
        Wall.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    Wall.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}


