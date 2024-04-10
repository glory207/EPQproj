#include <iostream>
#include <string>
#include"Mesh.h"
using namespace glm;
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

Vertex vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
 Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};
Vertex lightVertices[] =
{ //     COORDINATES     //
  Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
   

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


    Texture textures[]{
         Texture("planks.png","diffuse",0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    Shader shaderProgram("default.vert", "default.frag");
    vector<Vertex> verts(vertices, vertices + sizeof(vertices)/ sizeof(Vertex));
    vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    //Mesh floor(verts, ind, tex, "floor");
    Mesh floor("Cube.txt",tex);
    Shader lightShader("light.vert", "light.frag");

    vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
   // vector<Texture> lightTex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh light(lightVerts, lightInd, tex, "light");
   

    vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec3 lightPos = vec3(0.8f, 0.8f, 0.8f);
    mat4 lightModel = mat4(1.0f);
    lightModel = translate(lightModel, lightPos);

    vec3 objectPos = vec3(0.0f, -0.1f, 0.0f);
    mat4 objectModel = mat4(1.0f);
    objectModel = translate(objectModel, objectPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);




    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(SCR_WIDTH, SCR_HEIGHT,vec3(0.0f,0.0f,2.0f));
   
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
       
        floor.Draw(shaderProgram,camera);
        light.Draw(lightShader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport((width- height) * 0.5, 0, height, height);
}


