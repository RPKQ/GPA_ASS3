#ifndef GPA_ASS2_WINDOW_MODEL_H
#define GPA_ASS2_WINDOW_MODEL_H

#include "GLIncludes.h"
class WindowModel
{
public:
	WindowModel();
	~WindowModel();
	void draw();
private:
	GLuint vaoWindow;
	GLuint window_buffer;
};

#endif