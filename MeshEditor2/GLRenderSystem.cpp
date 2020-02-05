#include "GLRenderSystem.h"




void GLRenderSystem::init() {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glDepthFunc(GL_LESS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_LIGHTING);
	setWorldMatrix(glm::mat4(1.0));
	setViewMatrix(glm::mat4(1.0));
	setProjMatrix(glm::mat4(1.0));
};
GLRenderSystem::~GLRenderSystem() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void GLRenderSystem::clearDisplay(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void GLRenderSystem::setViewport(double x, double y, double width, double height) {
	glViewport(x, y, width, height);
};

void GLRenderSystem::renderTriangleSoup(const std::vector<Vertex>& vertices) {
	std::vector<Vertex> vertices2;
	std::transform(vertices.begin(), vertices.end(), back_inserter(vertices2), [ this](Vertex v) -> Vertex {
		Vertex v1 = { {0.0,0.0,0.0}, {0.0,0.0,0.0} };
		glm::vec4 pos = this->projMatrix * this->viewMatrix * this->worldMatrix * glm::vec4(v.position, 1.0);
		glm::vec4 nrm = this->worldMatrix * glm::vec4(v.normal, 1.0);
		v1.position = glm::vec3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
		v1.normal = glm::vec3(nrm);
		return v1;
	});

	glBufferData(GL_ARRAY_BUFFER,  vertices2.size()*sizeof(Vertex), vertices2.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex,normal));
	
	glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
};
void GLRenderSystem::setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is) {
	glm::vec4 pos = projMatrix * viewMatrix * glm::vec4(position, 1.0);
	if (index <= 7 && index >= 0) {
		index = GL_LIGHT0 + index;
		glLightfv(index, GL_POSITION, glm::value_ptr(pos));
		glLightfv(index, GL_AMBIENT, glm::value_ptr(glm::vec4(Ia, 1.0)));
		glLightfv(index, GL_DIFFUSE, glm::value_ptr(glm::vec4(Id, 1.0)));
		glLightfv(index, GL_SPECULAR, glm::value_ptr(glm::vec4(Is, 1.0)));
	}	
};
void GLRenderSystem::turnLight(uint32_t index, bool enable) {
	if (index <= 7 && index >= 0) {
		index = GL_LIGHT0 + index;
		if (enable)
			glEnable(index);
		else
			glDisable(index);
	}
		
};
void GLRenderSystem::setWorldMatrix(const glm::mat4& matrix) {
	this->worldMatrix = matrix;
};
const glm::mat4& GLRenderSystem::getWorldMatrix() const {
	return worldMatrix;
};
void GLRenderSystem::setViewMatrix(const glm::mat4& matrix) {
	this->viewMatrix = matrix;
};
const glm::mat4& GLRenderSystem::getViewMatrix() const {
	return viewMatrix;
};
void GLRenderSystem::setProjMatrix(const glm::mat4& matrix) {
	this->projMatrix = matrix;
};
const glm::mat4& GLRenderSystem::getProjMatrix() const {
	return projMatrix;
};