#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

namespace alpha
{
	namespace core
	{
		string ASSETS_FOLDER = "Assets/";
		
		class Utility
		{
		public:
			static Vector2f Clamp(Vector2f _vec, float _radius) {
				float dist = Distance(Vector2f(0, 0), _vec);
				if (dist > _radius) {
					Vector2f newVec = (_vec * _radius) / dist;
					return newVec;
				}
				return _vec;
			}
			static float Distance(Vector2f _v1, Vector2f _v2) {
				return sqrtf(powf(_v1.x - _v2.x, 2) + powf(_v1.y - _v2.y, 2));
			}
		};
	}
}

#endif // !UTILITY_H
