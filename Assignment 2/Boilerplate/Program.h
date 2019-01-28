/*
 * Program.h
 *	Base class of a rendering program. Has a scene to render, a rendering engine and a window to render to.
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>
//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;
class RenderingEngine;
class Scene;

class Program {
public:
	Program();
	virtual ~Program();

	//Creates the rendering engine and the scene and does the main draw loop
	void start();

	//Initializes GLFW and creates the window
	void setupWindow();

	//Prints system specs to the console
	void QueryGLVersion();

	Scene* getScene(){
		return scene;
	}




private:
	GLFWwindow* window;
	RenderingEngine* renderingEngine;
	Scene* scene;


};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	int scaleF = 0;
	int scaleR = 0;
	int up = 0;
	int left = 0;
	int right = 0;
	int down = 0;
	bool mButtonDown = false;
	std::string fileName = "i1.png";
	std::string bgName = "b1.png";
#endif /* PROGRAM_H_ */
