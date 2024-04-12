#ifndef MESHCONTAINER_CLASS_H
#define MESHCONTAINER_CLASS_H
#include <iostream>
#include <string>
#include"Mesh.h"
#include "ShaderClass.h"
#include"LightContainer.h"
class MeshContainer
{
public:
	
	vec3 Position;
	vec3 objectScale;
	vec3 objectRotation;
	mat4 objectModel;
	Mesh mesh;
	Shader shaderProgram;
	MeshContainer(vec3 pos, string path);
	MeshContainer();
	void Update(vector<LightContainer>& lights, Camera& camera);
	void destroy();

};
#endif

