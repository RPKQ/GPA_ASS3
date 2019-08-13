#ifndef GPA_ASS2_GLINCLUDE_H
#define GPA_ASS2_GLINCLUDE_H

#ifdef _MSC_VER
	#include "../Include/GLEW/glew.h"
	#include "../Include/FreeGLUT/freeglut.h"
	#include <direct.h>
#else
	#include <OpenGL/gl3.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
#endif

#ifdef _MSC_VER
	#pragma comment (lib, "glew32.lib")
	#pragma comment(lib, "freeglut.lib")
	#pragma comment(lib, "assimp.lib")
#endif

#define GLM_SWIZZLE
#include "../Include/GLM/glm/glm.hpp"
#include "../Include/GLM/glm/gtc/matrix_transform.hpp"
#include "../Include/GLM/glm/gtc/type_ptr.hpp"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <string>

#ifdef _MSC_VER
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
	#define __FILEPATH__(x) ((std::string(__FILE__).substr(0, std::string(__FILE__).rfind('\\'))+(x)).c_str())
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
	#define __FILEPATH__(x) ((std::string(__FILE__).substr(0, std::string(__FILE__).rfind('/'))+(x)).c_str())
#endif

#define deg2rad(x) ((x)*((3.1415926f)/(180.0f)))

void dumpInfo(void);
void printGLError();
void printMat4(glm::mat4 mat);
void printVec3(glm::vec3 vec);

#endif
