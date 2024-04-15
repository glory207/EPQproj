#include <iostream>
#include <string>
#include "Hierarchy.h"
#include<thread>
#include"imgui.h"
#include"imgui_impl_opengl3.h"
#include"imgui_impl_glfw.h"



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
   // thread debuger(Dbg,ref(scene), !glfwWindowShouldClose(window));
    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

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
        

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (!io.WantCaptureMouse)
        {
            camera.inputs(window);
        }
        
        
        camera.updateMatrix(45.0f, 0.1f, 100.0f, SCR_WIDTH, SCR_HEIGHT);

        scene.Update(camera);
        
        ImGui::Begin("add meshes");
       // ImGui::CheckboxFlags("io.ConfigFlags: DockingEnable", &io.ConfigFlags, ImGuiConfigFlags_DockingEnable);
        if (ImGui::TreeNode("meshes")) {
            if (ImGui::Button("add circle"))
            {
                scene.AddMesh("Cube.txt");
            }
            if (ImGui::Button("add opy"))
            {
                scene.AddMesh("opy.txt");
            }
            for (int i = 0; i < scene.meshes.size(); i++)
            {
                string pos;
                pos = scene.meshes[i].mesh.name.c_str() + to_string(i);
                if (ImGui::TreeNode(pos.c_str())) {
                    pos = "delete" + to_string(i);
                    if (ImGui::Button(pos.c_str()))
                    {
                         
                        scene.DeleteMesh(i);
                    }
                    pos = "pos ##" + to_string(i);
                    if (ImGui::TreeNode(pos.c_str())) {
                        ImGui::DragFloat("pos X", &scene.meshes[i].Position.x, 0.01f);
                        ImGui::DragFloat("pos Y", &scene.meshes[i].Position.y, 0.01f);
                        ImGui::DragFloat("pos Z", &scene.meshes[i].Position.z, 0.01f);
                        ImGui::TreePop();
                    }
                    pos = "rot ##" + to_string(i);
                    if (ImGui::TreeNode(pos.c_str())) {
                        ImGui::DragFloat("rot X", &scene.meshes[i].objectRotation.x, 0.01f);
                        ImGui::DragFloat("rot Y", &scene.meshes[i].objectRotation.y, 0.01f);
                        ImGui::DragFloat("rot Z", &scene.meshes[i].objectRotation.z, 0.01f);
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("light")) {
            if (ImGui::Button("add light"))
            {
                scene.AddLight(vec3(1));
            }
            for (int i = 0; i < scene.lights.size(); i++)
            {
                string pos;
                
                
                pos = "light" + to_string(i);
                if (ImGui::TreeNode(pos.c_str())) {
                    pos = "delete" + to_string(i);
                    if (ImGui::Button(pos.c_str()))
                    {
                         
                        scene.DeleteLight(i);
                    }
                    pos = "pos ##" + to_string(i);
                    if (ImGui::TreeNode(pos.c_str())) {
                        ImGui::DragFloat("pos X", &scene.lights[i].Position.x, 0.01f);
                        ImGui::DragFloat("pos Y", &scene.lights[i].Position.y, 0.01f);
                        ImGui::DragFloat("pos Z", &scene.lights[i].Position.z, 0.01f);
                        ImGui::TreePop();
                    }
                    pos = "color ##" + to_string(i);
                    if (ImGui::TreeNode(pos.c_str())) {
                        ImGui::DragFloat("R", &scene.lights[i].lightColor.x, 0.001f,0, 1);
                        ImGui::DragFloat("G", &scene.lights[i].lightColor.y, 0.001f,0, 1);
                        ImGui::DragFloat("B", &scene.lights[i].lightColor.z, 0.001f,0, 1);
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        ImGui::End();
       // ImGui::Begin("viewport"); 
       // ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
       // ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
       // ImGui::End();
       // ImGui::ShowDemoWindow();

        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
   // debuger.detach();
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


