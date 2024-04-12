#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNorm;
    layout (location = 2) in vec3 aColor;
    layout (location = 3) in vec2 aTPos;
     uniform mat4 camMatrix;
     uniform mat4 model;
     
out DATA
{
    vec3 Normal;
	vec3 color;
	vec2 texCoord;
    mat4 projection;
} data_out;


void main()
{
    data_out.Normal = aNorm;
   gl_Position = model * vec4(aPos,1.0f);
   data_out.color = aColor;
   data_out.texCoord = aTPos;
   data_out.projection = camMatrix;
   
}