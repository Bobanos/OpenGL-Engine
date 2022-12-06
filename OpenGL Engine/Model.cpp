#include "Model.h"

Model::Model()
{
	Model::VBO = 0;
	Model::VAO = 0;
}

void Model::generate_VBO(const float model_data[], int size_of_data, int count)
{
	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_of_data, model_data, GL_STATIC_DRAW); // TODO

	Model::count_of_indices = count;
}

void Model::generate_VAO8()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glEnableVertexAttribArray(2); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),NULL); //Cordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(GLvoid*)(3 * sizeof(GLfloat))); //Normal
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(GLfloat))); //Texture uv
}

void Model::generate_VAO6()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL); //Cordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat))); //Normal
}

void Model::generate_skybox_VAO()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL); //Cordinates
}

void Model::bind_VAO()
{
	glBindVertexArray(VAO); //bind the VAO
}

GLsizei Model::GetCountOfIndices()
{
	return Model::count_of_indices;
}
