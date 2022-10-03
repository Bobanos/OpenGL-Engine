#include "Model.h"




Model::Model(float model[])
{
	Model::VBO = 0;
	Model::VAO = 0;
	Model::model = model;
}

void Model::generate_VBO()
{
	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model), model, GL_STATIC_DRAW); //TODO
}

void Model::generate_VAO()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Model::bind_VAO()
{
	glBindVertexArray(VAO); //bind the VAO
}
