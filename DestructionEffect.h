#pragma once
#include <SFML/Graphics.h>
#include <vector>

struct DestructionEffect
{
	sfTexture * DE_Texture;
	sfSprite * DE_Sprite1;
	sfSprite * DE_Sprite2;
	sfSprite * DE_Sprite3;
	sfSprite * DE_Sprite4;

	sfClock * DE_Clock;
	float DE_Time_Step;
	float DE_Accumulator;
	float DE_Speed;


};

void Add_Destruction_Effect(sfVector2f Position, std::vector<DestructionEffect*> * DE)
{
	DestructionEffect * newDE = new DestructionEffect;
	newDE->DE_Texture = sfTexture_createFromFile("img/destruction.png", NULL);
	newDE->DE_Sprite1 = sfSprite_create();
	newDE->DE_Sprite2 = sfSprite_create();
	newDE->DE_Sprite3 = sfSprite_create();
	newDE->DE_Sprite4 = sfSprite_create();

	sfSprite_setTexture(newDE->DE_Sprite1, newDE->DE_Texture, NULL);
	sfSprite_setTexture(newDE->DE_Sprite2, newDE->DE_Texture, NULL);
	sfSprite_setTexture(newDE->DE_Sprite3, newDE->DE_Texture, NULL);
	sfSprite_setTexture(newDE->DE_Sprite4, newDE->DE_Texture, NULL);

	sfSprite_setPosition(newDE->DE_Sprite1, Position);
	sfSprite_setRotation(newDE->DE_Sprite1, 0.0);

	sfSprite_setPosition(newDE->DE_Sprite2, Position);
	sfSprite_setRotation(newDE->DE_Sprite2, 90.0);

	sfSprite_setPosition(newDE->DE_Sprite3, Position);
	sfSprite_setRotation(newDE->DE_Sprite3, 180.0);

	sfSprite_setPosition(newDE->DE_Sprite4, Position);
	sfSprite_setRotation(newDE->DE_Sprite4, 270.0);

	newDE->DE_Accumulator = 0.0;
	newDE->DE_Clock = sfClock_create();
	newDE->DE_Time_Step = 0.5f;
	newDE->DE_Speed = 4.0;

	DE->push_back(newDE);

}

void Destruction_Effect_Update(DestructionEffect * DE, std::vector<DestructionEffect*> * DE_vec)
{
	DE->DE_Accumulator += sfTime_asSeconds(sfClock_restart(DE->DE_Clock));

	sfVector2f move_vec = { -DE->DE_Speed, 0 };
	sfSprite_move(DE->DE_Sprite1, move_vec);

	move_vec = { 0,-DE->DE_Speed };
	sfSprite_move(DE->DE_Sprite2, move_vec);

	move_vec = { DE->DE_Speed,0 };
	sfSprite_move(DE->DE_Sprite3, move_vec);

	move_vec = { 0,DE->DE_Speed };
	sfSprite_move(DE->DE_Sprite4, move_vec);

	if (DE->DE_Accumulator >= DE->DE_Time_Step)
	{
		sfSprite_destroy(DE->DE_Sprite1);
		sfSprite_destroy(DE->DE_Sprite2);
		sfSprite_destroy(DE->DE_Sprite3);
		sfSprite_destroy(DE->DE_Sprite4);

		DE->DE_Sprite1 = NULL;
		DE->DE_Sprite2 = NULL;
		DE->DE_Sprite3 = NULL;
		DE->DE_Sprite4 = NULL;

		delete DE;

		DE_vec->erase(DE_vec->begin());
	}

}