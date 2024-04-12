#ifndef LIGHTCONTAINER_CLASS_H
#define LIGHTCONTAINER_CLASS_H
#include <iostream>
#include <string>
#include"Mesh.h"
#include "ShaderClass.h"
class LightContainer
{
public:

	vec3 Position;
	vec3 objectScale;
	vec3 objectRotation;
	vec4 lightColor;
	mat4 objectModel;
	Mesh mesh;
	Shader shaderProgram;
	LightContainer(vec3 pos,vec4 color);
	LightContainer();
	void Update(Camera& camera);
	void destroy();

};
#endif