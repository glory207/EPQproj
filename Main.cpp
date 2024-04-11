#include <iostream>
#include <string>
#include"Mesh.h"
#include"MeshContainer.h"
using namespace glm;
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

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
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));


    
    vector <MeshContainer> meshes = {
        MeshContainer(vec3(0), "Cube.txt"),
        MeshContainer(vec3(1), "Cube.txt"),
        MeshContainer(vec3(2), "Cube.txt"),
        MeshContainer(vec3(3), "Cube.txt"),
    
    };

    vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec3 lightPos = vec3(0.8f, 2.8f, 0.8f);
    mat4 lightModel = mat4(1.0f);
    lightModel = translate(lightModel, lightPos);



    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(SCR_WIDTH, SCR_HEIGHT,vec3(0.0f,0.0f,2.0f));
   
    double preTime = 0.0;
    double curTime = 0.0;
    double timeDif;
    unsigned int counter = 0;

    while (!glfwWindowShouldClose(window))
    {

       
        lightPos = vec3(sin((float)glfwGetTime()), 2.8f, 0.8f);
        lightModel = translate(mat4(1.0f), lightPos);
        
       

        curTime = glfwGetTime();
        timeDif = curTime - preTime;
        counter++;
        if (timeDif >= 1.0 / 30.0) {
            string FPS = to_string((int)((1.0 / timeDif) * counter));
            string ms = to_string((int)((timeDif/counter) * 1000));
            string title = "EPQ:  " + FPS + "FPS  " + ms + "ms";
            glfwSetWindowTitle(window, title.c_str());
            preTime = curTime;
            counter = 0;
        }


        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        for (MeshContainer mesh : meshes)
        {
            mesh.Update(lightColor, lightPos, camera);
        }
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (MeshContainer mesh : meshes)
    {
        mesh.destroy();
    }
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


