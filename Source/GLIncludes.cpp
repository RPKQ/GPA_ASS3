#include "GLIncludes.h"

void dumpInfo(void)
{
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}


void printGLError()
{
	GLenum code = glGetError();
	switch (code)
	{
	case GL_NO_ERROR:
		std::cout << "GL_NO_ERROR" << std::endl;
		break;
	case GL_INVALID_ENUM:
		std::cout << "GL_INVALID_ENUM" << std::endl;
		break;
	case GL_INVALID_VALUE:
		std::cout << "GL_INVALID_VALUE" << std::endl;
		break;
	case GL_INVALID_OPERATION:
		std::cout << "GL_INVALID_OPERATION" << std::endl;
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
		break;
	case GL_OUT_OF_MEMORY:
		std::cout << "GL_OUT_OF_MEMORY" << std::endl;
		break;
	case GL_STACK_UNDERFLOW:
		std::cout << "GL_STACK_UNDERFLOW" << std::endl;
		break;
	case GL_STACK_OVERFLOW:
		std::cout << "GL_STACK_OVERFLOW" << std::endl;
		break;
	default:
		std::cout << "GL_ERROR" << std::endl;
	}
}

void printMat4(glm::mat4 mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%lf ", mat[i][j]);
		printf("\n");
	}
}

void printVec3(glm::vec3 vec)
{
	printf("(%lf, %lf, %lf)\n", vec.x, vec.y, vec.z);
}

