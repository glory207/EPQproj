#include "MeshContainer.h"



MeshContainer::MeshContainer(vec3 pos, string path ) {
	Position = pos;
	objectScale = vec3(1.0f);
	objectRotation = vec3(0);

	Texture textures[]{
		 Texture("Res/planks.png","diffuse",0,GL_RGBA,GL_UNSIGNED_BYTE),
		 Texture("Res/planksSpec.png","specular",1,GL_RED,GL_UNSIGNED_BYTE),
	};
	//shaderProgram = Shader("default.vert", "default.frag");
	vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	
	MeshContainer::mesh = Mesh(path, tex);

}
MeshContainer::MeshContainer() {
	MeshContainer::Position = vec3(0);
	MeshContainer::objectScale = vec3(1.0f);
	MeshContainer::objectRotation = vec3(0);


}
void MeshContainer::destroy() {

	shaderProgram.Delete();

}
void MeshContainer::Update(vector<LightContainer>& lights, Camera& camera) {
	objectModel = translate(mat4(1.0f), Position);
	objectModel = rotate(objectModel, objectRotation.x, vec3(1.0f, 0.0f, 0.0f));
	objectModel = rotate(objectModel, objectRotation.y, vec3(0.0f, 1.0f, 0.0f));
	objectModel = rotate(objectModel, objectRotation.z, vec3(0.0f, 0.0f, 1.0f));
	objectModel = scale(objectModel, objectScale);
	objectRotation.y += 90.0f;
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, value_ptr(objectModel));
	glUniform1i(glGetUniformLocation(shaderProgram.ID, "lightnum"), lights.size());
	for (int i = 0; i < lights.size(); i++)
	{
		string ii = "lightColor[" + to_string(i) + "]";
		glUniform4f(glGetUniformLocation(shaderProgram.ID, ii.c_str()), lights[i].lightColor.x, lights[i].lightColor.y, lights[i].lightColor.z, lights[i].lightColor.w);
		ii = "lightPos[" + to_string(i) + "]";
		glUniform3f(glGetUniformLocation(shaderProgram.ID, ii.c_str()), lights[i].Position.x, lights[i].Position.y, lights[i].Position.z);

		ii = "lightRot[" + to_string(i) + "]";
		glUniform3f(glGetUniformLocation(shaderProgram.ID, ii.c_str()), lights[i].objectRotation.x, lights[i].objectRotation.y, lights[i].objectRotation.z);

	}
	mesh.Draw(shaderProgram,camera);
}


