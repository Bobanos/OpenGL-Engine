#pragma once
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"


class Scene
{
public:
	struct model_shader {
		DrawableObject *drawableObject;
		ShaderProgram *shaderProgram;
	};
	
	std::vector<model_shader> vectorOfModels;

	Scene();
	void AddToVector(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram);
	void DrawAllObjects();
};

