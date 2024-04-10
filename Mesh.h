#ifndef MESH_CLASS_H
#define MESH_CLASS_H
#include<glad/glad.h>
#include<string>

#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Camera.h"
using namespace std;
class Mesh
{
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	VAO VAO;
	Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures);
	void Draw(Shader& shader, Camera& camera);
};

#endif 
