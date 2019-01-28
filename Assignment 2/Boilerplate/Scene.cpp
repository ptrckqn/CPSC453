/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	MyTexture texture;
	InitializeTexture(&texture, "i1.png", GL_TEXTURE_RECTANGLE);

	//Load texture uniform
	//Shaders need to be active to load uniforms
	glUseProgram(renderer->shaderProgram);
	//Set which texture unit the texture is bound to
	glActiveTexture(GL_TEXTURE0);
	//Bind the texture to GL_TEXTURE0
	glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	//Get identifier for uniform
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	//Load texture unit number into uniform
	glUniform1i(uniformLocation, 0);

	gs = 0;
	sobelNum = 0;
	gaussian = 0;

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

		// three vertex positions and assocated colours of a triangle
	rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f,  -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f, 0.9f, 1.0f));

	/*rectangle.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	rectangle.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	rectangle.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	rectangle.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	rectangle.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	rectangle.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));*/

	rectangle.drawMode = GL_TRIANGLES;


	rectangle.uvs.push_back(glm::vec2(0.0f,  0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(texture.height)));


	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);

}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::newImg (std::string fileName){

	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();

	MyTexture texture;
	if (fileName == "i1.png") {
		InitializeTexture(&texture, "i1.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i2.png"){
		InitializeTexture(&texture, "i2.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i3.png"){
		InitializeTexture(&texture, "i3.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i4.png"){
		InitializeTexture(&texture, "i4.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i5.png"){
		InitializeTexture(&texture, "i5.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i6.png"){
		InitializeTexture(&texture, "i6.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i7.png"){
		InitializeTexture(&texture, "i7.png", GL_TEXTURE_RECTANGLE);
	}

	glUseProgram(renderer->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	glUniform1i(uniformLocation, 0);

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}


	rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f,  -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f, 0.9f, 1.0f));

	rectangle.drawMode = GL_TRIANGLES;

	rectangle.uvs.push_back(glm::vec2(0.0f,  0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f , float(texture.height)));


	RenderingEngine::assignBuffers(rectangle);
	RenderingEngine::setBufferData(rectangle);
	objects.push_back(rectangle);

}

void Scene::transform(std::string fileName, double xScale, double yScale){
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();

	float x = xScale / 500.0f;
	float y = yScale / 500.0f;

	MyTexture texture;
	if (fileName == "i1.png") {
		InitializeTexture(&texture, "i1.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i2.png"){
		InitializeTexture(&texture, "i2.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i3.png"){
		InitializeTexture(&texture, "i3.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i4.png"){
		InitializeTexture(&texture, "i4.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i5.png"){
		InitializeTexture(&texture, "i5.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i6.png"){
		InitializeTexture(&texture, "i6.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i7.png"){
		InitializeTexture(&texture, "i7.png", GL_TEXTURE_RECTANGLE);
	}
	glUseProgram(renderer->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	glUniform1i(uniformLocation, 0);

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}
	// rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( 0.9f,  -0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( -0.9f, 0.9f, 1.0f));

	rectangle.verts.push_back(glm::vec3( -0.9f + x, -0.9f - y, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f + x,  -0.9f - y, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f + x, 0.9f - y, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f + x, -0.9f - y, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f + x, 0.9f - y, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f + x, 0.9f - y, 1.0f));

	rectangle.drawMode = GL_TRIANGLES;

	rectangle.uvs.push_back(glm::vec2(0.0f,  0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f , float(texture.height)));

	// rectangle.uvs.push_back(glm::vec2(0.0f - x,  0.0f + y));
	// rectangle.uvs.push_back(glm::vec2(float(texture.width - x), 0.f + y));
	// rectangle.uvs.push_back(glm::vec2(float(texture.width - x), float(texture.height + y)));
	// rectangle.uvs.push_back(glm::vec2(0.0f - x, 0.0f + y));
	// rectangle.uvs.push_back(glm::vec2(float(texture.width - x), float(texture.height + y)));
	// rectangle.uvs.push_back(glm::vec2(0.0f - x, float(texture.height + y)));

	RenderingEngine::assignBuffers(rectangle);
	RenderingEngine::setBufferData(rectangle);
	objects.push_back(rectangle);
}

void Scene::scale(std::string fileName, double s){
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();

	float sFactor = s / 1000.0f;

	MyTexture texture;
	if (fileName == "i1.png") {
		InitializeTexture(&texture, "i1.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i2.png"){
		InitializeTexture(&texture, "i2.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i3.png"){
		InitializeTexture(&texture, "i3.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i4.png"){
		InitializeTexture(&texture, "i4.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i5.png"){
		InitializeTexture(&texture, "i5.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i6.png"){
		InitializeTexture(&texture, "i6.png", GL_TEXTURE_RECTANGLE);
	}
	else if(fileName == "i7.png"){
		InitializeTexture(&texture, "i7.png", GL_TEXTURE_RECTANGLE);
	}
	glUseProgram(renderer->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	glUniform1i(uniformLocation, 0);

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}
	// rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( 0.9f,  -0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	// rectangle.verts.push_back(glm::vec3( -0.9f, 0.9f, 1.0f));

	rectangle.verts.push_back(glm::vec3( -0.9f + sFactor, -0.9f + sFactor, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f - sFactor,  -0.9f + sFactor, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f - sFactor, 0.9f - sFactor, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f + sFactor, -0.9f + sFactor, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f - sFactor, 0.9f - sFactor, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f + sFactor, 0.9f - sFactor, 1.0f));

	rectangle.drawMode = GL_TRIANGLES;

	rectangle.uvs.push_back(glm::vec2(0.0f,  0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f , float(texture.height)));

	// rectangle.uvs.push_back(glm::vec2(0.0f + sFactor,  0.0f + sFactor));
	// rectangle.uvs.push_back(glm::vec2(float(texture.width - sFactor), 0.f + sFactor));
	// rectangle.uvs.push_back(glm::vec2(float(texture.width - sFactor), float(texture.height - sFactor)));
	// rectangle.uvs.push_back(glm::vec2(0.0f + sFactor, 0.0f + sFactor));
	// rectangle.uvs.push_back(glm::vec2(float(texture.width - sFactor), float(texture.height - sFactor)));
	// rectangle.uvs.push_back(glm::vec2(0.0f + sFactor, float(texture.height - sFactor)));

	RenderingEngine::assignBuffers(rectangle);
	RenderingEngine::setBufferData(rectangle);
	objects.push_back(rectangle);
}

void Scene::rotate(std::string fileName, double rFactor){
		objects.clear();
		rectangle.verts.clear();
		rectangle.uvs.clear();

		rFactor = rFactor / 10;

		MyTexture texture;
		if (fileName == "i1.png") {
			InitializeTexture(&texture, "i1.png", GL_TEXTURE_RECTANGLE);
		}
		else if(fileName == "i2.png"){
			InitializeTexture(&texture, "i2.png", GL_TEXTURE_RECTANGLE);
		}
		else if(fileName == "i3.png"){
			InitializeTexture(&texture, "i3.png", GL_TEXTURE_RECTANGLE);
		}
		else if(fileName == "i4.png"){
			InitializeTexture(&texture, "i4.png", GL_TEXTURE_RECTANGLE);
		}
		else if(fileName == "i5.png"){
			InitializeTexture(&texture, "i5.png", GL_TEXTURE_RECTANGLE);
		}
		else if(fileName == "i6.png"){
			InitializeTexture(&texture, "i6.png", GL_TEXTURE_RECTANGLE);
		}
		else if(fileName == "i7.png"){
			InitializeTexture(&texture, "i7.png", GL_TEXTURE_RECTANGLE);
		}
		glUseProgram(renderer->shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
		GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
		glUniform1i(uniformLocation, 0);

		if(renderer->CheckGLErrors()) {
			std::cout << "Texture creation failed" << std::endl;
		}

		// float pointOneX = 0.0f * cos(rFactor) + 0.0f * -(sin(rFactor));
		// float pointTwoX = float(texture.width) * cos(rFactor) + 0.0f * -(sin(rFactor));
		// float pointThreeX = float(texture.width) * cos(rFactor) + float(texture.height) * -(sin(rFactor));
		// float pointFourX = 0.0f * cos(rFactor) + 0.0f * -(sin(rFactor));
		// float pointFiveX = float(texture.width) * cos(rFactor) + float(texture.height) * -(sin(rFactor));
		// float pointSixX = 0.0f * cos(rFactor) + float(texture.height) * -(sin(rFactor));
		//
		// float pointOneY = 0.0f * sin(rFactor) + 0.0f * cos(rFactor);
		// float pointTwoY = float(texture.width) * sin(rFactor) + 0.0f * cos(rFactor);
		// float pointThreeY = float(texture.width) * sin(rFactor) + float(texture.height) * cos(rFactor);
		// float pointFourY = 0.0f * sin(rFactor) + 0.0f * cos(rFactor);
		// float pointFiveY = float(texture.width) * sin(rFactor) + float(texture.height) * cos(rFactor);
		// float pointSixY = 0.0f * sin(rFactor) + float(texture.height) * cos(rFactor);

		float pointOneX = -0.9f * cos(rFactor) + -0.9f * -(sin(rFactor));
		float pointTwoX = 0.9f * cos(rFactor) + -0.9f * -(sin(rFactor));
		float pointThreeX = 0.9f * cos(rFactor) + 0.9f * -(sin(rFactor));
		float pointFourX = -0.9f * cos(rFactor) + -0.9f * -(sin(rFactor));
		float pointFiveX = 0.9f * cos(rFactor) + 0.9f * -(sin(rFactor));
		float pointSixX = -0.9f * cos(rFactor) + 0.9f * -(sin(rFactor));

		float pointOneY = -0.9f * sin(rFactor) + -0.9f * cos(rFactor);
		float pointTwoY = 0.9f * sin(rFactor) + -0.9f * cos(rFactor);
		float pointThreeY = 0.9f * sin(rFactor) + 0.9f * cos(rFactor);
		float pointFourY = -0.9f * sin(rFactor) + -0.9f * cos(rFactor);
		float pointFiveY = 0.9f * sin(rFactor) + 0.9f * cos(rFactor);
		float pointSixY = -0.9f * sin(rFactor) + 0.9f * cos(rFactor);

		rectangle.verts.push_back(glm::vec3(pointOneX, pointOneY, 1.0f));
		rectangle.verts.push_back(glm::vec3(pointTwoX, pointTwoY, 1.0f));
		rectangle.verts.push_back(glm::vec3(pointThreeX, pointThreeY, 1.0f));
		rectangle.verts.push_back(glm::vec3(pointFourX , pointFourY, 1.0f));
		rectangle.verts.push_back(glm::vec3(pointFiveX, pointFiveY, 1.0f));
		rectangle.verts.push_back(glm::vec3(pointSixX, pointSixY, 1.0f));

		// rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
		// rectangle.verts.push_back(glm::vec3( 0.9f,  -0.9f, 1.0f));
		// rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
		// rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
		// rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
		// rectangle.verts.push_back(glm::vec3( -0.9f, 0.9f, 1.0f));

		rectangle.drawMode = GL_TRIANGLES;

		rectangle.uvs.push_back(glm::vec2(0.0f,  0.0f));
		rectangle.uvs.push_back(glm::vec2(float(texture.width), 0.f));
		rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
		rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
		rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
		rectangle.uvs.push_back(glm::vec2(0.0f, float(texture.height)));

		// rectangle.uvs.push_back(glm::vec2(pointOneX, pointOneY));
		// rectangle.uvs.push_back(glm::vec2(pointTwoX, pointTwoY));
		// rectangle.uvs.push_back(glm::vec2(pointThreeX, pointThreeY));
		// rectangle.uvs.push_back(glm::vec2(pointFourX , pointFourY));
		// rectangle.uvs.push_back(glm::vec2(pointFiveX, pointFiveY));
		// rectangle.uvs.push_back(glm::vec2(pointSixX, pointSixY));

		RenderingEngine::assignBuffers(rectangle);
		RenderingEngine::setBufferData(rectangle);
		objects.push_back(rectangle);
}

void Scene::grayscale(int gs) {
	glUseProgram(renderer -> shaderProgram);
	GLgrayscale = glGetUniformLocation(renderer -> shaderProgram, "gs");
	glUniform1i(GLgrayscale, gs);
}

void Scene::sobel(int sobelNum) {
	glUseProgram(renderer -> shaderProgram);
	GLsobel = glGetUniformLocation(renderer -> shaderProgram, "sobelNum");
	glUniform1i(GLsobel, sobelNum);
}

void Scene::gaus(int gaussian) {
	glUseProgram(renderer -> shaderProgram);
	GLgaus = glGetUniformLocation(renderer -> shaderProgram, "gaussian");
	glUniform1i(GLgaus, gaussian);
}

void Scene::bgImg(std::string bgName){
	objects.clear();

	MyTexture textureTwo;
	if (bgName == "b1.png") {
		InitializeTexture(&textureTwo, "b1.png", GL_TEXTURE_RECTANGLE);
	}
	else if(bgName == "b2.png"){
		InitializeTexture(&textureTwo, "b2.png", GL_TEXTURE_RECTANGLE);
	}
	else if(bgName == "b3.png"){
		InitializeTexture(&textureTwo, "b3.png", GL_TEXTURE_RECTANGLE);
	}

	glUseProgram(renderer->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, textureTwo.textureID);
	GLuint uniformLocationTwo = glGetUniformLocation(renderer->shaderProgram, "imageTextureTwo");
	glUniform1i(uniformLocationTwo, 0);

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}
	rectangleTwo.verts.push_back(glm::vec3( -1.0f, -1.0f, 0.0f));
	rectangleTwo.verts.push_back(glm::vec3( 1.0f,  -1.0f, 0.0f));
	rectangleTwo.verts.push_back(glm::vec3( 1.0f, 1.0f, 0.0f));
	rectangleTwo.verts.push_back(glm::vec3( -1.0f, -1.0f, 0.0f));
	rectangleTwo.verts.push_back(glm::vec3( 1.0f, 1.0f, 0.0f));
	rectangleTwo.verts.push_back(glm::vec3( -1.0f, 1.0f, 0.0f));

	rectangleTwo.drawMode = GL_TRIANGLES;

	rectangleTwo.uvs.push_back(glm::vec2(0.0f,  0.0f));
	rectangleTwo.uvs.push_back(glm::vec2(float(textureTwo.width), 0.f));
	rectangleTwo.uvs.push_back(glm::vec2(float(textureTwo.width), float(textureTwo.height)));
	rectangleTwo.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangleTwo.uvs.push_back(glm::vec2(float(textureTwo.width), float(textureTwo.height)));
	rectangleTwo.uvs.push_back(glm::vec2(0.0f , float(textureTwo.height)));

	RenderingEngine::assignBuffers(rectangleTwo);
	RenderingEngine::setBufferData(rectangleTwo);
	objects.push_back(rectangleTwo);
}
