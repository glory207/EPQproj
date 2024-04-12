#ifndef HIERARCHY_CLASS_H
#define HIERARCHY_CLASS_H
#include <iostream>
#include <string>
#include"MeshContainer.h"
#include"LightContainer.h"
using namespace glm;
using namespace std;

class Hierarchy {
public:
	vector<MeshContainer> meshes;
	vector<LightContainer> lights;

	string TempMeshe;
	vec4 TempLight;
	Hierarchy();
	void Update(Camera& camera);
	bool shouldAdd[2];
	void AddMesh(string msh);
	void AddLight(vec3 col);
	void DeleteMesh(int x);
	void DeleteLight(int x);
	void destroy();


};



#endif