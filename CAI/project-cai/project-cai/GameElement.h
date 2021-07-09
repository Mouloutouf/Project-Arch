#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Element.h"

class GameElement : public Element
{
public:

	GameElement();
	~GameElement();

	void Init();
	void Update();
};