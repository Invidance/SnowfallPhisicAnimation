#include "stdafx.h"
#include "SnowfallApp.h"
#include "Core/Object.h"
#include "System/Canvas.h"
#include "System/Sidebar.h"

using namespace Core;

SnowfallApp::SnowfallApp()
{
	clearParams();
}
SnowfallApp::~SnowfallApp()
{
	clearParams();
}
// VIRTUAL FUNCS
void SnowfallApp::init()
{
	Application::init();

	Canvas* canvas = new Canvas();
	registerObject(canvas);
	canvas->setWidth(CONSTS::SCREEN_WIDTH * 0.8f);
	canvas->setHeight((float)CONSTS::SCREEN_HEIGHT);
	canvas->init();

	Sidebar* sidebar = new Sidebar();
	registerObject(sidebar);
	sidebar->setX(CONSTS::SCREEN_WIDTH * 0.8f);
	sidebar->setWidth(CONSTS::SCREEN_WIDTH * 0.2f);
	sidebar->setHeight((float)CONSTS::SCREEN_HEIGHT);
	sidebar->init();
	sidebar->registerCallback(canvas);
}

// FUNCS
void SnowfallApp::clearParams()
{
}