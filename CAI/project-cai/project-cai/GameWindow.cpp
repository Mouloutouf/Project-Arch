#include "GameWindow.h"

GameWindow::GameWindow(string _projectName, float _width, float _height)
{
	width = _width;
	height = _height;
	InitializeWindow(width, height, _projectName);
}

GameWindow::~GameWindow()
{
	delete window;
}

void GameWindow::InitializeWindow(float _width, float _height, string _title)
{
	window = new RenderWindow(VideoMode(_width, _height), _title);
}

Vector2f GameWindow::GetWindowDimensions()
{
	return Vector2f(width, height);
}
