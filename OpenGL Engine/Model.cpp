#include "Model.h"

Model::Model()
{
	Model::VBO = 0;
	Model::VAO = 0;
}

void Model::generate_VBO(const float model_data[], int size_of_data)
{

	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_of_data, model_data, GL_STATIC_DRAW); // TODO
}

void Model::generate_VAO()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float),NULL); //Cordinates
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(GLvoid*)(4 * sizeof(GLfloat))); //Color
}

void Model::bind_VAO()
{
	glBindVertexArray(VAO); //bind the VAO
}
