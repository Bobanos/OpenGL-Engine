#pragma once

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	Shader CreateVertexShader(const char* vertex_shader_code);
	Shader CreateFragmentShader(const char* fragment_shader_code);
	void AttachShaders(const char* vertex_shader_code, const char* fragment_shader_code);
	void AttachShaders(GLuint vertex_shader, GLuint fragment_shader);
	void LinkProgram();
	void CheckLinkStatus();
	void UseProgram();
private:
	GLuint shader_program_id;
	GLint link_status;
};

