// proj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/graphics.h>
#include "MainMenu.h"
#include "ScreenResolution.cpp"
#include <stdlib.h>
#include <ctime>

int main()
{
	srand(time(NULL));

	sfVideoMode vm = { SCREEN_WIDTH,SCREEN_HEIGHT,32 };
	sfRenderWindow * window = sfRenderWindow_create(vm, "Gra", sfFullscreen, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
	Main_Menu(window);

    return 0;
}

