#version 330 core
    out vec4 FragColor;
     uniform vec4 lightColor[50];
     uniform vec3 lightPos[50];
     uniform int lightnum;
     uniform vec3 camPos;
    in vec3 norm;
    in vec3 crntPos;
    in vec2 TPos;
    uniform sampler2D diffuse0;
    uniform sampler2D specular0;

  
    vec4 pointLight(vec3 lPos,vec4 lColor)
{	
	vec3 lightVec = lPos - crntPos;

	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 20.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.07f;

	vec3 norm = normalize(norm);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(norm, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, norm);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, TPos) * (diffuse * inten + ambient) + texture(specular0, TPos).r * specular * inten) * lColor;
}
    void main()
    {
    
	vec4 CombinedLight;
	for(int i = 0 ; i < lightnum; i++)
	{
	CombinedLight += (pointLight(lightPos[i],lightColor[i]));
	}
    FragColor = CombinedLight;


    }
    

