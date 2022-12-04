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
	vertex_shader.checkCompileStatus();
	return vertex_shader;
}

Shader ShaderProgram::CreateFragmentShader(const char* fragment_shader_code)
{
	Shader fragment_shader(true);
	fragment_shader.setSource(fragment_shader_code);
	fragment_shader.compile();
	fragment_shader.checkCompileStatus();
	return fragment_shader;
}

std::string ShaderProgram::loadFile(const char* fname)
{
	std::ifstream file(fname);
	if (!file.is_open())
	{
		printf("Unable to open file  %s\n", fname);
		//exit(1);
	}
	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}

void ShaderProgram::AttachShaders(const char* vertex_shader_file_name, const char* fragment_shader_file_name)
{
	Shader vertex_shader = CreateVertexShader(ShaderProgram::loadFile(vertex_shader_file_name).c_str());
	Shader fragment_shader = CreateFragmentShader(ShaderProgram::loadFile(fragment_shader_file_name).c_str());
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

GLint ShaderProgram::GetUniformLocation() {
	GLint id = glGetUniformLocation(ShaderProgram::shader_program_id, "modelMatrix"); 
	if (id == -1) 
	{
		fprintf(stderr, "***Could not get uniform location by the name modelMatrix\n");
	}
	return id;
}

GLint ShaderProgram::GetUniformLocation(std::string name_of_variable) {
	GLint id = glGetUniformLocation(ShaderProgram::shader_program_id, name_of_variable.c_str());
	if (id == -1) 
	{
	fprintf(stderr, "***Could not get uniform location by the name *%s*\n", name_of_variable.c_str());
	}
	return id;
}

void ShaderProgram::UseProgram()
{
	glUseProgram(shader_program_id);
}
