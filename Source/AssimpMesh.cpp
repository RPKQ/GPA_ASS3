#include "AssimpMesh.h"

AssimpMesh::AssimpMesh(aiMesh* mesh)
{
	// vao
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);


	// vbo
	for (int v = 0; v < mesh->mNumVertices; v++)
	{
		this->data.push_back(mesh->mVertices[v][0]);
		this->data.push_back(mesh->mVertices[v][1]);
		this->data.push_back(mesh->mVertices[v][2]);
		this->data.push_back(mesh->mNormals[v][0]);
		this->data.push_back(mesh->mNormals[v][1]);
		this->data.push_back(mesh->mNormals[v][2]);
		this->data.push_back(mesh->mTextureCoords[0][v][0]);
		this->data.push_back(mesh->mTextureCoords[0][v][1]);
	}
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(float), &this->data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	// ebo
	for (int v = 0; v < mesh->mNumFaces; v++)
	{
		this->indices.push_back(mesh->mFaces[v].mIndices[0]);
		this->indices.push_back(mesh->mFaces[v].mIndices[1]);
		this->indices.push_back(mesh->mFaces[v].mIndices[2]);
	}
	glGenBuffers(1, &this->ebo); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);


	// others
	this->indexCount = mesh->mNumFaces * 3;
	this->materialID = mesh->mMaterialIndex;
	this->name = std::string(mesh->mName.C_Str());


	// log
	printf("load mesh [%s] with %d vertices, materialID: %d\n", mesh->mName.C_Str(), mesh->mNumVertices, this->materialID);
}

AssimpMesh::~AssimpMesh()
{

}

void AssimpMesh::draw()
{
	//std::cout << "draw mesh [" << this->name << "]\n";
	glBindTexture(GL_TEXTURE_2D, (*this->materialArray)[this->materialID]);
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
}

void AssimpMesh::setMaterialsArray(std::vector<GLuint>* material_array)
{
	this->materialArray = material_array;
}

