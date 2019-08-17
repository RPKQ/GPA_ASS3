#include "FBO.h"

FBO::FBO()
{
	glGenFramebuffers(1, &this->FBO_ID);
	// tex and RBO will be init in reshape
}

FBO::~FBO()
{
	glDeleteFramebuffers(1, &this->FBO_ID);
}

GLuint FBO::getID() const
{
	return this->FBO_ID;
}

void FBO::reshape(int width, int height)
{
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

GLuint FBO::getOuputTex() const
{
	return this->FBO_tex;
}