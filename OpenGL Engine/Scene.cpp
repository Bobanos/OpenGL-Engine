#include "Scene.h"

Scene::Scene(int width, int height) {
	Scene::camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f)); //TODO might be wrong
}

void Scene::AddToVector(DrawableObject *receivedDrawableObject, ShaderProgram *receivedShaderProgram)
{
	model_shader model_shader_to_push;
	model_shader_to_push.drawableObject = receivedDrawableObject;
	model_shader_to_push.shaderProgram = receivedShaderProgram;
	vectorOfModels.push_back(model_shader_to_push);
}

void Scene::DrawAllObjects()
{
	int vecSize = vectorOfModels.size();
	for (int i = 0; i < vecSize; i++) 
	{
		vectorOfModels[i].shaderProgram->UseProgram();
		vectorOfModels[i].drawableObject->UniformMatrix4fv(vectorOfModels[i].shaderProgram->GetUniformLocation("modelMatrix"));
		Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModels[i].shaderProgram->GetUniformLocation("viewMatrix"));
		Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModels[i].shaderProgram->GetUniformLocation("projectionMatrix"));
		vectorOfModels[i].drawableObject->model->bind_VAO();
		vectorOfModels[i].drawableObject->DrawArrays();
	}
}
