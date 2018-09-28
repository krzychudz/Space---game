#pragma once
#include <SFML/Graphics.h>
#include <iostream>

struct Bullet
{
	sfVector2f Bullet_Position;
	sfVector2i Mouse_Position;
	sfVector2f Bullet_Movement;

	sfTexture * Bullet_Texture;
	sfSprite * Bullet_Sprite;

	float speed;
	float x; // odleg³oœc w x od myszki
	float y; // odleg³oœæ w y od myszki
	float length; // d³ugoœæ wektora pocisk - myszka

	int Bullet_ID; // Lokalne ID ka¿dego bulleta

	static int ID; // statyczna zmienna ID

};

int Bullet::ID = -1;

void Bullet_Update(Bullet * bullet)
	{
		bullet->Bullet_Position = sfSprite_getPosition(bullet->Bullet_Sprite);
		bullet->Bullet_Movement = { bullet->x * bullet->speed / bullet->length
			, bullet->y * bullet->speed / bullet->length }; // Wekotr oraz jego normalizacja(dzielenie przez d³ugoœæ)
		sfSprite_move(bullet->Bullet_Sprite, bullet->Bullet_Movement);
	}




