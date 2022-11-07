#include "Shader.h"

Shader::Shader(bool is_fragment)
{
	if(is_fragment)
	{
		Shader::shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	Shader::shader_id = glCreateShader(GL_VERTEX_SHADER);
}

void Shader::setSource(const char* shader_code)
{
	glShaderSource(Shader::shader_id, 1, &shader_code, NULL);
}

void Shader::compile()
{
	glCompileShader(Shader::shader_id);
}

GLuint Shader::get_shader_id()
{
	return Shader::shader_id;
}
