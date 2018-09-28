#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.h>
#include <iostream>
#include <math.h>
#include "Bullet.h"
#include <vector>

using namespace std;

struct Player
{
	sfVector2f Player_Position;
	sfVector2f Movement;
	sfVector2i Mouse_Position;

	sfTexture * Player_Texture;
	sfSprite * Player_Sprite;

	int Lives; // Licznik ¿yæ

	sfClock * Shoot_Timer;
	float Accumulator; // ile czasu minê³o od porzedniego strza³u
	float Time_Step; // krok czasowy dla strza³u

};


void Player_Update(Player * player, std::vector<Bullet*> * PBullets)
{
	/// Szybkosc strzelania

	if (player->Accumulator < player->Time_Step)
	{
		player->Accumulator += sfTime_asSeconds(sfClock_restart(player->Shoot_Timer));
	}

	///
	player->Player_Position = sfSprite_getPosition(player->Player_Sprite);

	/// Sterowanie

	if (sfKeyboard_isKeyPressed(sfKeyW))
	{
		player->Movement = { 0.0, -5.0 };
		sfSprite_move(player->Player_Sprite, player->Movement);
	}

	if (sfKeyboard_isKeyPressed(sfKeyS))
	{
		player->Movement = { 0.0, 5.0 };
		sfSprite_move(player->Player_Sprite, player->Movement);
	}

	if (sfKeyboard_isKeyPressed(sfKeyA))
	{
		player->Movement = { -5.0, 0.0 };
		sfSprite_move(player->Player_Sprite, player->Movement);
	}

	if (sfKeyboard_isKeyPressed(sfKeyD))
	{
		player->Movement = { 5.0, 0.0 };
		sfSprite_move(player->Player_Sprite, player->Movement);
	}

	///

	/// Obracanie player'a wzglêdem myszki

	player->Mouse_Position = sfMouse_getPosition(NULL);
	float x = player->Player_Position.x - player->Mouse_Position.x;
	float y = player->Player_Position.y - player->Mouse_Position.y;

	float angle = atan2(y, x) * 180 / M_PI;

	sfSprite_setRotation(player->Player_Sprite, angle);

	///

	/// Strzelanie

	if (sfMouse_isButtonPressed(sfMouseLeft) && player->Accumulator >= player->Time_Step)
	{

		Bullet * New_Bullet = new Bullet;
		sfVector2f SpriteOrigin = { 12.5,12.5 };												//
		New_Bullet->Bullet_Texture = sfTexture_createFromFile("img/bullet.png", NULL);		//
		New_Bullet->Bullet_Sprite = sfSprite_create();										//
		sfSprite_setTexture(New_Bullet->Bullet_Sprite, New_Bullet->Bullet_Texture, sfTrue); //
		sfSprite_setOrigin(New_Bullet->Bullet_Sprite, SpriteOrigin);						//
		sfSprite_setPosition(New_Bullet->Bullet_Sprite, player->Player_Position);			//
		New_Bullet->Bullet_Position = player->Player_Position;								//
		New_Bullet->speed = 15.0;															//
		New_Bullet->Mouse_Position = sfMouse_getPosition(NULL);								//
		New_Bullet->x = New_Bullet->Mouse_Position.x - New_Bullet->Bullet_Position.x;		//
		New_Bullet->y = New_Bullet->Mouse_Position.y - New_Bullet->Bullet_Position.y;		// 
		New_Bullet->length = sqrt(New_Bullet->x*New_Bullet->x + New_Bullet->y*New_Bullet->y);//Inicjalizacja Pocisku

		float x = New_Bullet->Mouse_Position.x - New_Bullet->Bullet_Position.x;
		float y = New_Bullet->Mouse_Position.x - New_Bullet->Bullet_Position.y;

		float angle2 = atan2(y, x) * 180 / M_PI;

		sfSprite_setRotation(New_Bullet->Bullet_Sprite, angle);

		Bullet::ID += 1;
		New_Bullet->Bullet_ID = Bullet::ID;

		PBullets->push_back(New_Bullet);

		player->Accumulator = 0.0;

	}

	///
}

