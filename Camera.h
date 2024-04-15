#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"ShaderClass.h"
using namespace std;
using namespace glm;

class Camera
{
public:
	vec3 Position;
	vec3 Orientation = vec3(0.0f,0.0,-1.0f);
	vec3 Up = vec3(0.0f,1.0,0.0f);
	mat4 cameraMatrix = mat4(1.0f);
	float width;
	float height;
	bool firstClick = true;
	float speed = 0.1f;
	float sensitivity = 100.0f;

	Camera(float width, float height, vec3 position);
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane, float wi, float he);
	void Matrix(Shader& shader,const char* uniform);
	void inputs(GLFWwindow* window);

};



#endif 

