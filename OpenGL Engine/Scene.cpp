#include "Scene.h"

Scene::Scene(int width, int height,	GLFWwindow* window, Model* treeModel, Texture* treeTexture, ShaderProgram* textureShader) {
	Scene::camera = new Camera(width, height, glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	Scene::window = window;

	Scene::treeModel = treeModel;
	Scene::treeTexture = treeTexture;
	Scene::treeTextureShader = textureShader;
}

Scene::Scene(int width, int height, GLFWwindow* window) {
	Scene::camera = new Camera(width, height, glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	Scene::window = window;

}

Scene::Scene(int width, int height, GLFWwindow* window, Model* treeModel, Texture* treeTexture, ShaderProgram* textureShader, glm::vec3 cameraPosition, glm::vec3 cameraOrientation) {
	Scene::camera = new Camera(width, height, cameraPosition, cameraOrientation); //broken for some reason
	Scene::window = window;

	Scene::treeModel = treeModel;
	Scene::treeTexture = treeTexture;
	Scene::treeTextureShader = textureShader;
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

void Scene::AddToVectorModelsShadersTexturesNormals(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Texture* receivedTexture, Texture* receivedNormalMap) 
{
	model_shader_texture_normalMap mstn;
	mstn.drawableObject = receivedDrawableObject;
	mstn.shaderProgram = receivedShaderProgram;
	mstn.texture = receivedTexture;
	mstn.normalMap = receivedNormalMap;
	vectorOfModelsShadersTexturesNormals.push_back(mstn);
}

void Scene::AddTreeToVectorModelsShadersTextures(glm::vec3 treePosition) 
{
	DrawableObject* drawableTreeGenerated = new DrawableObject(Scene::treeModel);
	drawableTreeGenerated->Translate(treePosition);
	Scene::AddToVectorModelsShadersTextures(drawableTreeGenerated, Scene::treeTextureShader, Scene::treeTexture);
}

void Scene::CheckForClick()
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !clicked)
	{
		clicked = true;
		int width, height;
		double dx, dy;
		int x, y;
		glfwGetFramebufferSize(window, &width, &height);
		glfwGetCursorPos(window, &dx, &dy);
		x = int(dx);
		y = int(dy);
		GLbyte color[4];
		GLfloat depth;
		GLuint index; // identifikace tìlesa
		int newy = height - y;
		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = camera->GetCameraView();
		glm::mat4 projection = camera->GetCameraProjection();
		glm::vec4 viewPort = glm::vec4(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

		Scene::AddTreeToVectorModelsShadersTextures(glm::vec3(pos.x, pos.y, pos.z));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) 
	{
		clicked = false;
	}
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
		Scene::camera->sendCameraPositionToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("cameraPosition"));
		Scene::camera->sendCameraOrientationToShaderProgram(vectorOfModelsShaders[i].shaderProgram->GetUniformLocation("cameraOrientation"));
		vectorOfModelsShaders[i].drawableObject->model->bind_VAO();
		vectorOfModelsShaders[i].drawableObject->DrawArrays();
	}

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

	vecSize = vectorOfModelsShadersTexturesNormals.size();
	for (int i = 0; i < vecSize; i++)
	{
		incrementor++;
		glStencilFunc(GL_ALWAYS, incrementor, 0xFF);
		vectorOfModelsShadersTexturesNormals[i].shaderProgram->UseProgram();
		vectorOfModelsShadersTexturesNormals[i].drawableObject->UniformMatrix4fv(vectorOfModelsShadersTexturesNormals[i].shaderProgram->GetUniformLocation("modelMatrix"));
		Scene::camera->sendCameraViewMatrixToShaderProgram(vectorOfModelsShadersTexturesNormals[i].shaderProgram->GetUniformLocation("viewMatrix"));
		Scene::camera->sendCameraProjectionMatrixToShaderProgram(vectorOfModelsShadersTexturesNormals[i].shaderProgram->GetUniformLocation("projectionMatrix"));
		Scene::camera->sendCameraPositionToShaderProgram(vectorOfModelsShadersTexturesNormals[i].shaderProgram->GetUniformLocation("cameraPos"));
		vectorOfModelsShadersTexturesNormals[i].texture->Uniform1i(vectorOfModelsShadersTexturesNormals[i].shaderProgram->GetUniformLocation("UIAlbedo"));
		vectorOfModelsShadersTexturesNormals[i].normalMap->Uniform1i(vectorOfModelsShadersTexturesNormals[i].shaderProgram->GetUniformLocation("UINormal"));
		vectorOfModelsShadersTexturesNormals[i].drawableObject->model->bind_VAO();
		vectorOfModelsShadersTexturesNormals[i].drawableObject->DrawArrays();
	}


}
