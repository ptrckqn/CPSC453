/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */


 //USE DEGREE ELEVATION WITHIN THE SHADER TO BRING ALL BEZIERS TO CUBIC LEVEL TO SIMPLIFY

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GlyphExtractor.h"

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	//
	// spiral.verts.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	// spiral.verts.push_back(glm::vec3( 1.0f,  0.0f, 1.0f));
	//
	// spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	// spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	//
	// spiral.drawMode = GL_PATCHES;
	//
	// //Construct vao and vbos for the triangle
	// RenderingEngine::assignBuffers(spiral);
	//
	// //Send the triangle data to the GPU
	// //Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	// RenderingEngine::setBufferData(spiral);
	//
	//Add the triangle to the scene objects
	// objects.push_back(spiral);
	// GlyphExtractor g;
	// g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	// MyGlyph a = g.ExtractGlyph('a');
	//
	// for (unsigned int i = 0; i < a.contours.size(); i++) {
	// 	std::cout << "Contour " << i << std::endl;
	// 	for(unsigned int j = 0; j < a.contours[i].size(); j++) {
	// 		std::cout << "Bezier curve " << j << std::endl;
	// 		for(unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
	// 			std::cout << "x " << a.contours[i][j].x[k] << std::endl;
	// 			std::cout << "y " << a.contours[i][j].y[k] << std::endl;
	// 			std::cout << std::endl;
	// 		}
	// 	}
	// }

}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}


