#ifndef GPA_ASS2_SHADER_H
#define GPA_ASS2_SHADER_H
#include "../Source/GLIncludes.h"

class Shader
{
public:
	Shader(GLenum shaderType, const char* filePath);
	~Shader();
	GLuint getID() const;
	void shaderLog();

private:
	GLuint ID;
	static char** loadShaderSource(const char* file);
	static void freeShaderSource(char** shaderSource);
};
#endif

