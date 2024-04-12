#ifndef MESHCONTAINER_CLASS_H
#define MESHCONTAINER_CLASS_H
#include <iostream>
#include <string>
#include"Mesh.h"
#include "ShaderClass.h"
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
	void Update(vec4& lightColor, vec3& lightPos, Camera& camera);
	void destroy();

};
#endif

