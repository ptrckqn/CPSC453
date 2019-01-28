/*
 * Program.h
 *	Base class of a rendering program. Has a scene to render, a rendering engine and a window to render to.
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <iostream>
#include <string>
#include <vector>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>


//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;

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



};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct Geometry{
	// OpenGL names for array buffer objects, vertex array object
	GLuint  vertexBuffer;
	GLuint  textureBuffer;
	GLuint  colourBuffer;
	GLuint  vertexArray;
	GLsizei elementCount;

	// initialize object names to zero (OpenGL reserved value)
	Geometry() : vertexBuffer(0), colourBuffer(0), vertexArray(0), elementCount(0)
	{}
};

struct planet{
	planet* parent;
	std::vector<planet*> child;
	int tex;
	float distance;
	float axialT;
	float inc;
	float rPeriod;
	float oSpeed;
	glm::mat4 trans;
	glm::vec3 o = glm::vec3(0, 0, 0);
	float radius;
};

void drawSolarSystem(int focusPlanet);
void scroll_callback(GLFWwindow* window, double xOff, double yOff);
std::string LoadSource(const std::string &filename);
GLuint CompileShader(GLenum shaderType, const std::string &source);
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint InitializeShaders();
void InitializeVAO(Geometry *Geometry);
void LoadGeometry(Geometry *geometry, glm::vec3 *vertices, glm::vec2* texCoord, int elementCount);
void DestroyGeometry(Geometry *geometry);

int oSpeed = 1;
float scale = 6.0;

GLFWwindow* window;

#endif /* PROGRAM_H_ */
