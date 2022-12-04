#pragma once

#include "Shader.h"

#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

class ShaderProgram
{
public:
	ShaderProgram();
	Shader CreateVertexShader(const char* vertex_shader_code);
	Shader CreateFragmentShader(const char* fragment_shader_code);
	std::string loadFile(const char* fname);
	void AttachShaders(const char* vertex_shader_code, const char* fragment_shader_code);
	void AttachShaders(GLuint vertex_shader, GLuint fragment_shader);
	void LinkProgram();
	void CheckLinkStatus();
	GLint GetUniformLocation();
	GLint GetUniformLocation(std::string name_of_variable);
	void UseProgram();
private:
	GLuint shader_program_id;
	GLint link_status;
};

