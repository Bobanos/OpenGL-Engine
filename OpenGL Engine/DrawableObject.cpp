#include "DrawableObject.h"

//Include GLM  
#include "glm/glm.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

DrawableObject::DrawableObject(Model* model) {
	DrawableObject::model = model;
	DrawableObject::modelMatrix = glm::mat4(1.0f);
	printf("############################\n");
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[0][0], DrawableObject::modelMatrix[0][1], DrawableObject::modelMatrix[0][2], DrawableObject::modelMatrix[0][3]);
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[1][0], DrawableObject::modelMatrix[1][1], DrawableObject::modelMatrix[1][2], DrawableObject::modelMatrix[1][3]);
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[2][0], DrawableObject::modelMatrix[2][1], DrawableObject::modelMatrix[2][2], DrawableObject::modelMatrix[2][3]);
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[3][0], DrawableObject::modelMatrix[3][1], DrawableObject::modelMatrix[3][2], DrawableObject::modelMatrix[3][3]);
}

void DrawableObject::UniformMatrix4fv(GLint id)
{
	printf("############################\n");
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[0][0], DrawableObject::modelMatrix[0][1], DrawableObject::modelMatrix[0][2], DrawableObject::modelMatrix[0][3]);
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[1][0], DrawableObject::modelMatrix[1][1], DrawableObject::modelMatrix[1][2], DrawableObject::modelMatrix[1][3]);
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[2][0], DrawableObject::modelMatrix[2][1], DrawableObject::modelMatrix[2][2], DrawableObject::modelMatrix[2][3]);
	printf("%f %f %f %f\n", DrawableObject::modelMatrix[3][0], DrawableObject::modelMatrix[3][1], DrawableObject::modelMatrix[3][2], DrawableObject::modelMatrix[3][3]);
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(DrawableObject::modelMatrix)); //TODO may replace last paramater with value_ptr
}

void DrawableObject::Rotate(float angle_in_degrees, glm::vec3 axes) {
	DrawableObject::modelMatrix = glm::rotate(DrawableObject::modelMatrix, glm::radians(angle_in_degrees), axes);
}

void DrawableObject::Scale(glm::vec3 scale) {
	DrawableObject::modelMatrix = glm::scale(DrawableObject::modelMatrix, scale);
}

void DrawableObject::Translate(glm::vec3 translate) {
	DrawableObject::modelMatrix = glm::translate(DrawableObject::modelMatrix, translate);
}

void DrawableObject::DrawArrays()
{
	glDrawArrays(GL_TRIANGLES, 0, DrawableObject::model->GetCountOfIndices());
}
