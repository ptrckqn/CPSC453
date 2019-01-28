/*
 * Scene.cpp
 *
 *  Author: Patrick Quan and Jason Li
 		ID's: 10152770 (Patrick), 10158349 (Jason)
		Based off Boilerplate provided by John Hall

		Q, W, E and, R to change scenes
		Up and down arrow keys to increase and decrease level.
 */

#include "Scene.h"

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	// //Create a single triangle
	// //Additional triangles can be created by pushing groups of three more vertices into the verts vector
	// Geometry triangle;
	// triangle.verts.push_back(glm::vec3(-0.6f, -0.4f, 1.0f));
	// triangle.verts.push_back(glm::vec3(0.0f, 0.6f, 1.0f));
	// triangle.verts.push_back(glm::vec3(0.6f, -0.4f, 1.0f));
	//
	// //Colors are stored per vertex in the order of the vertices
	// triangle.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// triangle.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// triangle.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	//
	// triangle.drawMode = GL_TRIANGLES;
	//
	// //Construct vao and vbos for the triangle
	// RenderingEngine::assignBuffers(triangle);
	//
	// //Send the triangle data to the GPU
	// //Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	// RenderingEngine::setBufferData(triangle);
	//
	// //Add the triangle to the scene objects
	// objects.push_back(triangle);
	//
	// The first default scene is the Square scene
	squareAndDiamond(1);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::squareAndDiamond(int levels){
	type = "squareAndDiamond";
	objects.clear();
	Geometry squareAndDiamond;
	int count = levels;

	for(int i = 0; i < count; i++){
		float lineLength = 0.9;

		if(i != 0){
			lineLength = lineLength * std::pow(0.4998, i);
		}

		squareAndDiamond.verts.push_back(glm::vec3(-lineLength, -lineLength, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(lineLength, -lineLength, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(lineLength, lineLength, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(-lineLength, lineLength, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(-lineLength, -lineLength, 0.0f));

		squareAndDiamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

		squareAndDiamond.verts.push_back(glm::vec3(0.0f, -lineLength, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(lineLength, 0.0f, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(0.0f, lineLength, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(-lineLength, 0.0f, 0.0f));
		squareAndDiamond.verts.push_back(glm::vec3(0.0f, -lineLength, 0.0f));

		squareAndDiamond.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		squareAndDiamond.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	}

	squareAndDiamond.drawMode = GL_LINE_STRIP;
	RenderingEngine::assignBuffers(squareAndDiamond);
	RenderingEngine::setBufferData(squareAndDiamond);
	objects.push_back(squareAndDiamond);
}

void Scene::spiral(int revolutions){
	objects.clear();
	type = "spiral";
	Geometry spiral;
	int count = revolutions;

	float lines = 50;
	float upperLimit = M_PI* (2 * (revolutions - 1) + 6);
	float steps = (M_PI * 2) / lines;


	for(float i = 0; i < upperLimit; i = i + steps){
		spiral.verts.push_back(glm::vec3((i * cos(i) / 100.0), (i * sin(i) / 100.0), 0.0));
		spiral.colors.push_back(glm::vec3(i, i, i));
	}

	spiral.drawMode = GL_LINE_STRIP;
	RenderingEngine::assignBuffers(spiral);
	RenderingEngine::setBufferData(spiral);
	objects.push_back(spiral);
}

void Scene::spongeSquare(float startX, float startY, int levels, int count){

	int steps = levels;
	if(count == 1){
		objects.clear();
	}

	if(levels > 1){
		spongeSquare(startX, startY, levels - 1, count++);
		spongeSquare(startX + 2 / pow(3, count), startY, levels - 1, count++);
		spongeSquare(startX + 2 * (2 / pow(3, count)), startY, levels - 1, count++);
		spongeSquare(startX, startY - 2 / pow(3, count), levels - 1, count++);
		spongeSquare(startX + 2 * (2 / pow(3, count)), startY - 2 / pow(3, count), levels - 1, count++);
		spongeSquare(startX, startY - 2 * (2 / pow(3, count)), levels - 1, count++);
		spongeSquare(startX + 2 / pow(3, count), startY - 2 * (2 / pow(3, count)), levels - 1, count++);
		spongeSquare(startX + 2 * (2 / pow(3, count)), startY - 2 * (2 / pow(3, count)), levels - 1, count++);

	}

	else if(levels == 0){
		type = "spongeSquare";
		objects.clear();
		Geometry spongeSquareOne;

		spongeSquareOne.verts.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
		spongeSquareOne.verts.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
		spongeSquareOne.verts.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
		spongeSquareOne.verts.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		spongeSquareOne.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		spongeSquareOne.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		spongeSquareOne.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		spongeSquareOne.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

		spongeSquareOne.drawMode = GL_TRIANGLE_STRIP;
		RenderingEngine::assignBuffers(spongeSquareOne);
		RenderingEngine::setBufferData(spongeSquareOne);
		objects.push_back(spongeSquareOne);
	}

	else {
			Geometry spongeSquareOne;
			spongeSquareOne.verts.push_back(glm::vec3(startX , startY, 1.0f));
			spongeSquareOne.verts.push_back(glm::vec3(startX, startY - 2 / pow(3, count), 1.0f));
			spongeSquareOne.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY, 1.0f));
			spongeSquareOne.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY - 2 / pow(3, count), 1.0f));

			spongeSquareOne.colors.push_back(glm::vec3(0.0f, 0.0f, 0.4f));
			spongeSquareOne.colors.push_back(glm::vec3(0.0f, 0.0f, 0.4f));
			spongeSquareOne.colors.push_back(glm::vec3(0.0f, 0.0f, 0.4f));
			spongeSquareOne.colors.push_back(glm::vec3(0.0f, 0.0f, 0.4f));


			spongeSquareOne.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareOne);
			RenderingEngine::setBufferData(spongeSquareOne);
			objects.push_back(spongeSquareOne);

			Geometry spongeSquareTwo;

			spongeSquareTwo.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY, 1.0f));
			spongeSquareTwo.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY - 2 / pow(3, count), 1.0f));
			spongeSquareTwo.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY, 1.0f));
			spongeSquareTwo.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY - 2 / pow(3, count), 1.0f));

			spongeSquareTwo.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareTwo.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareTwo.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareTwo.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));

			spongeSquareTwo.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareTwo);
			RenderingEngine::setBufferData(spongeSquareTwo);
			objects.push_back(spongeSquareTwo);

			Geometry spongeSquareThree;

			spongeSquareThree.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY, 1.0f));
			spongeSquareThree.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 2 / pow(3, count), 1.0f));
			spongeSquareThree.verts.push_back(glm::vec3(startX + 3 * (2 / pow(3, count)), startY, 1.0f));
			spongeSquareThree.verts.push_back(glm::vec3(startX + 3 * (2 / pow(3, count)), startY- 2 / pow(3, count), 1.0f));

			spongeSquareThree.colors.push_back(glm::vec3(0.4f, 0.0f, 0.0f));
			spongeSquareThree.colors.push_back(glm::vec3(0.4f, 0.0f, 0.0f));
			spongeSquareThree.colors.push_back(glm::vec3(0.4f, 0.0f, 0.0f));
			spongeSquareThree.colors.push_back(glm::vec3(0.4f, 0.0f, 0.0f));

			spongeSquareThree.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareThree);
			RenderingEngine::setBufferData(spongeSquareThree);
			objects.push_back(spongeSquareThree);

			Geometry spongeSquareFour;
			spongeSquareFour.verts.push_back(glm::vec3(startX, startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareFour.verts.push_back(glm::vec3(startX, startY- 2 / pow(3, count), 1.0f));
			spongeSquareFour.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareFour.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY- 2 / pow(3, count), 1.0f));

			spongeSquareFour.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareFour.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareFour.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareFour.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));

			spongeSquareFour.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareFour);
			RenderingEngine::setBufferData(spongeSquareFour);
			objects.push_back(spongeSquareFour);



			Geometry spongeSquareFive;

			spongeSquareFive.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareFive.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 2 / pow(3, count), 1.0f));
			spongeSquareFive.verts.push_back(glm::vec3(startX + 3 * (2 / pow(3, count)), startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareFive.verts.push_back(glm::vec3(startX + 3 * (2 / pow(3, count)), startY- 2 / pow(3, count), 1.0f));

			spongeSquareFive.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareFive.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareFive.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareFive.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));

			spongeSquareFive.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareFive);
			RenderingEngine::setBufferData(spongeSquareFive);
			objects.push_back(spongeSquareFive);

			Geometry spongeSquareSix;
			spongeSquareSix.verts.push_back(glm::vec3(startX, startY- 3 * (2 / pow(3, count)), 1.0f));
			spongeSquareSix.verts.push_back(glm::vec3(startX, startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareSix.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY- 3 * (2 / pow(3, count)), 1.0f));
			spongeSquareSix.verts.push_back(glm::vec3(startX + 2 / pow(3, count), startY- 2 * (2 / pow(3, count)), 1.0f));

			spongeSquareSix.colors.push_back(glm::vec3(0.3f, 0.0f, 0.4f));
			spongeSquareSix.colors.push_back(glm::vec3(0.3f, 0.0f, 0.4f));
			spongeSquareSix.colors.push_back(glm::vec3(0.3f, 0.0f, 0.4f));
			spongeSquareSix.colors.push_back(glm::vec3(0.3f, 0.0f, 0.4f));

			spongeSquareSix.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareSix);
			RenderingEngine::setBufferData(spongeSquareSix);
			objects.push_back(spongeSquareSix);

			Geometry spongeSquareSeven;

			spongeSquareSeven.verts.push_back(glm::vec3(startX + (2 / pow(3, count)), startY- 3 * (2 / pow(3, count)), 1.0f));
			spongeSquareSeven.verts.push_back(glm::vec3(startX + (2 / pow(3, count)), startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareSeven.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 3 * (2 / pow(3, count)), 1.0f));
			spongeSquareSeven.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 2 * (2 / pow(3, count)), 1.0f));

			spongeSquareSeven.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareSeven.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareSeven.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));
			spongeSquareSeven.colors.push_back(glm::vec3(0.4f, 0.4f, 0.4f));

			spongeSquareSeven.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareSeven);
			RenderingEngine::setBufferData(spongeSquareSeven);
			objects.push_back(spongeSquareSeven);

			Geometry spongeSquareEight;

			spongeSquareEight.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 3 * (2 / pow(3, count)), 1.0f));
			spongeSquareEight.verts.push_back(glm::vec3(startX + 2 * (2 / pow(3, count)), startY- 2 * (2 / pow(3, count)), 1.0f));
			spongeSquareEight.verts.push_back(glm::vec3(startX + 3 * (2 / pow(3, count)), startY- 3 * (2 / pow(3, count)), 1.0f));
			spongeSquareEight.verts.push_back(glm::vec3(startX + 3 * (2 / pow(3, count)), startY- 2 * (2 / pow(3, count)), 1.0f));

			spongeSquareEight.colors.push_back(glm::vec3(0.0f, 0.4f, 0.0f));
			spongeSquareEight.colors.push_back(glm::vec3(0.0f, 0.4f, 0.0f));
			spongeSquareEight.colors.push_back(glm::vec3(0.0f, 0.4f, 0.0f));
			spongeSquareEight.colors.push_back(glm::vec3(0.0f, 0.4f, 0.0f));

			spongeSquareEight.drawMode = GL_TRIANGLE_STRIP;
			RenderingEngine::assignBuffers(spongeSquareEight);
			RenderingEngine::setBufferData(spongeSquareEight);
			objects.push_back(spongeSquareEight);

	}
}

