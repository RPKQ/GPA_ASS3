#ifndef GPA_ASS2_CAMERA_H
#define GPA_ASS2_CAMERA_H

#include "GLIncludes.h"

constexpr auto MOUSE_START_POS = -1;

class Camera 
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT, FRONT, BACK};

	Camera(glm::vec3 CamPos, glm::vec3 LookPos, glm::vec3 UpDir);
	~Camera();
	void moveLocal(Direction direct);
	void rotateWithMouse(int mouse_x, int mouse_y);
	void endOfRotate();
	void setMoveSpeed(float speedFactor);

	glm::vec3 getLookDir();
	glm::vec3 getUpDir();
	glm::vec3 getLeftDir();
	glm::vec3 getRightDir();
	glm::vec3 getCamPos();
	glm::mat4 getViewMat();

private:
	glm::mat4 viewMatrix;
	glm::vec3 camPos;
	glm::vec3 lookPos;
	glm::vec3 upDir;
	float rotateSpeedFactor = 0.001f;
	float moveSpeedFactor = 5.0f;
	struct {
		int x = MOUSE_START_POS, y = MOUSE_START_POS;
	} lastMouse;

	void updateViewMat();
};

#endif