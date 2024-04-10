#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNorm;
    layout (location = 2) in vec3 aColor;
    layout (location = 3) in vec2 aTPos;
    out vec3 color;
    out vec3 norm;
    out vec3 crntPos;
    out vec2 TPos;
     uniform mat4 camMatrix;
     uniform mat4 model;


    void main()
    {
    norm = aNorm;
       crntPos = vec3(model * vec4(aPos,1.0f));
       gl_Position = camMatrix * vec4(crntPos, 1.0);
       color = aColor;
       TPos = aTPos;
       
    }