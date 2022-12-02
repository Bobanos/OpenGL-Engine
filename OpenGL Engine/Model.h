#pragma once

//Include GLEW
#include <GL/glew.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

class Model
{
private:
	GLuint VBO;
	GLuint VAO;
	GLsizei count_of_indices;

public:
	Model();

	void generate_VBO(const float model_data[], int size_of_data, int count);
	void generate_VAO8();
	void generate_VAO6();
	void bind_VAO();

	GLsizei GetCountOfIndices();
};

// bude obsahovat vbo a vao

