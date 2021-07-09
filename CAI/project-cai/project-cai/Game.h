#pragma once

#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Content.h"

class GameObject;
class SpaceShip;
class Background;
class Spawner;

class Game
{
public:

	Game(Vector2f windowDimensions);
	~Game();

	Content * gameContent;

	vector<GameObject *> gameObjects;
};

#endif // !GAME_H
