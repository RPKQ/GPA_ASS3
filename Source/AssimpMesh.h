#ifndef GPA_ASS2_ASSIMP_MESH_H
#define GPA_ASS2_ASSIMP_MESH_H

#include "GLIncludes.h"
#include "Program.h"
#include <vector>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

class AssimpMesh
{
public:
	AssimpMesh(aiMesh* mesh);
	~AssimpMesh();
	void draw();
	void setMaterialsArray(std::vector<GLuint>* material_array);
private:
	std::string name;
	std::vector<GLuint>* materialArray;
	std::vector<float> data;
	std::vector<unsigned int> indices;
	GLuint vao;
	GLuint ebo;
	GLuint vbo;
	int materialID, indexCount;
};

#endif