/*
 * Program.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function

	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 512;
	int height = 512;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(window, this);

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Set the custom function that tracks mouse clicks
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//Set the custom function that tracks mouse movement
	glfwSetCursorPosCallback(window, cursor_pos_callback);

	//Set the custom function that tracks scroll movement
	glfwSetScrollCallback(window, scroll_callback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	Program *program = (Program*) glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		scaleR = scaleR - 1;
		program -> getScene() -> rotate(fileName, scaleR);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		scaleR = scaleR + 1;
		program -> getScene() -> rotate(fileName, scaleR);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		fileName = "i1.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		fileName = "i2.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		fileName = "i3.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		fileName = "i4.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		fileName = "i5.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		fileName = "i6.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		fileName = "i7.png";
		scaleF = 0;
		scaleR = 0;
		program -> getScene() -> newImg(fileName);
	}
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		bgName = "b1.png";
		program -> getScene() -> bgImg(bgName);
	}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		bgName = "b2.png";
		program -> getScene() -> bgImg(bgName);
	}
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		bgName = "b3.png";
		program -> getScene() -> bgImg(bgName);
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> grayscale(0);
	}
 	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> grayscale(1);
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> grayscale(2);
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> grayscale(3);
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(0);
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(1);
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(2);
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> gaus(0);
		program -> getScene() -> sobel(3);
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> gaus(0);
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> gaus(1);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> gaus(2);
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		program -> getScene() -> grayscale(0);
		program -> getScene() -> sobel(0);
		program -> getScene() -> gaus(3);
	}


}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			mButtonDown = true;
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
			mButtonDown = false;
		}
}


static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
	Program *program = (Program*) glfwGetWindowUserPointer(window);
	if(mButtonDown){
			program -> getScene() -> transform(fileName, xpos - (512 / 2), ypos - (512 /2));
	}

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	Program *program = (Program*) glfwGetWindowUserPointer(window);
	if(yoffset == 1){
		scaleF = scaleF - 50;
	}
	else if(yoffset == -1 && scaleF != 0){
					scaleF = scaleF + 50;
	}
		program -> getScene() -> scale(fileName, scaleF);
}
