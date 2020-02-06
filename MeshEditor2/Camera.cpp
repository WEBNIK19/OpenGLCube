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
	return glm::length(target - eye);
}

const glm::vec3& Camera::getEye() const
{
	return eye;
}

const glm::vec3& Camera::getTarget() const
{
	return target;
}

void Camera::setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)
{
	glm::vec3 oldForward = calcForward();
	this->eye = newEye;
	this->target = newTarget;
	
	if (glm::dot(newUp, calcForward()) != 0) {
		if (glm::length(glm::cross(calcForward(), up)) != 0)
			this->up = glm::rotate(glm::mat4(1.0), 90.0f, glm::cross(calcForward(), up)) * glm::vec4(calcForward(), 1.0);
		else
			this->up = oldForward;
		printf("%f %f %f\n", this->up.x, this->up.y, this->up.z);
	}
	else
		this->up = newUp;
}

void Camera::setDistanceToTarget(double D)
{
	eye = target - calcForward() * (float)D;
}

void Camera::setFrontView()
{
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0, 0, 1 }, target, { 0, 1, 0 });
	setDistanceToTarget(D);
}

void Camera::translate(glm::vec3 delta)
{
	this->eye += delta;
	this->target += delta;
}

void Camera::transform(const glm::mat4& trf)
{
	setEyeTargetUp(trf * glm::vec4(eye, 1.0), trf * glm::vec4(target, 1.0), trf * glm::vec4(up, 1.0));
	/*this->eye = trf * glm::vec4(eye, 1.0);
	this->target = trf * glm::vec4(target, 1.0);
	this->up = trf * glm::vec4(up, 0.0);*/
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, double angle)
{
	translate(glm::vec3(0.0) - point);
	//printf("%f\n", (float)angle);
	glm::mat4 rot = glm::rotate(glm::mat4(1.0), (float)angle, axis);
	transform(rot);
	translate(point - glm::vec3(0.0));
}

void Camera::setTopView()
{
	/*glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, 90.0f);*/
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0, 1, 0 }, target, { 0, 0, -1 });
	setDistanceToTarget(D);
}

void Camera::setRearView()
{
	/*glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, 180.0f);*/
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0, 0, -1 }, target, { 0, 1, 0 });
	setDistanceToTarget(D);
}

void Camera::setRightView()
{
	/*glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, 90);*/
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 1, 0, 0 }, target, { 0, 1, 0 });
	setDistanceToTarget(D);
}

void Camera::setLeftView()
{
	/*glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, 90);*/
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ -1, 0, 0 }, target, { 0, 1, 0 });
	setDistanceToTarget(D);
}

void Camera::setBottomView()
{
	/*glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, 90);*/
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0, -1, 0 }, target, { 0, 0, 1 });
	setDistanceToTarget(D);
}

void Camera::setIsoView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, -45.0f);
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
