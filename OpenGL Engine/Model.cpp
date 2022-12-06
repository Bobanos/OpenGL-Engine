#include "Model.h"

Model::Model()
{
	Model::VBO = 0;
	Model::VAO = 0;
}

void Model::loadModelFromFile(std::string modelFileName)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
	const aiScene* aisceneP = importer.ReadFile(modelFileName.c_str(), importOptions);
	if (aisceneP) {
		aiMesh* mesh = aisceneP->mMeshes[0];
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (unsigned int j = 0; j < 3; j++)
			{
				Model::data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
				Model::data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
				Model::data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
				Model::data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
				Model::data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
				Model::data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
				Model::data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
				Model::data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
			}
		}
	}
	else {
		printf("Could not load model file named: %s, %s", modelFileName.c_str(), importer.GetErrorString());
		exit(EXIT_FAILURE);
	}
}

void Model::generate_VBO(const float model_data[], int size_of_data, int count)
{
	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size_of_data, model_data, GL_STATIC_DRAW); // TODO

	Model::count_of_indices = count;
}

void Model::generate_VBO(std::string modelFileName)
{
	Model::loadModelFromFile(modelFileName);

	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Model::data.size() * sizeof(float), &Model::data[0], GL_STATIC_DRAW); // TODO

	Model::count_of_indices = Model::data.size() / 8;
}

void Model::generate_VAO8()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glEnableVertexAttribArray(2); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),NULL); //Cordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(GLvoid*)(3 * sizeof(GLfloat))); //Normal
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(GLfloat))); //Texture uv
}

void Model::generate_VAO6()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL); //Cordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat))); //Normal
}

void Model::generate_skybox_VAO()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	bind_VAO();
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//TODO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL); //Cordinates
}

void Model::bind_VAO()
{
	glBindVertexArray(VAO); //bind the VAO
}

GLsizei Model::GetCountOfIndices()
{
	return Model::count_of_indices;
}
