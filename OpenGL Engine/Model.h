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
	float* model;

	Model(float model[]);
	void generate_VBO();
	void generate_VAO();
	void bind_VAO();

};

// bude obsahovat vbo a vao