void Scene::dot(int levels){
	objects.clear();
	type = "dot" ;
	Geometry dots;
	float startX = 0.0f;
	float startY = 1.0f;

	for (int i = 0; i < levels; i++){

		switch(rand() % 3){
			case 0:
				startX = startX * 0.5;
				startY = (startY + 1.0f) * 0.5;
				break;
			case 1:
				startX = (startX - 1.0f) * 0.5;
				startY = (startY - 1.0f) * 0.5;
				break;
			case 2:
				startX = (startX + 1.0f) * 0.5;
				startY = (startY - 1.0f) * 0.5;
		}


		dots.verts.push_back(glm::vec3(startX, startY, 0.0f));
		dots.colors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
		dots.drawMode = GL_POINTS;
		RenderingEngine::assignBuffers(dots);
		RenderingEngine::setBufferData(dots);
		objects.push_back(dots);
	}
}

void Scene::levelUp(){
	if (type == "squareAndDiamond")
	{
		squareAndDiamond(squareCount++);
	}
	else if (type == "spiral")
	{
		spiral(spiralCount++);
	}
	else if (type == "spongeSquare")
	{
		spongeSquare(-1.0f, 1.0f, spongeCount++, 1);
	}
	else if(type == "dot"){
		dot(dotCount);
		if(dotCount < 1000000){
			dotCount = dotCount + 1000;
		}

	}
}
//
// TODO FIX LEVEL DOWN
void Scene::levelDown()
{
	if (type == "squareAndDiamond")
	{
		squareCount = squareCount - 1;
		squareAndDiamond(squareCount);
	}
	else if (type == "spiral")
	{
		spiralCount = spiralCount - 1;
		spiral(spiralCount);
	}
	else if (type == "spongeSquare")
	{
		spongeCount = spongeCount - 1;
		spongeSquare(-1.0f, 1.0f, spongeCount, 1);
	}
	else if(type == "dot"){
		dotCount = dotCount - 1000;
		dot(dotCount);
	}
}
