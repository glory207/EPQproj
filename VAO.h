#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include<glad/glad.h>
#include"VBO.h"
using namespace std;
class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO VBO,GLuint layout);
	void Bind();
	void Unbind();
	void Delete();
};

#endif 
