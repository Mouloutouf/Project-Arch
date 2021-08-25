#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <random>
#include "Alpha.h"

///\

namespace alpha
{
	namespace core
	{
#pragma region FILES

		const string ASSETS_FOLDER = "Assets/";

#pragma endregion

#pragma region COLORS

		const Color BACKGROUND_COLOR = Color(43, 46, 59);
		const Color DETAIL_COLOR = Color(67, 82, 104);

		const Color GREEN_COLOR = Color(131, 255, 70);
		const Color RED_COLOR = Color(255, 55, 55);
		const Color BLUE_COLOR = Color(44, 135, 255);

#pragma endregion

		class Utility
		{
		public:

#pragma region MATH

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

			static int powerOf(float _value, int _base) {
				int r = 0;
				while (_value >= _base) { _value /= _base; ++r; }
				return r;
			}
			static float pceil(float _value, int _base) {
				float mod = (float)fmod(_value, _base);
				_value += (_value > 0 ? _base : 0 - mod);
				return _value;
			}
			static float pfloor(float _value, int _base) {
				float mod = _value > 0 ? (float)fmod(_value, _base) : (float)fmod(_base, _value);
				_value -= mod;
				return _value;
			}

#pragma endregion
			
			template<typename I>
			static I GetRandomIterator(I begin, I end)
			{
				const unsigned long n = distance(begin, end);
				const unsigned long divisor = (RAND_MAX + 1) / n;

				unsigned long k;
				do { k = rand() / divisor; } while (k >= n);

				std::advance(begin, k);
				return begin;
			}

			template<typename T>
			static T GetRandomElementFromContainer(const vector<T>& _container)
			{
				vector<T> result;
				sample( _container.begin(), _container.end(), back_inserter(result), 1, mt19937 { random_device {}() });
				return result.front();
			}
		};
	}
}

#endif // !UTILITY_H
