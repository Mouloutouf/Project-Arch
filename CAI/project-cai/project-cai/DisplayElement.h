#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Element.h"

class DisplayElement : public Element
{
public:

	DisplayElement();
	~DisplayElement();

	void Draw();

private:

	Sprite sprite;
};