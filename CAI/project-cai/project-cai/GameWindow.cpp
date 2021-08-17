#include "GameWindow.h"

namespace alpha
{
	namespace core
	{
		GameWindow::GameWindow(string _name, int _width, int _height)
			: width(_width), height(_height), name(_name)
		{
			window = new RenderWindow(VideoMode(_width, _height), _name);
		}

		GameWindow::GameWindow(const GameWindow& that)
			: width(that.width), height(that.height), name(that.name)
		{
			window = new RenderWindow(VideoMode(that.width, that.height), that.name);
		}

		GameWindow& GameWindow::operator=(const GameWindow& that)
		{
			if (this != &that)
			{
				RenderWindow* newWindow = new RenderWindow(VideoMode(that.width, that.height), that.name);
				delete window;
				window = newWindow;

				width = that.width;
				height = that.height;
				name = that.name;
			}
			return *this;
		}

		GameWindow::~GameWindow()
		{
			delete window;
		}
	}
}
