#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	ShaderProgram::shader_program_id = glCreateProgram();
}

Shader ShaderProgram::CreateVertexShader(const char* vertex_shader_code)
{
	Shader vertex_shader(false);
	vertex_shader.setSource(vertex_shader_code);
	vertex_shader.compile();
	return vertex_shader;
}

Shader ShaderProgram::CreateFragmentShader(const char* fragment_shader_code)
{
	Shader fragment_shader(true);
	fragment_shader.setSource(fragment_shader_code);
	fragment_shader.compile();
	return fragment_shader;
}

void ShaderProgram::AttachShaders(const char* vertex_shader_code, const char* fragment_shader_code)
{
	Shader vertex_shader = CreateVertexShader(vertex_shader_code);
	Shader fragment_shader = CreateFragmentShader(fragment_shader_code);
	glAttachShader(ShaderProgram::shader_program_id, vertex_shader.get_shader_id());
	glAttachShader(ShaderProgram::shader_program_id, fragment_shader.get_shader_id());
}

void ShaderProgram::AttachShaders(GLuint vertex_shader, GLuint fragment_shader)
{
	glAttachShader(ShaderProgram::shader_program_id, vertex_shader);
	glAttachShader(ShaderProgram::shader_program_id, fragment_shader);
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(ShaderProgram::shader_program_id);
}

void ShaderProgram::CheckCompileStatus()
{
	glGetProgramiv(ShaderProgram::shader_program_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(ShaderProgram::shader_program_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(ShaderProgram::shader_program_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Compile failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::CheckLinkStatus()
{
	glGetProgramiv(ShaderProgram::shader_program_id, GL_LINK_STATUS, &link_status);
	if (link_status == GL_FALSE)
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
