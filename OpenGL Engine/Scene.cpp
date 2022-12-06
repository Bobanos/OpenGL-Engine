#include "Scene.h"

Scene::Scene(int width, int height) {
	Scene::camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f)); //TODO might be wrong
}

void Scene::AddToVectorModelsShaders(DrawableObject *receivedDrawableObject, ShaderProgram *receivedShaderProgram)
{
	model_shader model_shader_to_push;
	model_shader_to_push.drawableObject = receivedDrawableObject;
	model_shader_to_push.shaderProgram = receivedShaderProgram;
	vectorOfModelsShaders.push_back(model_shader_to_push);
}

void Scene::AddToVectorModelsShadersTextures(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Texture* receivedTexture)
{
	model_shader_texture model_shader_texture_to_push;
	model_shader_texture_to_push.drawableObject = receivedDrawableObject;
	model_shader_texture_to_push.shaderProgram = receivedShaderProgram;
	model_shader_texture_to_push.texture = receivedTexture;
	vectorOfModelsShadersTextures.push_back(model_shader_texture_to_push);
}

void Scene::DrawAllObjects()
{
	vecSize = vectorOfModelsShaders.size();
	for (int i = 0; i < vecSize; i++) 
	{
		vectorOfModelsShaders[i].shaderProgram->UseProgram();
		vectorOfModelsShaders[i].drawableObject->UniformMatrix4fv(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("modelMatrix"));
		Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("viewMatrix"));
		Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("projectionMatrix"));
		vectorOfModelsShaders[i].drawableObject->model->bind_VAO();
		vectorOfModelsShaders[i].drawableObject->DrawArrays();
	}

	vecSize = vectorOfModelsShadersTextures.size();
	for (int i = 0; i < vecSize; i++)
	{
		vectorOfModelsShadersTextures[i].shaderProgram->UseProgram();
		vectorOfModelsShadersTextures[i].drawableObject->UniformMatrix4fv(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("modelMatrix"));
		Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("viewMatrix"));
		Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("projectionMatrix"));
		vectorOfModelsShadersTextures[i].texture->Uniform1i(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("textureUnitID"));
		vectorOfModelsShadersTextures[i].drawableObject->model->bind_VAO();
		vectorOfModelsShadersTextures[i].drawableObject->DrawArrays();
	}


}
