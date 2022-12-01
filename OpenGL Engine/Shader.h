#pragma once

//Include GLEW
#include <GL/glew.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string>

class Shader
{
public:
	Shader(bool is_fragment);
	void setSource(const char* shader_code);
	void compile();
	void checkCompileStatus();
	GLuint get_shader_id();
private:
	std::string shader_type;
	GLuint shader_id;
	GLint compile_status;
};

