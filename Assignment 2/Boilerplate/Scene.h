/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"

#include <string>

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();


	//Send geometry to the renderer
	void displayScene();
	void newImg (std::string fileName);
	void transform(std::string fileName, double x, double y);
	void scale(std::string fileName, double sFactor);
	void rotate(std::string fileName, double rFactor);
	void bgImg(std::string bgName);

	GLuint GLgrayscale;
	GLuint GLsobel;
	GLuint GLgaus;

	void grayscale(int gs);
	void sobel(int sobelNum);
	void gaus(int gaussian);

private:
	RenderingEngine* renderer;

	Geometry rectangle;
	Geometry rectangleTwo;

	//list of objects in the scene
	std::vector<Geometry> objects;

	int gs;
	int sobelNum;
	int gaussian;
};

#endif /* SCENE_H_ */
