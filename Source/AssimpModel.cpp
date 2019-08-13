#include "AssimpModel.h"

#ifndef STB_IMAGE_IMPLEMENTATION_HH
#define STB_IMAGE_IMPLEMENTATION_HH
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION
#include "../Include/STB/stb_image.h"

AssimpModel::AssimpModel(const char* filePath)
{
	printf("/////////// load scene from [%s] /////////////////\n", filePath);
	const aiScene *scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);

	loadMaterials(scene);
	loadMeshes(scene);

	aiReleaseImport(scene);
}

AssimpModel::~AssimpModel()
{
	for (auto it = meshes.begin(); it != meshes.end(); it++)
		delete *it;
}

void AssimpModel::draw()
{
	for (int i = 0; i < this->numMeshes; i++)
		meshes[i]->draw();
}

void AssimpModel::loadMaterials(const aiScene *scene)
{
	printf("load %d materials\n", scene->mNumMaterials);
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial *material = scene->mMaterials[i];
		GLuint materialID = 0;
		aiString texturePath;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == aiReturn_SUCCESS)
		{
			auto it = this->matPathIndexMap.find(std::string(texturePath.C_Str()));
			if (it != this->matPathIndexMap.end())
			{
				materialID = (*it).second;
			}
			else
			{
				texture_data tdata = load_png(texturePath.C_Str());
				glGenTextures(1, &materialID);
				glBindTexture(GL_TEXTURE_2D, materialID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tdata.width, tdata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata.data);
				glGenerateMipmap(GL_TEXTURE_2D);

				this->matPathIndexMap.insert(std::pair<std::string, GLuint>(std::string(texturePath.C_Str()), materialID));
				printf("load material [%s]\n", texturePath.C_Str());
			}
		}
		else
		{
			printf("load material [%s] failed!\n", texturePath.C_Str());
		}
		this->materials.push_back(materialID);
	}
}

void AssimpModel::loadMeshes(const aiScene *scene)
{
	printf("load %d meshes\n", scene->mNumMeshes);
	this->numMeshes = scene->mNumMeshes;
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		AssimpMesh* newMesh = new AssimpMesh(mesh);
		newMesh->setMaterialsArray(&this->materials);
		this->meshes.push_back(newMesh);
	}
}

texture_data AssimpModel::load_png(const char* path)
{
	texture_data texture;
	int n;
	stbi_uc *data = stbi_load(path, &texture.width, &texture.height, &n, 4);
	if (data != NULL)
	{
		texture.data = new unsigned char[texture.width * texture.height * 4 * sizeof(unsigned char)];
		memcpy(texture.data, data, texture.width * texture.height * 4 * sizeof(unsigned char));
		// vertical-mirror image data
		for (size_t i = 0; i < texture.width; i++)
		{
			for (size_t j = 0; j < texture.height / 2; j++)
			{
				for (size_t k = 0; k < 4; k++) {
					std::swap(texture.data[(j * texture.width + i) * 4 + k], texture.data[((texture.height - j - 1) * texture.width + i) * 4 + k]);
				}
			}
		}
		stbi_image_free(data);
	}
	return texture;
}