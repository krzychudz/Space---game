#pragma once
#include <SFML/Graphics.h>
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>
using namespace std;

int Check_Collision_Player_Enemy(Player * player, Enemy * enemy)
{
	sfFloatRect Player_Rect = sfSprite_getGlobalBounds(player->Player_Sprite);
	sfFloatRect Enemy_Rect = sfSprite_getGlobalBounds(enemy->Enemy_Sprite);

	if (sfFloatRect_intersects(&Player_Rect, &Enemy_Rect, NULL))
		return 1;

	return 0;


}


int Check_Collision_Bullet_Enemy(Bullet * bullet, Enemy * enemy)
{
	sfFloatRect Bullet_Rect = sfSprite_getGlobalBounds(bullet->Bullet_Sprite);
	sfFloatRect Enemy_Rect = sfSprite_getGlobalBounds(enemy->Enemy_Sprite);

	if (sfFloatRect_intersects(&Bullet_Rect, &Enemy_Rect, NULL))
		return 1;
	
	return 0;
}

void Remove_Bullets_From_Vector(Bullet * bullet, std::vector<Bullet*> * Bullets)
{
	int tmpID = bullet->Bullet_ID; // Pobieranie ID, aby mo¿na by³o go póŸniej u¿yæ
	Bullet * Bullet_To_Remove = bullet; // WskaŸnik do miejsca Bulleta w pamiêci 

	Bullets->erase(Bullets->begin() + bullet->Bullet_ID);// kolizja

	sfSprite_destroy(bullet->Bullet_Sprite);
	sfTexture_destroy(bullet->Bullet_Texture);

	Bullet::ID -= 1;

	for (int x = tmpID; x < Bullets->size(); x++) // cofanie ID obiektów o 1
		(*Bullets)[x]->Bullet_ID -= 1;

	delete Bullet_To_Remove; // usuwanie pocisku z pamiêci

}

void Remove_Enemy_From_Vector(Enemy * enemy, std::vector<Enemy*> * Enemies)
{
	int tmpID = enemy->Enemy_ID;
	Enemy * Enemy_To_Remove = enemy;

	Enemies->erase(Enemies->begin() + enemy->Enemy_ID);

	sfSprite_destroy(enemy->Enemy_Sprite);
	sfTexture_destroy(enemy->Enemy_Texture);
	Enemy::ID -= 1;

	for (int x = tmpID; x < Enemies->size(); x++)
		(*Enemies)[x]->Enemy_ID -= 1;

	delete Enemy_To_Remove;

}
