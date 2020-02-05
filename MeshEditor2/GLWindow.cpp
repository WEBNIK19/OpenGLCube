#include "GLWindow.h"



GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height)
{
	glfwInit();
	this->width = width;
	this->height = height;
	this->handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
	if (this->handle == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(this->handle);

	static bool initGLAD = false;
	if (!initGLAD)
	{
		initGLAD = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	glViewport(0, 0, width, height);
	
	
	glfwSetWindowUserPointer(this->handle, (void*)this);
	glfwSetKeyCallback(handle, onKey);
	glfwSetMouseButtonCallback(handle, onMouseButton);
	glfwSetCursorPosCallback(handle,  onCursorPos);
	glfwSetScrollCallback(handle,  onScroll);
}

GLWindow::~GLWindow() {
	glfwTerminate();
}

GLFWwindow* GLWindow::getGLFWHandle() const{
	return this->handle;
}
uint32_t GLWindow::getWidth() const {
	return this->width;
}
uint32_t GLWindow::getHeight() const{
	return this->height;
}
void GLWindow::onKey(GLFWwindow* window, int key, int scancode, int actions, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, true);
	else {
		GLWindow* obj = (GLWindow*)glfwGetWindowUserPointer(window);
		obj->keyCallback((KeyCode)key, (Action)actions, (Modifier)mods);
	}
}
void GLWindow::onMouseButton(GLFWwindow* window, int button, int action, int mods) {
	GLWindow* obj = (GLWindow*)glfwGetWindowUserPointer(window);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	//obj->mouseCallback((ButtonCode)button, (Action)action, (Modifier)mods, xpos, ypos);
}
void GLWindow::onCursorPos(GLFWwindow *window, double x, double y) {
	GLWindow* obj = (GLWindow*)glfwGetWindowUserPointer(window);
	//obj->cursorPosCallback(x, y);
}
void GLWindow::onScroll(GLFWwindow* window, double xoffset, double yoffset) {
	GLWindow* obj = (GLWindow*)glfwGetWindowUserPointer(window);
	//obj->scrollCallback(xoffset, yoffset);
};
void GLWindow::setKeyCallback(const KeyCallback& callback) {
	
	this->keyCallback = callback;
}
void GLWindow::setCursorPosCallback(const CursorPosCallback& callback) {
	this->cursorPosCallback = callback;
}
void GLWindow::setMouseCallback(const MouseCallback& callback) {
	this->mouseCallback = callback;
};
void GLWindow::setScrollCallback(const ScrollCallback& callback) {
	this->scrollCallback = callback;
};

bool GLWindow::shouldClose() {
	return glfwWindowShouldClose(this->handle);
}