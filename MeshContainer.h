#ifndef MESHCONTAINER_CLASS_H
#define MESHCONTAINER_CLASS_H
#include <iostream>
#include <string>
#include"Mesh.h"
#include "ShaderClass.h"
#include"LightContainer.h"
#include "HirObj.h"
class MeshContainer:public HirObj
{
public:
	
	Mesh mesh;
	Shader shaderProgram;
	MeshContainer(vec3 pos, string path);
	MeshContainer();
	void destroy();

	void Update(vector<LightContainer>& lights, Camera& camera);

};
#endif

