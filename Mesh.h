#ifndef MESH_CLASS_H
#define MESH_CLASS_H
#include<glad/glad.h>
#include<string>
#include <iostream>
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Camera.h"
#include <fstream>
using namespace std;
class Mesh
{
public:
	string name = "no name";
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	VAO VAO;
	Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, string name);
	Mesh(string path, vector<Texture>& textures);
	Mesh();
	void Draw(Shader& shader, Camera& camera);
};

#endif 
