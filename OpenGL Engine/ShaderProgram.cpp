#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	ShaderProgram::shader_program_id = glCreateProgram();
}

Shader ShaderProgram::CreateVertexShader(const char* vertex_shader_code)
{
	Shader vertex_shader = new Shader(true);
	vertex_shader.setSource(vertex_shader_code);
	vertex_shader.compile();
	return vertex_shader;
}

Shader ShaderProgram::CreateFragmentShader(const char* fragment_shader_code)
{
	Shader fragment_shader = new Shader(true);
	fragment_shader.setSource(fragment_shader_code);
	fragment_shader.compile();
	return fragment_shader;
}

void ShaderProgram::AttachShaders(const char* vertex_shader_code, const char* fragment_shader_code)
{
	glAttachShader(ShaderProgram::shader_program_id, ShaderProgram::CreateVertexShader(vertex_shader_code).get_shader_id());
	glAttachShader(ShaderProgram::shader_program_id, ShaderProgram::CreateFragmentShader(fragment_shader_code).get_shader_id());
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(ShaderProgram::shader_program_id);
}

void ShaderProgram::CheckLinkStatus()
{
	glGetProgramiv(ShaderProgram::shader_program_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(ShaderProgram::shader_program_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(ShaderProgram::shader_program_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::UseProgram()
{
	glUseProgram(shader_program_id);
}
