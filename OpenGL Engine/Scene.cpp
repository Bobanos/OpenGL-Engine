#include "Scene.h"

Scene::Scene() {

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
	unsigned int vecSize = vectorOfModels.size();
	for (int i = 0; i < vecSize; i++) 
	{
		vectorOfModels[i].shaderProgram->UseProgram();
		vectorOfModels[i].drawableObject->model->bind_VAO();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}
