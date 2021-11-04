#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <chrono>
#include <algorithm>
#include <random>
#include "Alpha.h"

///\

namespace alpha
{
	namespace core
	{
#define _TIME chrono::system_clock::to_time_t(chrono::system_clock::now())

#pragma region FILES

		const string ASSETS_FOLDER = "Assets/";
		const string FONTS_FOLDER = ASSETS_FOLDER + "Fonts/";

#pragma endregion

#pragma region FONTS

		const string TEXT_FONT = FONTS_FOLDER + "SourceCodePro-Regular" + ".ttf";

#pragma endregion

#pragma region COLORS

		const Color DARK_BLACK = Color(0, 4, 5);
		const Color BACKGROUND_BLACK = Color(1, 9, 12);
		const Color DARK_GREY_BLUE = Color(4, 21, 28);
		const Color DARK_TEAL_BLUE = Color(6, 40, 53);
		const Color GREY_BLUE = Color(56, 95, 127);
		const Color DETAIL_GREY_BLUE = Color(111, 149, 178);
		const Color WHITE_BLUE = Color(179, 212, 229);

		const Color BACKGROUND_COLOR = Color(43, 46, 59);
		const Color DETAIL_COLOR = Color(67, 82, 104);

		const Color GREEN_COLOR = Color(131, 255, 70);
		const Color RED_COLOR = Color(255, 55, 55);
		const Color BLUE_COLOR = Color(44, 135, 255);

#pragma endregion

		const string DEFAULT_SPRITE = ASSETS_FOLDER + "Default/" + "Default Sprite" + ".png";

		class Utility
		{
		public:

			static string spritePath(string _sprite) { return ASSETS_FOLDER + _sprite + ".png"; }

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
			
#pragma region RANDOM

			template<typename I>
			static I GetRandomIterator(I _begin, I _end)
			{
				const unsigned long n = distance(_begin, _end);
				const unsigned long divisor = (RAND_MAX + 1) / n;

				unsigned long k;
				do { k = rand() / divisor; } while (k >= n);

				advance(_begin, k);
				return _begin;
			}

			template<typename T>
			static T GetRandomElementFromContainer(const vector<T>& _container)
			{
				vector<T> result;
				sample(_container.begin(), _container.end(), back_inserter(result), 1, mt19937{ random_device {}() });
				return result.front();
			}

			static int GetRandomNumberInRange(int _min, int _max)
			{
				random_device rd;
				mt19937 mt(rd());

				uniform_int_distribution dist(_min, _max);
				return dist(mt) + _min;
			}

#pragma endregion

			template<typename T>
			static bool Contains(const vector<T>& _vector, const T& _value)
			{
				return find(_vector.begin(), _vector.end(), _value) != _vector.end();
			}
		};
	}
}

#endif // !UTILITY_H
