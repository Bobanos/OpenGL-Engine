#include "Scene.h"

Scene::Scene(int width, int height) {
	Scene::camera = new Camera(width, height, glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
}

Scene::Scene(int width, int height, glm::vec3 cameraPosition, glm::vec3 cameraOrientation) {
	Scene::camera = new Camera(width, height, cameraPosition, cameraOrientation); //broken for some reason
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

void Scene::AddSkybox(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Skybox* receivedSkybox)
{
	Scene::model_shader_skybox.drawableObject = receivedDrawableObject;
	Scene::model_shader_skybox.shaderProgram = receivedShaderProgram;
	Scene::model_shader_skybox.skybox = receivedSkybox;
}

void Scene::DrawAllBalls()
{
	vecSize = vectorOfModelsShaders.size();
	for (int i = 0; i < vecSize; i++)
	{
		vectorOfModelsShaders[i].shaderProgram->UseProgram();
		vectorOfModelsShaders[i].drawableObject->UniformMatrix4fv(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("modelMatrix"));
		Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("viewMatrix"));
		Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("projectionMatrix"));
		Scene::camera->sendCameraPositionToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("cameraPos"));
		vectorOfModelsShaders[i].drawableObject->model->bind_VAO();
		vectorOfModelsShaders[i].drawableObject->DrawArrays();
	}
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

	//vecSize = vectorOfModelsShadersTextures.size();
	//for (int i = 0; i < vecSize; i++)
	//{
	//	vectorOfModelsShadersTextures[i].shaderProgram->UseProgram();
	//	vectorOfModelsShadersTextures[i].drawableObject->UniformMatrix4fv(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("modelMatrix"));
	//	Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("viewMatrix"));
	//	Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("projectionMatrix"));
	//	vectorOfModelsShadersTextures[i].texture->Uniform1i(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("textureUnitID"));
	//	vectorOfModelsShadersTextures[i].drawableObject->model->bind_VAO();
	//	vectorOfModelsShadersTextures[i].drawableObject->DrawArrays();
	//}
}

void Scene::DrawAllObjectsWithSkybox()
{ 
	int incrementor = 1;
	glStencilFunc(GL_ALWAYS, incrementor, 0xFF);
	Scene::model_shader_skybox.drawableObject->ClearModelMatrix();
	Scene::model_shader_skybox.drawableObject->Translate(Scene::camera->GetCameraPosition());

	Scene::model_shader_skybox.shaderProgram->UseProgram();
	Scene::model_shader_skybox.drawableObject->UniformMatrix4fv(Scene::model_shader_skybox.shaderProgram->GetUniformLocation("modelMatrix"));
	Scene::camera->sendCameraViewMatrixToShaderProgram(Scene::model_shader_skybox.shaderProgram->GetUniformLocation("viewMatrix"));
	Scene::camera->sendCameraProjectionMatrixToShaderProgram(Scene::model_shader_skybox.shaderProgram->GetUniformLocation("projectionMatrix"));
	Scene::model_shader_skybox.skybox->Uniform1i(Scene::model_shader_skybox.shaderProgram->GetUniformLocation("skybox"));
	Scene::model_shader_skybox.drawableObject->model->bind_VAO();
	Scene::model_shader_skybox.drawableObject->DrawArrays();

	glClear(GL_DEPTH_BUFFER_BIT);

	vecSize = vectorOfModelsShaders.size();
	for (int i = 0; i < vecSize; i++)
	{
		incrementor++;
		glStencilFunc(GL_ALWAYS, incrementor, 0xFF);
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
		incrementor++;
		glStencilFunc(GL_ALWAYS, incrementor, 0xFF);
		vectorOfModelsShadersTextures[i].shaderProgram->UseProgram();
		vectorOfModelsShadersTextures[i].drawableObject->UniformMatrix4fv(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("modelMatrix"));
		Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("viewMatrix"));
		Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("projectionMatrix"));
		vectorOfModelsShadersTextures[i].texture->Uniform1i(vectorOfModelsShadersTextures[i].shaderProgram->GetUniformLocation("textureUnitID"));
		vectorOfModelsShadersTextures[i].drawableObject->model->bind_VAO();
		vectorOfModelsShadersTextures[i].drawableObject->DrawArrays();
	}


}
