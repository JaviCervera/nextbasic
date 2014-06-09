#include "glfw3.h"
#include <map>
#include <string>
using namespace std;

typedef void(* GLFWerrorfunBind)(int, string);
typedef void(* GLFWcursorposfunBind)(GLFWwindow*, float, float);
typedef void(* GLFWscrollfunBind)(GLFWwindow*, float, float);

static GLFWerrorfunBind _errorFuncPtr = NULL;
static map<GLFWwindow*, GLFWcursorposfunBind> _cursorPosFuncPtrs;
static map<GLFWwindow*, GLFWscrollfunBind> _scrollFuncPtrs;

static void _errorFunc(int code, const char* msg) {
	if ( _errorFuncPtr ) _errorFuncPtr(code, string(msg));
}

static void _cursorPosFunc(GLFWwindow* win, double x, double y) {
	if ( _cursorPosFuncPtrs.count(win) > 0 ) _cursorPosFuncPtrs[win](win, float(x), float(y));
}

static void _scrollFunc(GLFWwindow* win, double x, double y) {
	if ( _scrollFuncPtrs.count(win) > 0 ) _scrollFuncPtrs[win](win, float(x), float(y));
}

extern "C" {

int _glfwInit() {
	int ret = glfwInit();
	if ( ret == GL_TRUE ) {
		glfwSetErrorCallback(_errorFunc);
	}
	return ret;
}

void _glfwTerminate() {
	glfwTerminate();
	_errorFuncPtr = NULL;
	_cursorPosFuncPtrs.clear();
	_scrollFuncPtrs.clear();
}


GLFWerrorfunBind _glfwSetErrorCallback(GLFWerrorfunBind fun) {
	GLFWerrorfunBind prev = _errorFuncPtr;
	_errorFuncPtr = fun;
	return prev;
}

GLFWwindow* _glfwCreateWindow(int width, int height, const char *title, GLFWmonitor* monitor, GLFWwindow* share) {
	GLFWwindow* win = glfwCreateWindow(width, height, title, monitor, share);
	glfwSetCursorPosCallback(win, _cursorPosFunc);
	glfwSetScrollCallback(win, _scrollFunc);
	return win;
}

void _glfwGetCursorPos(GLFWwindow* window, float* xpos, float* ypos) {
	double dxpos, dypos;
	glfwGetCursorPos(window, &dxpos, &dypos);
	if ( xpos ) *xpos = float(dxpos);
	if ( ypos ) *ypos = float(dypos);
}

void _glfwSetCursorPos(GLFWwindow* window, float xpos, float ypos) {
	glfwSetCursorPos(window, xpos, ypos);
}

GLFWcursorposfunBind _glfwSetCursorPosCallback(GLFWwindow *window, GLFWcursorposfunBind cbfun) {
	GLFWcursorposfunBind prev = NULL;
	if ( _cursorPosFuncPtrs.count(window) > 0 ) prev = _cursorPosFuncPtrs[window];
	_cursorPosFuncPtrs[window] = cbfun;
	return prev;
}

GLFWscrollfunBind _glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfunBind cbfun) {
	GLFWscrollfunBind prev = NULL;
	if ( _scrollFuncPtrs.count(window) > 0 ) prev = _scrollFuncPtrs[window];
	_scrollFuncPtrs[window] = cbfun;
	return prev;
}

float _glfwGetTime() {
	return float(glfwGetTime());
}

void _glfwSetTime(float time) {
	glfwSetTime(time);
}

} // extern "C"
