#pragma once

//Include GLEW
#include <GL/glew.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>   // std::setprecision, std::setw

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags




class Model
{
private:
	GLuint VBO;
	GLuint VAO;
	GLsizei count_of_indices;
	void loadModelFromFile(std::string modelFileName);
	std::vector<float> data;

public:
	Model();

	void generate_VBO(const float model_data[], int size_of_data, int count);
	void generate_VBO(std::string modelFileName);
	void generate_VAO8();
	void generate_VAO6();
	void generate_skybox_VAO();
	void bind_VAO();

	GLsizei GetCountOfIndices();
};


