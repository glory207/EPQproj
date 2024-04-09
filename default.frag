#version 330 core
    out vec4 FragColor;
     in vec3 color;
     uniform vec4 lightColor;
     uniform vec3 lightPos;
     uniform vec3 camPos;
    in vec3 norm;
    in vec3 crntPos;
    in vec2 TPos;
    uniform sampler2D tex0;
    uniform sampler2D tex1;
    void main()
    {
    float ambient = 1.0f;
        vec3 normal = normalize(norm);
        vec3 lightDir = normalize(lightPos - crntPos);

        float diffuse = max(dot(normal, lightDir), 0.0f) ;

        float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight * 5;


    FragColor = texture(tex0, TPos) * lightColor * (diffuse + ambient +  (texture(tex1, TPos).r * specular ) );


      // FragColor = texture(tex0, TPos)  * lightColor * (( texture(tex0, TPos).r * specular));
      //FragColor = vec4(color, 1.0f);
     // FragColor = texture(tex0, TPos);
    }