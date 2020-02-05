#include "Viewport.h"



Camera& Viewport::getCamera()
{
	return this->camera;
}

const Camera& Viewport::getCamera() const
{
	return this->camera;
}

ray Viewport::calcCursorRay(double x, double z) const
{
	/*glm::vec3 a = glm::unProject(x, y, -1.0);
	glm::vec3 b = glm::unProject(x, y, 1.0);
	ray cursorRay{ a, normalize(b - a) };*/
	return ray();
}

double Viewport::calcTargetPlaneWidth() const
{
	return calcTargetPlaneHeight() * calcAspectRatio();
}

double Viewport::calcTargetPlaneHeight() const
{
	return 2.0 * camera.distanceFromEyeToTarget() * tan(glm::radians(FOV / 2.0));
}

double Viewport::calcAspectRatio() const
{
	return width / height;
}

glm::mat4 Viewport::calcProjectionMatrix() const
{
	return glm::mat4();
}

void Viewport::setViewportSize(uint32_t inWidth, uint32_t inHeight)
{
}

void Viewport::setFOV(double inFOV)
{
}

void Viewport::setZNear(double inZNear)
{
	this->zNear = inZNear;
}

void Viewport::setZFar(double inZFar)
{
	this->zFar = inZFar;
}

void Viewport::setParallelProjection(bool use)
{
}

double Viewport::getZNear() const
{
	return this->zNear;
}

double Viewport::getZFar() const
{
	return this->zFar;
}

double Viewport::getFov() const
{
	return this->FOV;
}

double Viewport::getWidth() const
{
	return this->width;
}

double Viewport::getHeight() const
{
	return this->height;
}

bool Viewport::isParallelProjection() const
{
	return PP;
}
