#pragma once

#include "Model.h"

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class DrawableObject
{
public:
	Model *model;
	DrawableObject(Model *model);
	void UniformMatrix4fv(GLint id);
	void Rotate(float angle, glm::vec3 axes);
	void Scale(glm::vec3 scale);
	void Translate(glm::vec3 translate);
	void DrawArrays();
private:
	glm::mat4 modelMatrix;
};

