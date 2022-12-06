#pragma once
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Texture.h"
#include "Camera.h"


class Scene
{
public:
	struct model_shader {
		DrawableObject *drawableObject;
		ShaderProgram *shaderProgram;
	};

	struct model_shader_texture {
		DrawableObject* drawableObject;
		ShaderProgram* shaderProgram;
		Texture* texture;
	};
	
	std::vector<model_shader> vectorOfModelsShaders;
	std::vector<model_shader_texture> vectorOfModelsShadersTextures;

	Camera* camera;

	int vecSize;

	Scene(int width, int height);
	void AddToVectorModelsShaders(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram);
	void AddToVectorModelsShadersTextures(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Texture* receivedTexture);
	void DrawAllObjects();
};

