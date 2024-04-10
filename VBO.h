#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<vector>
using namespace std;
using namespace glm;

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO(vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif 
