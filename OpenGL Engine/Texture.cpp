#include "Texture.h"

Texture::Texture(int textureUnit)
{
	Texture::textureUnitNumber = textureUnit;
	glActiveTexture(Texture::textureUnitNumber + Texture::textureUnitNumberIncreaser);
}
void Texture::ActiveTexture()
{
	glActiveTexture(Texture::textureUnitNumber + Texture::textureUnitNumberIncreaser);
}
void Texture::LoadTexture(std::string textureFileName)
{
	Texture::textureID = SOIL_load_OGL_texture(textureFileName.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (Texture::textureID == NULL) {
		printf("An error occurred while loading texture from file: %s", textureFileName.c_str());
	}
}
void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, Texture::textureID);
}
void Texture::Uniform1i(GLint id)
{
	glUniform1i(id, Texture::textureUnitNumber);
}