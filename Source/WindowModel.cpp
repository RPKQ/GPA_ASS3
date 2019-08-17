#include "WindowModel.h"

WindowModel::WindowModel()
{
	static const GLfloat window_positions[] =
	{
		1.0f,-1.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,0.0f,
		-1.0f,1.0f,0.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f
	};

	// window_vao
	glGenVertexArrays(1, &this->vaoWindow);
	glBindVertexArray(this->vaoWindow);

	glGenBuffers(1, &this->window_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->window_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(window_positions), window_positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, (const GLvoid*)(sizeof(GL_FLOAT) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

WindowModel::~WindowModel()
{
	glDeleteBuffers(1, &this->window_buffer);
	glDeleteVertexArrays(1, &this->vaoWindow);
}

void WindowModel::draw()
{
	glBindVertexArray(this->vaoWindow);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}