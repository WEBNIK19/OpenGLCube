#include "GLWindow.h"
#include "GLRenderSystem.h"
#include <glfw3.h>
#include <iostream>
#include <ctype.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm\gtc\type_ptr.hpp>
#include "Viewport.h"

std::vector<Vertex> vertices = {
	{{-0.5f,-0.5f,-0.5f},{-1.0f,  0.0f, 0.0f}},
	{{-0.5f,-0.5f, 0.5f},{-1.0f,  0.0f, 0.0f}},
	{{-0.5f, 0.5f, 0.5f},{-1.0f,  0.0f, 0.0f}},
	{{0.5f, 0.5f,-0.5f},{0.0f,  0.0f, -1.0f}},
	{{-0.5f,-0.5f,-0.5f},{0.0f,  0.0f, -1.0f}},
	{{-0.5f, 0.5f,-0.5f},{0.0f,  0.0f, -1.0f}},
	{{0.5f,-0.5f, 0.5f},{0.0f,  -1.0f, 0.0f}},
	{{-0.5f,-0.5f,-0.5f},{0.0f,  -1.0f, 0.0f}},
	{{0.5f,-0.5f,-0.5f},{0.0f,  -1.0f, 0.0f}},
	{{0.5f, 0.5f,-0.5f},{0.0f,  0.0f, -1.0f}},
	{{0.5f,-0.5f,-0.5f},{0.0f,  0.0f, -1.0f}},
	{{-0.5f,-0.5f,-0.5f},{0.0f,  0.0f, -1.0f}},
	{{-0.5f,-0.5f,-0.5f},{-1.0f,  0.0f, 0.0f}},
	{{-0.5f, 0.5f, 0.5f},{-1.0f,  0.0f, 0.0f}},
	{{-0.5f, 0.5f,-0.5f},{-1.0f,  0.0f, 0.0f}},
	{{0.5f,-0.5f, 0.5f},{0.0f,  -1.0f, 0.0f}},
	{{-0.5f,-0.5f, 0.5f},{0.0f,  -1.0f, 0.0f}},
	{{-0.5f,-0.5f,-0.5f},{0.0f,  -1.0f, 0.0f}},
	{{-0.5f, 0.5f, 0.5f},{0.0f,  0.0f, 1.0f}},
	{{-0.5f,-0.5f, 0.5f},{0.0f,  0.0f, 1.0f}},
	{{0.5f,-0.5f, 0.5f},{0.0f,  0.0f, 1.0f}},
	{{0.5f, 0.5f, 0.5f},{1.0f,  0.0f, 0.0f}},
	{{0.5f,-0.5f,-0.5f},{1.0f,  0.0f, 0.0f}},
	{{0.5f, 0.5f,-0.5f},{1.0f,  0.0f, 0.0f}},
	{{0.5f,-0.5f,-0.5f},{1.0f,  0.0f, 0.0f}},
	{{0.5f, 0.5f, 0.5f},{1.0f,  0.0f, 0.0f}},
	{{0.5f,-0.5f, 0.5f},{1.0f,  0.0f, 0.0f}},
	{{0.5f, 0.5f, 0.5f},{0.0f,  1.0f, 0.0f}},
	{{0.5f, 0.5f,-0.5f},{0.0f,  1.0f, 0.0f}},
	{{-0.5f, 0.5f,-0.5f},{0.0f,  1.0f, 0.0f}},
	{{0.5f, 0.5f, 0.5f},{0.0f,  1.0f, 0.0f}},
	{{-0.5f, 0.5f,-0.5f},{0.0f,  1.0f, 0.0f}},
	{{-0.5f, 0.5f, 0.5f},{0.0f,  1.0f, 0.0f}},
	{{0.5f, 0.5f, 0.5f},{0.0f,  0.0f, 1.0f}},
	{{-0.5f, 0.5f, 0.5f},{0.0f,  0.0f, 1.0f}},
	{{0.5f,-0.5f, 0.5f},{0.0f,  0.0f, 1.0f}}
};
void renderScene(GLRenderSystem& rs)
{	
	rs.renderTriangleSoup(vertices);	
}

void moveCube(GLRenderSystem& rs ,glm::vec3 offset)
{
	static glm::vec3 pos = glm::vec3(0.0);
	pos += offset;

	glm::mat4 worldMatrix = glm::translate(glm::mat4(1.0), pos);

	rs.setWorldMatrix(worldMatrix);

}

glm::vec3 getFigCenter(const std::vector<Vertex>& vertices) {
	glm::vec3 figCntr = glm::vec3(0.0);

	for (int i = 0; i < vertices.size(); i++) {
		figCntr += vertices[i].position / (float)vertices.size();
	}

	return figCntr;
}

