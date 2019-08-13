#include "Filter.h"

Filter::Filter()
{
	static const GLfloat window_positions[] =
	{
		1.0f,-1.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,0.0f,
		-1.0f,1.0f,0.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f
	};

	// others
	glGenFramebuffers(1, &this->FBO_ID);

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

Filter::~Filter()
{
	glDeleteBuffers(1, &this->window_buffer);
	glDeleteVertexArrays(1, &this->vaoWindow);
	glDeleteFramebuffers(1, &this->FBO_ID);
}

GLuint Filter::getID() const
{
	return this->FBO_ID;
}

void Filter::reshape(int width, int height)
{
	// FBO
	glDeleteRenderbuffers(1, &this->RBO);
	glDeleteTextures(1, &this->FBO_tex);

	glGenRenderbuffers(1, &this->RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

	glGenTextures(1, &this->FBO_tex);
	glBindTexture(GL_TEXTURE_2D, this->FBO_tex);	// bind tex
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO_ID);	// bind FBO
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->RBO);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->FBO_tex, 0);
}

void Filter::draw() const
{
	glBindVertexArray(this->vaoWindow);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->FBO_tex);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}