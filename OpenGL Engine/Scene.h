#pragma once
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"


class Scene
{
public:
	struct model_shader {
		DrawableObject *drawableObject;
		ShaderProgram *shaderProgram;
	};
	
	std::vector<model_shader> vectorOfModels;

	Camera* camera; //TODO might be wrong

	Scene(int width, int height);
	void AddToVector(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram);
	void DrawAllObjects();

};

