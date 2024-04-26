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
	vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO(vector<Vertex>& vertices);
	VBO(vector<float>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif 
