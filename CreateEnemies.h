#pragma once
#include <vector>
#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include "ScreenResolution.cpp"
using namespace std;



void Create_Enemies(std::vector<Enemy*> * PEnemies)
{

	float Part_Of_Screen = (rand() % 4) + 1; // Losowanie w której czêœci ekarnu zostanie utworzony przeciwnik
	float x, y; // Pozycja w której zostanie utworzony nowy przeciwnik
	
	if (Part_Of_Screen == 1) // Prawy górny róg
	{
		 x = (rand() % 100) + SCREEN_WIDTH + 25;
		 y = (rand() % (SCREEN_HEIGHT)) + SCREEN_HEIGHT / 2 - SCREEN_HEIGHT;
	}
	else if (Part_Of_Screen == 2) // Lewy górny
	{
		x = (rand() % 100) - 100;
		y = (rand() % (SCREEN_HEIGHT)) + SCREEN_HEIGHT / 2 - SCREEN_HEIGHT;
	}
	else if (Part_Of_Screen == 3) // Lewy dolny
	{
		x = (rand() % 100) - 100;
		y = (rand() % (SCREEN_HEIGHT)) + SCREEN_HEIGHT / 2;
	}
	else // Prawy dolny
	{
		x = (rand() % 100) + SCREEN_WIDTH + 25;
		y = (rand() % (SCREEN_HEIGHT)) + SCREEN_HEIGHT / 2;
	}


	Enemy * enemy = new Enemy;

	sfVector2f SpriteOrigin = { 12.5,12.5 };									//
	sfVector2f Enemy_Position = { x,y };										//
	enemy->Enemy_Texture = sfTexture_createFromFile("img/enemy.png", NULL);		//
	enemy->Enemy_Sprite = sfSprite_create();									//
	sfSprite_setTexture(enemy->Enemy_Sprite, enemy->Enemy_Texture, sfTrue);		//
	sfSprite_setOrigin(enemy->Enemy_Sprite, SpriteOrigin);						//
	sfSprite_setPosition(enemy->Enemy_Sprite, Enemy_Position);					// Inicjalizacja przeciwknika
	enemy->speed = 2.0;															//
	Enemy::ID += 1;																//
	enemy->Enemy_ID = Enemy::ID;												//
	PEnemies->push_back(enemy);													//
}