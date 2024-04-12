#include <iostream>
#include <string>
#include "Hierarchy.h"
#include<thread>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
string vts(vec3 v)
{
    return "x:" + to_string(v.x) + " y:" + to_string(v.y) + " z:" + to_string(v.z);
};
string vts(vec2 v)
{
    return "x:" + to_string(v.x) + " y:" + to_string(v.y);
};
vec3 setV3()
{
    vec3 x;
    cout << "x = ";
    cin >> x.x;
    cout << "y = ";
    cin >> x.y;
    cout << "z = ";
    cin >> x.z;
    return x;
};

void setMesh(MeshContainer& mesh)
{

    cout << "1.pos " << vts(mesh.Position) << endl;
    cout << "2.rot " << vts(mesh.objectRotation) << endl;
    cout << "3.sca " << vts(mesh.objectScale) << endl;
    int y;
    cin >> y;

    vec3 x = setV3();
    switch (y)
    {
    case 1:
        mesh.Position = x;
        break;
    case 2:
        mesh.objectRotation = x;
        break;
    case 3:
        mesh.objectScale = x;
        break;
    }
    
};
void setMesh(LightContainer& mesh)
{

    cout << "1.pos " << vts(mesh.Position) << endl;
    cout << "2.rot " << vts(mesh.objectRotation) << endl;
    cout << "3.sca " << vts(mesh.objectScale) << endl;
    cout << "4.col " << vts(vec3(mesh.lightColor)) << endl;
    int y;
    cin >> y;

    vec3 x = setV3();
    switch (y)
    {
    case 1:
        mesh.Position = x;
        break;
    case 2:
        mesh.objectRotation = x;
        break;
    case 3:
        mesh.objectScale = x;
        break;
    case 4:
        mesh.lightColor = vec4(x,1);
        break;
    }

};
void Dbg(Hierarchy& scene, bool close)
{
    while (close)
    {
       // system("CLS");
        cout << "menue" << endl;
        cout << "1.meshs" << endl;
        cout << "2.lights" << endl;
        int x;
        string a;
        cin >> x;
        system("CLS");
        if (x == 1)
        {
            cout << "e - edit" << endl;
            cout << "a - add" << endl;
            cout << "d - delet" << endl;
            for (int i = 0; i < scene.meshes.size(); i++) {
                cout << i << ".mesh" << endl;
            }

            cin >> a;
            if (a == "e")
            {
                cout << "select ";
                cin >> x;
                setMesh(scene.meshes[x]);
            }
            else if(a == "a")
            {
                cout << "Cube.txt" << endl;
                cout << "opy.txt" << endl;
                cin >> a;
                scene.AddMesh(a);
            }
            else if(a == "d")
            {
                cout << "select ";
                cin >> x;
                scene.DeleteMesh(x);
            }

            

        }
        else if (x == 2)
        {
            cout << "e - edit" << endl;
            cout << "a - add" << endl;
            cout << "d - delet" << endl;
            for (int i = 0; i < scene.lights.size(); i++) {
                cout << i << ".light" << endl;
            }
            cin >> a;
            if (a == "e")
            {
                cout << "select ";
                cin >> x;
                setMesh(scene.lights[x]);
            }
            else if (a == "a")
            {
                scene.AddLight(setV3());
            }
            else if (a == "d")
            {
                cout << "select ";
                cin >> x;
                scene.DeleteLight(x);
            }
        }



    }
};

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


    Hierarchy scene;
    

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(SCR_WIDTH, SCR_HEIGHT,vec3(0.0f,0.0f,2.0f));
   
    double preTime = 0.0;
    double curTime = 0.0;
    double timeDif;
    unsigned int counter = 0;
    thread debuger(Dbg,ref(scene), !glfwWindowShouldClose(window));
    
    
    while (!glfwWindowShouldClose(window))
    {


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

        scene.Update(camera);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    debuger.detach();
    scene.destroy();
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


