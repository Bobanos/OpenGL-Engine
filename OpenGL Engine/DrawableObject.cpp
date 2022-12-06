#include "DrawableObject.h"

//Include GLM  
#include "glm/glm.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

DrawableObject::DrawableObject(Model* model) 
{
	DrawableObject::model = model;
	DrawableObject::modelMatrix = glm::mat4(1.0f);
}

void DrawableObject::UniformMatrix4fv(GLint id)
{
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(DrawableObject::modelMatrix));
}

void DrawableObject::Rotate(float angle_in_degrees, glm::vec3 axes) 
{
	DrawableObject::modelMatrix = glm::rotate(DrawableObject::modelMatrix, glm::radians(angle_in_degrees), axes);
}

void DrawableObject::Scale(glm::vec3 scale) 
{
	DrawableObject::modelMatrix = glm::scale(DrawableObject::modelMatrix, scale);
}

void DrawableObject::Translate(glm::vec3 translate) 
{
	DrawableObject::modelMatrix = glm::translate(DrawableObject::modelMatrix, translate);
}

void DrawableObject::ClearModelMatrix()
{
	DrawableObject::modelMatrix = glm::mat4(1.0f);
}

void DrawableObject::DrawArrays()
{
	glDrawArrays(GL_TRIANGLES, 0, DrawableObject::model->GetCountOfIndices());
}
