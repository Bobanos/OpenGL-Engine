#pragma once
//Include GLEW
#include <GL/glew.h>

#include "SOIL.h"
//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string>

class Texture
{
public:
	Texture(int textureUnit);
	void ActiveTexture();
	void LoadTexture(std::string textureFileName);
	void Parameters();
	void BindTexture();
	void Uniform1i(GLint id);

private:
	int textureUnitNumber;
	int const textureUnitNumberIncreaser = 33984;
	GLuint textureID;
};

