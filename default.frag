#version 330 core
    out vec4 FragColor;
     in vec3 color;
     uniform vec4 lightColor;
     uniform vec3 lightPos;
     uniform vec3 camPos;
    in vec3 norm;
    in vec3 crntPos;
    in vec2 TPos;
    uniform sampler2D diffuse0;
    uniform sampler2D specular0;
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
	float specular = specAmount * specularLight;


    FragColor = texture(diffuse0, TPos) * lightColor * (diffuse + ambient +  ((texture(specular0, TPos).r * 4) * specular ) );


      // FragColor = texture(diffuse0, TPos)  * lightColor * (( texture(specular0, TPos).r * specular));
      //FragColor = vec4(color, 1.0f);
     // FragColor = texture(tex0, TPos);
    }