#include "GameWindow.h"

GameWindow::GameWindow(string gameName, float width, float height)
{
	windowWidth = width;
	windowHeight = height;
	InitializeWindow(windowWidth, windowHeight, gameName);
}

GameWindow::~GameWindow()
{
	delete window;
}

void GameWindow::InitializeWindow(float width, float height, string title)
{
	window = new RenderWindow(VideoMode(width, height), title);
}

Vector2f * GameWindow::GetWindowDimensions()
{
	return new Vector2f(windowWidth, windowHeight);
}
