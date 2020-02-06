#pragma once
#include <glm.hpp>
#include "Camera.h"
struct ray
{
	glm::vec3 orig;
	glm::vec3 dir{ 0,0,1 };
};

class Viewport
{
public:
	glm::mat4 calcProjectionMatrix() const;
	void setViewportSize(uint32_t inWidth, uint32_t inHeight);
	void setFOV(double inFOV);
	void setZNear(double inZNear);
	void setZFar(double inZFar);
	void setParallelProjection(bool use);
	double getZNear() const; // 0.01 by default
	double getZFar() const; // 500 by default
	double getFov() const; // 60 in degrees by default
	double getWidth() const; // 1 by default
	double getHeight() const; // 1 by default
	bool isParallelProjection() const; // false by default
	ray calcCursorRay(double x, double z) const;
	double calcTargetPlaneWidth() const;
	double calcTargetPlaneHeight() const;
	double calcAspectRatio() const;
	Camera& getCamera();
	const Camera& getCamera() const;
private:
	float FOV;
	float zNear;
	float zFar;
	bool PP;
	uint32_t width;
	uint32_t height;
	Camera camera;
};

