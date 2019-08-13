#ifndef GPA_ASS2_PROGRAM_H
#define GPA_ASS2_PROGRAM_H

#include "Shader.h"

#include "GLIncludes.h"
#include <set>

class Program
{
public:
	Program(const char* vsPath, const char* fsPath);
	~Program();

	void use() const;
	GLuint getID() const;

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setTexture(GLuint textureID);

private:
	GLuint ID;
	std::set<std::string> uniformNames;
};

#endif
