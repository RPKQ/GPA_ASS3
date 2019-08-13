#include "Camera.h"

Camera::Camera(glm::vec3 cam_pos, glm::vec3 look_pos, glm::vec3 up_dir)
{
	this->camPos = cam_pos;
	this->lookPos = look_pos;
	this->upDir = up_dir;
	this->updateViewMat();
}

Camera::~Camera() {}

void Camera::moveLocal(Camera::Direction direct)
{
	// Get Movement
	glm::vec3 movement = glm::vec3(0.0, 0.0, 0.0);
	switch (direct)
	{
	case Camera::UP:
		movement = glm::vec3(0.0, 1.0, 0.0);
		break;
	case Camera::DOWN:
		movement = glm::vec3(0.0, -1.0, 0.0);
		break;
	case Camera::LEFT:
		movement = this->getLeftDir();
		break;
	case Camera::RIGHT:
		movement = this->getRightDir() ;
		break;
	case Camera::FRONT:
		movement = this->getLookDir();
		break;
	case Camera::BACK:
		movement = -this->getLookDir();
		break;
	default:
		break;
	}

	// update members
	movement *= this->moveSpeedFactor;
	camPos += movement;
	lookPos += movement;
	this->updateViewMat();
}

void Camera::rotateWithMouse(int mouse_x, int mouse_y)
{
	if (this->lastMouse.x == MOUSE_START_POS && this->lastMouse.y == MOUSE_START_POS)
	{
		this->lastMouse.x = mouse_x;
		this->lastMouse.y = mouse_y;
		return;
	}


	// update lastMouse
	int move_x = mouse_x - this->lastMouse.x;
	int move_y = mouse_y - this->lastMouse.y;
	this->lastMouse.x = mouse_x;
	this->lastMouse.y = mouse_y;

	// get rotate matrix
	glm::vec3 mouseMoveInSpace =  this->getRightDir() * (float)move_x - this->getUpDir() * (float)move_y;
	if (glm::length(mouseMoveInSpace) == 0) return;


	glm::vec3 rotateAxis = glm::cross(mouseMoveInSpace, this->getLookDir());
	glm::mat4 rotateMat = glm::rotate(glm::mat4(), glm::length(mouseMoveInSpace) * rotateSpeedFactor, rotateAxis);

	// update lookDir and upDir
	glm::vec4 look_dir = rotateMat * glm::vec4(this->getLookDir(), 0.0);
	this->lookPos = this->camPos + glm::normalize(glm::vec3(look_dir));
	/*glm::vec4 up_dir = rotateMat * glm::vec4(this->getUpDir(), 0.0);
	this->upDir = glm::normalize(glm::vec3(up_dir));*/

	// update viewMatrix
	this->updateViewMat(); 
}

void Camera::endOfRotate()
{
	this->lastMouse.x = MOUSE_START_POS;
	this->lastMouse.y = MOUSE_START_POS;
}

void Camera::updateViewMat()
{
	this->viewMatrix = glm::lookAt(this->camPos, this->lookPos, this->upDir);
}

void Camera::setMoveSpeed(float speedFactor)
{
	this->moveSpeedFactor = speedFactor;
}

glm::vec3 Camera::getCamPos()
{
	return this->camPos;
}

glm::vec3 Camera::getLookDir()
{
	return glm::normalize(this->lookPos - this->camPos);
}

glm::vec3 Camera::getUpDir()
{
	return glm::normalize(this->upDir);
}

glm::vec3 Camera::getLeftDir()
{
	glm::vec3 left = glm::cross(this->getUpDir(), this->getLookDir());
	return glm::normalize(left);
;}

glm::vec3 Camera::getRightDir()
{
	return -this->getLeftDir();
}

glm::mat4 Camera::getViewMat()
{
	return this->viewMatrix;
}