#include "MeshContainer.h"



MeshContainer::MeshContainer(vec3 pos, string path ) {
	MeshContainer::Position = pos;
	MeshContainer::objectScale = vec3(0.7f);
	MeshContainer::objectRotation = vec3(0);

	Texture textures[]{
		 Texture("planks.png","diffuse",0,GL_RGBA,GL_UNSIGNED_BYTE),
		 Texture("planksSpec.png","specular",1,GL_RED,GL_UNSIGNED_BYTE),
	};
	//shaderProgram = Shader("default.vert", "default.frag");
	vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	
	MeshContainer::mesh = Mesh(path, tex);

}
void MeshContainer::destroy() {

	shaderProgram.Delete();

}
void MeshContainer::Update(vec4& lightColor, vec3& lightPos, Camera& camera) {
	objectModel = translate(mat4(1.0f), Position);
	objectRotation.y = (float)glfwGetTime();
	objectModel = rotate(objectModel, objectRotation.x, vec3(1.0f, 0.0f, 0.0f));
	objectModel = rotate(objectModel, objectRotation.y, vec3(0.0f, 1.0f, 0.0f));
	objectModel = rotate(objectModel, objectRotation.z, vec3(0.0f, 0.0f, 1.0f));
	objectModel = scale(objectModel, objectScale);
	objectRotation.y += 90.0f;
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	mesh.Draw(shaderProgram,camera);
}