void rotateCube(float deg, glm::vec3 pivot)
{
	std::vector<Vertex> vertices2;
	glm::mat4 rfrag = glm::mat4(1.0);
	glm::mat4 rnorm = glm::mat4(1.0);

	glm::mat4 toFigCntr = glm::mat4(1.0);
	glm::mat4 fromFigCntr = glm::mat4(1.0);

	glm::mat4 deformate = glm::mat4(1.0);
	glm::mat4 formate = glm::mat4(1.0);

	glm::vec3 figCntr = getFigCenter(vertices);

	fromFigCntr = glm::translate(fromFigCntr,glm::vec3(0.0) - figCntr);
	toFigCntr = glm::translate(toFigCntr, figCntr - glm::vec3(0.0));

	rfrag = glm::rotate(rfrag, deg, pivot);
	rnorm = glm::rotate(rnorm, deg, pivot);

	std::transform(vertices.begin(), vertices.end(), back_inserter(vertices2), [fromFigCntr, toFigCntr, rfrag, rnorm](Vertex v) -> Vertex {
		Vertex v1 = { {0.0,0.0,0.0}, {0.0,0.0,0.0} };
		glm::vec4 pos = fromFigCntr * glm::vec4(v.position, 1.0);
		pos = rfrag * pos;
		pos = toFigCntr * pos;

		glm::vec4 nrm = fromFigCntr * glm::vec4(v.normal, 1.0);
		nrm = rnorm * nrm;
		nrm = toFigCntr * nrm;

		v1.position = glm::vec3(pos.x, pos.y, pos.z);
		v1.normal = glm::vec3(nrm.x, nrm.y, nrm.z);
		return v1;
	});
	vertices.clear();
	vertices = vertices2;
}


void moveCamera(Camera& camera, glm::vec3 offset)
{
	//TODO
}


int main(void)
{
	
	GLRenderSystem rs;
	GLWindow window = GLWindow("myWindow", 640, 480);

	Viewport viewport;
	viewport.setViewportSize(640, 480);
	viewport.setFOV(60);
	viewport.setZNear(0.01);
	viewport.setZFar(500);

	window.setKeyCallback([&](KeyCode key, Action action, Modifier mods) {
		if (key == KeyCode::UP && action != Action::Release)
			moveCube(rs, glm::vec3(0.0, 0.01, 0.0));

		if (key == KeyCode::DOWN && action != Action::Release)
			moveCube(rs, glm::vec3(0.0, -0.01, 0.0));

		if (key == KeyCode::LEFT && action != Action::Release)
			moveCube(rs, glm::vec3(-0.01, 0.0, 0.0));

		if (key == KeyCode::RIGHT && action != Action::Release)
			moveCube(rs, glm::vec3(0.01, 0.0, 0.0));

		if (key == KeyCode::RIGHT && action != Action::Release)
			moveCube(rs, glm::vec3(0.01, 0.0, 0.0));

		if (key == KeyCode::W && action != Action::Release)
			moveCamera(viewport.getCamera(), glm::vec3(1.0, 0.0, 0.0));

		if (key == KeyCode::S && action != Action::Release)
			moveCamera(viewport.getCamera(), glm::vec3(0.0, 0.0, 1.0));

		if (key == KeyCode::A && action != Action::Release)
			moveCamera(viewport.getCamera(), glm::vec3(0.0, 1.0, 0.0));

		if (key == KeyCode::D && action != Action::Release)
			moveCamera(viewport.getCamera(), glm::vec3(0.0, 1.0, 0.0));

		if (key == KeyCode::F1 && action != Action::Release)
			viewport.getCamera().setFrontView();

		if (key == KeyCode::F2 && action != Action::Release)
			viewport.getCamera().setTopView();

		if (key == KeyCode::F3 && action != Action::Release)
			viewport.getCamera().setRearView();

		if (key == KeyCode::F4 && action != Action::Release)
			viewport.getCamera().setRightView();

		if (key == KeyCode::F5 && action != Action::Release)
			viewport.getCamera().setLeftView();

		if (key == KeyCode::F6 && action != Action::Release)
			viewport.getCamera().setBottomView();

		if (key == KeyCode::F7 && action != Action::Release)
			viewport.getCamera().setIsoView();

		if (key == KeyCode::F8 && action != Action::Release)
			if (viewport.isParallelProjection()) 
				viewport.setParallelProjection(false);
			else
				viewport.setParallelProjection(true);
		});
	
	rs.init();
	rs.setupLight(1, glm::vec3{ 0,0.5,0.5 }, glm::vec3{ 1,0,0 }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,1 });
	rs.turnLight(1, true);
	
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rs.setViewMatrix(viewMatrix);

	glm::mat4 projMatrix = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 500.f);
	rs.setProjMatrix(projMatrix);
	

	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		rs.setViewport(0, 0, window.getWidth(), window.getHeight());
		rs.clearDisplay(0.5f, 0.5f, 0.5f);

		rs.setViewMatrix(viewport.getCamera().calcViewMatrix());
		rs.setProjMatrix(viewport.calcProjectionMatrix());
		renderScene(rs);
		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();

	}
	rs.~GLRenderSystem();
	window.~GLWindow();
	return 0;
}