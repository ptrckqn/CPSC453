/*
 * Scene.cpp
 *
 *  Author: Patrick Quan and Jason Li
 		ID's: 10152770 (Patrick), 10158349 (Jason)
		Based off Boilerplate provided by John Hall

		Q, W, E and, R to change scenes
		Up and down arrow keys to increase and decrease level.
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
	void squareAndDiamond(int levels);
	void levelUp();
	void levelDown();
	void spiral(int revolutions);
	void spongeSquare(float startX, float startY, int levels, int levelsTwo);
	void dot(int levels);

	int squareCount = 2;
	int spiralCount =  2;
	int spongeCount = 2;
	int dotCount = 1000;

private:
	RenderingEngine* renderer;

	//list of objects in the scene
	std::vector<Geometry> objects;

	std::string type;
};

#endif /* SCENE_H_ */
