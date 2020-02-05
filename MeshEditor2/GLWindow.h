#pragma once

#include <glad/glad.h>
#include <string>
#include <glfw3.h>
#include <iostream>
#include <functional>

enum class Modifier
{
	NoModifier = 0,
	Shift = 1,
	Control = 2,
	Alt = 4,
	Super = 8,
};

enum class Action
{
	Release = 0,
	Press = 1,
	Repeat = 2,
};

enum class ButtonCode
{
	Button_0 = 0,
	//... repeats all buttons codes from the glfw header
};

enum class KeyCode
{
	UNKNOWN = -1,
	SPASE = 32,
	APOSTROPHE = 39,
	COMMA = 44,
	MINUS = 45,  
	PERIOD = 46, 
	SLASH = 47,  
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	SEMICOLON = 59,
	EQUAL = 61,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	ESCAPE = 256,
	RIGHT = 262,
	LEFT = 263,
	DOWN = 264,
	UP	 = 265,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5	 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297
};

class GLWindow
{
public:
	using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
	using CursorPosCallback = std::function<void(double, double)>;
	using MouseCallback = std::function<void(ButtonCode, Action, Modifier, double, double)> ;
	using ScrollCallback = std::function<void(double, double)>;
	

	GLWindow(const std::string&, uint32_t, uint32_t);
	~GLWindow();
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	bool shouldClose();
	
	void setKeyCallback(const KeyCallback& callback);
	
	void setCursorPosCallback(const CursorPosCallback& callback);
	void setMouseCallback(const MouseCallback& callback);
	void setScrollCallback(const ScrollCallback& callback);

	GLFWwindow* getGLFWHandle() const;
	
private:
	GLFWwindow* handle;
	uint32_t width;
	uint32_t height;
	static void onKey(GLFWwindow*, int, int, int, int);
	static void onCursorPos(GLFWwindow*, double, double);
	static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void onScroll(GLFWwindow* window, double xoffset, double yoffset);
	KeyCallback keyCallback;
	CursorPosCallback cursorPosCallback;
	MouseCallback mouseCallback;
	ScrollCallback scrollCallback;
};

