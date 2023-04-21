#pragma once

#include "engine/rendering/Window.h"
#include "engine/rendering/Renderer.h"
#include "engine/rendering/Renderable.h"

#include <vector>

/*
The Control class is what is passed to the user.
It provides functions to manipulate the Window and Renderer.
Layer of functions for shader, textures, etc.
*/

class Control
{
public:
	Control(Window* window, Renderer* renderer) :
		m_WINDOW(window), m_RENDERER(renderer) {};
	~Control();
	
	const unsigned char* GetVersion();

	bool GetWindowOpen();
	void WindowClose();

	int GetWindowWidth();
	int GetWindowHeight();
	void SetWindowWidth(int width);
	void SetWindowHeight(int height);

	bool GetWindowBlending();
	void SetWindowBlending(bool blending);

	int GetRenderedObjCount();

	void WindowClear(Color color);
	void RenderClear();

	void Update();

	void EnableDebug();
protected:
	void AddRender(Renderable& renderable);
private:
	Window* m_WINDOW;
	Renderer* m_RENDERER;
};

