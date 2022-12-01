#include "Shader.h"

Shader::Shader(bool is_fragment)
{
	if(is_fragment)
	{
		printf("***Constructed fragment shader\n");
		Shader::shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		printf("***Constructed vertex shader\n");
		Shader::shader_id = glCreateShader(GL_VERTEX_SHADER);
	}

}

void Shader::setSource(const char* shader_code)
{
	glShaderSource(Shader::shader_id, 1, &shader_code, NULL);
}

void Shader::compile()
{
	glCompileShader(Shader::shader_id);
}

void Shader::checkCompileStatus() {
	glGetShaderiv(Shader::shader_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(Shader::shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(Shader::shader_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "***Compile failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

GLuint Shader::get_shader_id()
{
	return Shader::shader_id;
}
