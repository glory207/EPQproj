#include "Hierarchy.h"

Hierarchy::Hierarchy() {

     meshes = {
        MeshContainer(vec3(0.0f,0.0f,0.0f), "Cube.txt"),

    };
     lights = { 
         LightContainer(vec3(-1.0f, 2.8f, 0.8f), vec4(1.0f, 0.0f, 0.0f, 1.0f)),
         LightContainer(vec3(1.0f, 2.8f, 0.8f), vec4(0.0f, 1.0f, 0.0f, 1.0f)),
         LightContainer(vec3(0.0f, 2.8f, 0.8f), vec4(0.0f, 0.0f, 1.0f, 1.0f)),
     };
     shouldAdd[0] = false;
     shouldAdd[1] = false;
}

void Hierarchy::AddMesh(string msh) {
    TempMeshe = msh;
    shouldAdd[0] = true;
}
void Hierarchy::AddLight(vec3 col)
{
    TempLight = vec4(col,1);
    shouldAdd[1] = true;
}
void Hierarchy::Update(Camera& camera){

   

    for (LightContainer light : lights)
    {
        light.Update(camera);
    }
    for (MeshContainer mesh : meshes)
    {
        mesh.Update(lights, camera);
    }
    if (shouldAdd[0])
    {
        shouldAdd[0] = false;
        meshes.push_back(MeshContainer(camera.Position, TempMeshe));
    }
    if (shouldAdd[1])
    {
        shouldAdd[1] = false;
        lights.push_back(LightContainer(camera.Position, TempLight));
    }
}
void Hierarchy::destroy() {
    for (LightContainer light : lights)
    {
        light.destroy();
    }
    for (MeshContainer mesh : meshes)
    {
        mesh.destroy();
    }
}
void Hierarchy::DeleteMesh(int pos)
{
    meshes[pos].destroy();
    meshes.erase(meshes.begin() + pos);
}
void Hierarchy::DeleteLight(int pos)
{
    lights[pos].destroy();
    lights.erase(lights.begin() + pos);
}