#pragma once
#include <SFML/Graphics.h>
#include <math.h>

struct Enemy
{
	sfVector2f Enemy_Position;
	sfVector2f Enemy_Movement; // wektor przesuniêcia do gracza

	float speed;

	sfTexture * Enemy_Texture;
	sfSprite * Enemy_Sprite;

	int Enemy_ID; // lokalne ID

	static int ID; // statyczna zmienna ID

};

int Enemy::ID = -1;

void Enemy_Update(Enemy * enemy, sfVector2f Player_Position)
{
	enemy->Enemy_Position = sfSprite_getPosition(enemy->Enemy_Sprite);

	float x = Player_Position.x - enemy->Enemy_Position.x;
	float y = Player_Position.y - enemy->Enemy_Position.y;
	float length = sqrt(x*x + y*y); // d³ogœæ wektora potrzebna do normalizacji

	if (enemy->Enemy_Position.x == Player_Position.x && enemy->Enemy_Position.y == Player_Position.y)
		enemy->Enemy_Movement = { 0,0 }; // je¿eli pozycja taka sama to nie ma ruchu
	else
		enemy->Enemy_Movement = { x * enemy->speed / length , y * enemy->speed / length };

	sfSprite_move(enemy->Enemy_Sprite, enemy->Enemy_Movement);

}