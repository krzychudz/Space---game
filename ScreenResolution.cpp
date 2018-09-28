#pragma once
#include <SFML/Graphics.h>

sfVideoMode ScreenResolution = sfVideoMode_getDesktopMode();

int SCREEN_HEIGHT = ScreenResolution.height;
int SCREEN_WIDTH = ScreenResolution.width;
