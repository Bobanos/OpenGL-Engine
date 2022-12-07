#pragma once
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Texture.h"
#include "Camera.h"
#include "Skybox.h"


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

	struct model_shader_skybox {
		DrawableObject* drawableObject;
		ShaderProgram* shaderProgram;
		Skybox* skybox;
	};

	struct model_shader_texture_normalMap {
		DrawableObject* drawableObject;
		ShaderProgram* shaderProgram;
		Texture* texture;
		Texture* normalMap;
	};
	
	std::vector<model_shader> vectorOfModelsShaders;
	std::vector<model_shader_texture> vectorOfModelsShadersTextures;
	model_shader_skybox model_shader_skybox;
	std::vector<model_shader_texture_normalMap> vectorOfModelsShadersTexturesNormals;

	Camera* camera;



	int vecSize;

	Scene(int width, int height);
	Scene(int width, int height, glm::vec3 cameraPosition, glm::vec3 cameraOrientation);
	void AddToVectorModelsShaders(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram);
	void AddToVectorModelsShadersTextures(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Texture* receivedTexture);
	void AddToVectorModelsShadersTexturesNormals(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Texture* receivedTexture, Texture* receivedNormalMap);
	void AddSkybox(DrawableObject* receivedDrawableObject, ShaderProgram* receivedShaderProgram, Skybox* receivedSkybox);
	void DrawAllObjects();
	void DrawAllBalls();
	void DrawAllObjectsWithSkybox();
};

