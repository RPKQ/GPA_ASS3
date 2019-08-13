#include "Program.h"

Program::Program(const char* vsPath, const char* fsPath)
{
	this->ID = glCreateProgram();
	
	// Shader
	Shader* vs = new Shader(GL_VERTEX_SHADER, vsPath);
	Shader* fs = new Shader(GL_FRAGMENT_SHADER, fsPath);
	glAttachShader(this->ID, vs->getID());
	glAttachShader(this->ID, fs->getID());

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	// Link Program
	glLinkProgram(this->ID);
	glGetProgramiv(this->ID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(this->ID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		system("pause");
	}

	// Release Them
	glDetachShader(this->ID, vs->getID());
	glDetachShader(this->ID, fs->getID());
	delete vs;
	delete fs;

	// Validate Program
	glValidateProgram(this->ID);
	glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(this->ID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		system("pause");
	}
}

Program::~Program()
{
	glDeleteProgram(this->ID);
}

void Program::use() const
{
	glUseProgram(this->ID);
}

GLuint Program::getID() const
{
	return this->ID;
}

void Program::setTexture(const std::string &name, GLuint textureID, int bindingPoint)
{
	glActiveTexture(bindingPoint);
	glBindTexture(GL_TEXTURE_2D, textureID);
	this->setInt(name, bindingPoint);
}

// ------------------------------------------------------------------------
void Program::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Program::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Program::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Program::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Program::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Program::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Program::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Program::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Program::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Program::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Program::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Program::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
