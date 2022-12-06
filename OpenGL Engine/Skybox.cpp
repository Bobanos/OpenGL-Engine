#include "Skybox.h"

Skybox::Skybox(int textureUnit)
{
	Skybox::textureUnitNumber = textureUnit;
	glActiveTexture(Skybox::textureUnitNumber + Skybox::textureUnitNumberIncreaser);
}

void Skybox::LoadCubemap()
{
	Skybox::textureID = SOIL_load_OGL_cubemap("Textures/posx.jpg", "Textures/negx.jpg", "Textures/posy.jpg", "Textures/negy.jpg", "Textures/posz.jpg", "Textures/negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (Skybox::textureID == NULL) {
		printf("An error occurred while loading skybox texture from file");
	}
}
void Skybox::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, Skybox::textureID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
void Skybox::Uniform1i(GLint id)
{
	glUniform1i(id, Skybox::textureUnitNumber);
}