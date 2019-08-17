#ifndef GPA_ASS2_FBO_H
#define GPA_ASS2_FBO_H
#include "../Source/GLIncludes.h"
#include "Program.h"

class FBO
{
public:
	FBO();
	~FBO();
	void reshape(int width, int height);
	GLuint getID() const;
	GLuint getOuputTex() const;

private:
	GLuint FBO_ID;
	GLuint RBO, FBO_tex;
};
#endif

