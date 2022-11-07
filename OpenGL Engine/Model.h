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

public:
	Model();

	void generate_VBO(float* model_data);
	void generate_VAO();
	void bind_VAO();

};

// bude obsahovat vbo a vao

