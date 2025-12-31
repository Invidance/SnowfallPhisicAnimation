#include "stdafx.h"
#include "raylib.h"
#include "Core/Easing.h"
#include "Components/Slider.h"
#include "SnowfallApp.h"

using namespace Core;

int main()
{
	InitWindow(CONSTS::SCREEN_WIDTH, CONSTS::SCREEN_HEIGHT, "Effects System");
	
	SetTargetFPS(120);
	SnowfallApp* app = new SnowfallApp();
	app->init();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		app->draw();
		EndDrawing();
	}

	delete app;

	CloseWindow();
	return 0;
}
