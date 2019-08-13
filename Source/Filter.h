#ifndef GPA_ASS2_FILTER_H
#define GPA_ASS2_FILTER_H
#include "../Source/GLIncludes.h"
#include "Program.h"

class Filter
{
public:
	Filter();
	~Filter();
	void reshape(int width, int height);
	GLuint getID() const;
	void draw() const;

private:
	GLuint FBO_ID;
	GLuint RBO, FBO_tex;
	GLuint vaoWindow;
	GLuint window_buffer;
};
#endif

