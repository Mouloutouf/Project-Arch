#include "GameWindow.h"

namespace alpha
{
	namespace core
	{
		GameWindow::GameWindow(string _name, int _width, int _height)
			: width(_width), height(_height), name(_name)
		{
			//window = new RenderWindow(VideoMode(_width, _height), _name, Style::Fullscreen);
			window = new RenderWindow(VideoMode::getFullscreenModes()[0], _name, Style::Fullscreen);
			//window = new RenderWindow(VideoMode::getDesktopMode(), _name);
		}

		GameWindow::GameWindow(const GameWindow& that)
			: width(that.width), height(that.height), name(that.name)
		{
			//window = new RenderWindow(VideoMode(that.width, that.height), that.name, Style::Fullscreen);
			window = new RenderWindow(VideoMode::getFullscreenModes()[0], that.name, Style::Fullscreen);
			//window = new RenderWindow(VideoMode::getDesktopMode(), that.name);
		}

		GameWindow& GameWindow::operator=(const GameWindow& that)
		{
			if (this != &that)
			{
				//RenderWindow* newWindow = new RenderWindow(VideoMode(that.width, that.height), that.name);
				RenderWindow* newWindow = new RenderWindow(VideoMode::getFullscreenModes()[0], that.name, Style::Fullscreen);
				//RenderWindow* newWindow = new RenderWindow(VideoMode::getDesktopMode(), that.name);
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