void Scene::sceneOne(bool cPoints) {
	objects.clear();
	spiral.verts.clear();
	spiral.colors.clear();

	spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(2.0f, -1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(-2.0f, -1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3(1.2f, 0.5f, 1.0f));
	spiral.verts.push_back(glm::vec3(2.5f, 1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3(1.3f, -0.4f, 1.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	if(cPoints){

		//dots
		//off curve 3
		spiral.verts.push_back(glm::vec3(2.01f, -1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.01f, -1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));

		//on curve 1
		spiral.verts.push_back(glm::vec3(0.01f, -1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.01f, -1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		//off curve 1
		spiral.verts.push_back(glm::vec3(-2.01f, -1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(-2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-2.01f, -1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));

		//on curve 1
		spiral.verts.push_back(glm::vec3(-1.01f, 1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.01f, 1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		//on curve 2
		spiral.verts.push_back(glm::vec3(0.01f, 1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.01f, 1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		//on curve 2
		spiral.verts.push_back(glm::vec3(1.01f, 1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.01f, 1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		//on curve 2
		spiral.verts.push_back(glm::vec3(1.25f, 0.51f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.2f, 0.5f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.21f, 0.51f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		//off curve 3
		spiral.verts.push_back(glm::vec3(2.51f, 1.01f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.5f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.51f, 1.01f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));

		//on curve 3
		spiral.verts.push_back(glm::vec3(1.31f, -0.41f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.3f, -0.4f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.31f, -0.41f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		//Lines
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));

		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));

		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(0.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.0f, -1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		spiral.verts.push_back(glm::vec3(1.2f, 0.5f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.3f, -0.4f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.3f, -0.4f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.3f, -0.4f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.5f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.5f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(2.5f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.2f, 0.5f, 1.0f));
		spiral.verts.push_back(glm::vec3(1.2f, 0.5f, 1.0f));

	}

	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);

}

void Scene::sceneTwo(bool cPoints) {
	objects.clear();
	spiral.verts.clear();
	spiral.colors.clear();

	spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
	spiral.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
	spiral.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
	spiral.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));

	spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
	spiral.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
	spiral.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
	spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));

	if(cPoints){

		//dots
		//on curve 1
		spiral.verts.push_back(glm::vec3( 1.1f, 1.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 1.1f, 1.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 1.1f, 1.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//off curve 1
		spiral.verts.push_back(glm::vec3( 4.1f, 0.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.1f, 0.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.2f, 0.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//off curve 1
		spiral.verts.push_back(glm::vec3( 6.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.1f, 2.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//on curve 1
		spiral.verts.push_back(glm::vec3( 9.1f, 1.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.1f, 1.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.1f, 1.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));


		//on curve 2
		spiral.verts.push_back(glm::vec3( 8.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.1f, 2.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//off curve 2
		spiral.verts.push_back(glm::vec3( 0.1f, 8.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.1f, 8.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.1f, 8.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//off curve 2
		spiral.verts.push_back(glm::vec3( 0.1f, -2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.1f, -2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.1f, -2.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//on curve 2
		spiral.verts.push_back(glm::vec3( 8.1f, 4.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.1f, 4.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.1f, 4.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//on curve 3
		spiral.verts.push_back(glm::vec3( 5.1f, 3.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.1f, 3.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.1f, 3.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//off curve 3
		spiral.verts.push_back(glm::vec3( 3.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 2.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//off curve 3
		spiral.verts.push_back(glm::vec3( 3.1f, 3.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 3.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 3.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//on curve 3
		spiral.verts.push_back(glm::vec3( 5.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.1f, 2.1f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.1f, 2.1f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//on curve 4
		spiral.verts.push_back(glm::vec3( 3.1f, 2.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 2.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 2.3f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//off curve 4
		spiral.verts.push_back(glm::vec3( 3.6f, 2.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.6f, 2.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.6f, 2.8f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//off curve 4
		spiral.verts.push_back(glm::vec3( 3.6f, 3.4f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.6f, 3.4f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.6f, 3.4f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//on curve 4
		spiral.verts.push_back(glm::vec3( 3.1f, 3.9f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 3.9f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.1f, 3.9f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//on curve 5
		spiral.verts.push_back(glm::vec3( 2.9f, 3.6f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.9f, 3.6f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.9f, 3.6f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		//off curve 5
		spiral.verts.push_back(glm::vec3( 2.5f, 3.9f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.5f, 3.9f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.5f, 3.9f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//off curve 5
		spiral.verts.push_back(glm::vec3( 2.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.5f, 3.3f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 1.0f));

		//on curve 5
		spiral.verts.push_back(glm::vec3( 2.9f, 3.6f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.9f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.6f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.9f, 3.6f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));


		//Lines
		spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

		spiral.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));

		spiral.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
		spiral.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));

		spiral.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));

		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
		spiral.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));

	}

	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);

}

void Scene::sceneThree(int font){
	objects.clear();
	spiral.verts.clear();
	spiral.colors.clear();
	GlyphExtractor g;

	std::string fontOne = "fonts/source-sans-pro/SourceSansPro-Regular.otf";
	std::string fontTwo = "fonts/lora/Lora-Regular.ttf";
	std::string fontThree = "fonts/great-vibes/GreatVibes-Regular.otf";

	if(font == 1){
		g.LoadFontFile(fontOne);
	}
	else if(font == 2){
		g.LoadFontFile(fontTwo);
	}
	else if(font == 3){
		g.LoadFontFile(fontThree);
	}

	char fName[7] = {'P', 'a', 't', 'r', 'i', 'c', 'k'};

	float leftShift = -5.5f;
	float fontSize = 4.5f;

	for(int i = 0; i < 7; i++){
		MyGlyph myG = g.ExtractGlyph(fName[i]);
		for(int j = 0; j < myG.contours.size(); j++){
			for(int k = 0; k < myG.contours[j].size(); k++){
				if (myG.contours[j][k].degree == 1) {
					for(int l = 0; l <= myG.contours[j][k].degree; l++){
						spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[l] * fontSize + leftShift, myG.contours[j][k].y[l] * fontSize + 0.5f, 1.0f));
						spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
					}
					spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[1] * fontSize + leftShift, myG.contours[j][k].y[1] * fontSize + 0.5f, 1.0f));
					spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
					spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[1] * fontSize + leftShift, myG.contours[j][k].y[1] * fontSize + 0.5f, 1.0f));
					spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
				}
				else if (myG.contours[j][k].degree == 2) {
					for(int l = 0; l <= myG.contours[j][k].degree; l++){
						spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[l] * fontSize + leftShift, myG.contours[j][k].y[l] * fontSize + 0.5f, 1.0f));
						spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
					}
					spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[2] * fontSize + leftShift, myG.contours[j][k].y[2] * fontSize + 0.5f, 1.0f));
					spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
				}
				else if (myG.contours[j][k].degree == 3) {
					for(int l = 0; l <= myG.contours[j][k].degree; l++){
						spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[l] * fontSize + leftShift, myG.contours[j][k].y[l] * fontSize + 0.5f, 1.0f));
						spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
					}
				}

				spiral.drawMode = GL_PATCHES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(spiral);

				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(spiral);

				//Add the triangle to the scene objects
				objects.push_back(spiral);
				spiral.verts.clear();
			}
		}
		leftShift = leftShift + myG.advance * fontSize;
	}
}

void Scene::sceneFour(int font){
	objects.clear();
	spiral.verts.clear();
	spiral.colors.clear();
	GlyphExtractor g;

	std::string fontOne = "fonts//alex-brush/AlexBrush-Regular.ttf";
	std::string fontTwo = "fonts/inconsolata/Inconsolata.otf";
	std::string fontThree = "fonts/amatic/AmaticSC-Regular.ttf";

	if(font == 1){
		g.LoadFontFile(fontOne);
	}
	else if(font == 2){
		g.LoadFontFile(fontTwo);
	}
	else if(font == 3){
		g.LoadFontFile(fontThree);
	}

	std::string s = "the quick brown fox jumps over the lazy dog";

	float leftShift = -9.0f;
	float fontSize = 3.0f;

	for(int i = 0; i < sizeof(s); i++){
		MyGlyph myG = g.ExtractGlyph(s[i]);
		for(int j = 0; j < myG.contours.size(); j++){
			for(int k = 0; k < myG.contours[j].size(); k++){
				if (myG.contours[j][k].degree == 1) {
					for(int l = 0; l <= myG.contours[j][k].degree; l++){
						spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[l] * fontSize + leftShift, myG.contours[j][k].y[l] * fontSize + 0.5f, 1.0f));
						spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
					}
					spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[1] * fontSize + leftShift, myG.contours[j][k].y[1] * fontSize + 0.5f, 1.0f));
					spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
					spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[1] * fontSize + leftShift, myG.contours[j][k].y[1] * fontSize + 0.5f, 1.0f));
					spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
				}
				else if (myG.contours[j][k].degree == 2) {
					for(int l = 0; l <= myG.contours[j][k].degree; l++){
						spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[l] * fontSize + leftShift, myG.contours[j][k].y[l] * fontSize + 0.5f, 1.0f));
						spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
					}
					spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[2] * fontSize + leftShift, myG.contours[j][k].y[2] * fontSize + 0.5f, 1.0f));
					spiral.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
				}
				else if (myG.contours[j][k].degree == 3) {
					for(int l = 0; l <= myG.contours[j][k].degree; l++){
						spiral.verts.push_back(glm::vec3(myG.contours[j][k].x[l] * fontSize + leftShift, myG.contours[j][k].y[l] * fontSize + 0.5f, 1.0f));
						spiral.colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
					}
				}

				spiral.drawMode = GL_PATCHES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(spiral);

				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(spiral);

				//Add the triangle to the scene objects
				objects.push_back(spiral);
				spiral.verts.clear();
			}
		}
		leftShift = leftShift + myG.advance * fontSize;
	}
}
