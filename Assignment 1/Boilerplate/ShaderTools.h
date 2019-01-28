/*
 * Scene.cpp
 *
 *  Author: Patrick Quan and Jason Li
 		ID's: 10152770 (Patrick), 10158349 (Jason)
		Based off Boilerplate provided by John Hall

		Q, W, E and, R to change scenes
		Up and down arrow keys to increase and decrease level.
 */
#ifndef SHADERTOOLS_H_
#define SHADERTOOLS_H_

#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

//Shader associated functions are put in the ShaderTools namespace
namespace ShaderTools {

	std::string LoadSource(const std::string &filename);

	// creates and returns a shader object compiled from the given source
	GLuint CompileShader(GLenum shaderType, const std::string &source);

	// creates and returns a program object linked from vertex and fragment shaders
	GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader);

	GLuint InitializeShaders();
}

#endif /* SHADERTOOLS_H_ */
