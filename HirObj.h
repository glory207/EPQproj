#ifndef HIROBJ_CLASS_H
#define HIROBJ_CLASS_H
#include <iostream>
#include <string>
#include"Mesh.h"
#include "ShaderClass.h"
#include"LightContainer.h"
class HirObj
{
public:

	vec3 Position;
	vec3 objectScale;
	vec3 objectRotation;
	mat4 objectModel;
	HirObj();
	void destroy();
	virtual void Update(vector<LightContainer>& lights, Camera& camera) = 0;

};
#endif

