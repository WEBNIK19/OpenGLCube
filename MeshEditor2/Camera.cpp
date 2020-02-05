#include "Camera.h"

glm::mat4 Camera::calcViewMatrix() const
{
	return glm::lookAt(eye, target, up);
}

glm::vec3 Camera::calcForward() const
{
	return glm::normalize(target - eye);
}

glm::vec3 Camera::calcRight() const
{
	return glm::normalize(glm::cross(up,calcForward()));
}

double Camera::distanceFromEyeToTarget() const
{
	return glm::length(calcForward());
}

const glm::vec3& Camera::getEye() const
{
	return eye;
}

const glm::vec3& Camera::getTarget() const
{
	return target;
}

void Camera::setFrontView()
{
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0,0,1 }, target, { 0,1,0 });
	setDistanceToTarget(D);
}

void Camera::setTopView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, 90);
}

void Camera::setRearView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, 180);
}

void Camera::setRightView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, 90);
}

void Camera::setLeftView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, -90);
}

void Camera::setBottomView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, -90);
}

void Camera::setIsoView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,1,1 }, 90);
}

void Camera::orbit(glm::vec3 a, glm::vec3 b)
{
	float angle = 1.0f / cos(glm::dot(a, b)); // ???????????
	glm::vec3 axis = glm::cross(a, b);
	glm::mat4 O = glm::mat4(1.0);
	O = glm::rotate(O, angle, axis);

}

void Camera::pan(double u, double v)
{
	this->target = target + calcRight() * (float)u + up * (float)v;
	this->eye = eye + calcRight() * (float)u + up * (float)v;
}

void Camera::zoom(double factor)
{
}

void Camera::translate(glm::vec3 delta)
{
	this->eye += delta;
	this -> target += delta;
}

void Camera::setDistanceToTarget(double D)
{
	eye = target - calcForward() * (float)D;
}

void Camera::transform(const glm::mat4& trf)
{
	this->eye = trf * glm::vec4(eye,1.0);
	this->target = trf * glm::vec4(target, 1.0);
	this->up = trf * glm::vec4(up, 0.0);
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, double angle)
{
	translate(glm::vec3(0.0) - point);
	glm::mat4 rot = glm::mat4(1.0);
	rot = glm::rotate(rot, (float)angle, axis);
	transform(rot);
	translate(point - glm::vec3(0.0));
}

void Camera::setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)
{
	glm::vec3 f = calcForward();
	this->eye = newEye;
	this->target = newTarget;

	if (glm::dot(newUp, f) != 0) {
		this->up = glm::rotate(glm::mat4(1.0), 90.0f, glm::cross(f, up)) * glm::vec4(f, 1.0);
	} else 
		this->up = newUp;
}
