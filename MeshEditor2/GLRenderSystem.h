#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "GLWindow.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class GLRenderSystem
{
public:
	~GLRenderSystem();
	void init(); //must be called after glfw window creation. Set default GL settings
	void clearDisplay(float r, float g, float b);
	void setViewport(double x, double y, double width, double height);
	void renderTriangleSoup(const std::vector<Vertex>&  vertices);
	void setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
	void turnLight(uint32_t index, bool enable);
	void setWorldMatrix(const glm::mat4&   matrix);
	const glm::mat4&   getWorldMatrix() const;
	void setViewMatrix(const glm::mat4&   matrix);
	const glm::mat4&   getViewMatrix() const;
	void setProjMatrix(const glm::mat4&   matrix);
	const glm::mat4&   getProjMatrix() const;
private:
	GLuint VAO;
	
	GLuint VBO;
	
	glm::mat4 worldMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	//GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
};