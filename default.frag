#version 330 core
    out vec4 FragColor;
     in vec3 color;
    in vec2 TPos;
    uniform sampler2D tex0;
    void main()
    {
       //FragColor = (texture(tex0, TPos) + vec4(color, 1.0f)) / 2f;
      //FragColor = vec4(color, 1.0f);
      FragColor = texture(tex0, TPos);
    }