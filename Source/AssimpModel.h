#ifndef GPA_ASS2_ASSIMP_MODEL_H
#define GPA_ASS2_ASSIMP_MODEL_H

#include "AssimpMesh.h"
#include "Program.h"
#include "GLIncludes.h"
#include <vector>
#include <map>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

typedef struct _texture_data
{
	_texture_data() : width(0), height(0), data(0) {}
	int width;
	int height;
	unsigned char* data;
} texture_data;

class AssimpModel
{
public:
	AssimpModel(const char* filePath);
	~AssimpModel();
	void draw();

private:
	std::vector<AssimpMesh*> meshes;
	std::vector<GLuint> materials;
	std::map<std::string, GLuint> matPathIndexMap;
	int numMeshes;
	void loadMaterials(const aiScene *scene);
	void loadMeshes (const aiScene *scene);
	static texture_data load_png(const char* filePath);
};

#endif