#include "LightContainer.h"



LightContainer::LightContainer(vec3 pos,vec4 color) {
	LightContainer::Position = pos;
	LightContainer::lightColor = color;
	LightContainer::objectScale = vec3(0.5f);

	shaderProgram = Shader("Res/light.vert", "Res/light.frag", "Res/light.geomertry");
	
	LightContainer::mesh = Mesh();

}
LightContainer::LightContainer() {
	LightContainer::Position = vec3(0,0,0);
	LightContainer::lightColor = vec4(1);
	LightContainer::objectScale = vec3(0.5f);

	shaderProgram = Shader("Res/light.vert", "Res/light.frag");
	Texture textures[]{
		 Texture(),
	};
	vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	LightContainer::mesh = Mesh("Res/Cube.txt", tex);

}
void LightContainer::destroy() {

	shaderProgram.Delete();

}
void LightContainer::Update(Camera& camera) {

	objectModel = translate(mat4(1.0f), Position);
	objectModel = scale(objectModel, objectScale);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "camUp"), camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
	mesh.Draw(shaderProgram, camera);
	
}


