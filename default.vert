#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTPos;
    layout (location = 2) in vec3 aColor;
    out vec3 color;
    out vec2 TPos;
     uniform float scale;
    void main()
    {
       gl_Position = vec4(vec3(aPos.x, aPos.y, aPos.z) + vec3(aPos.x, aPos.y, aPos.z) * scale, 1.0);
       color = aColor;
       TPos = aTPos;
    }