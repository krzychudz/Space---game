#pragma once
#include <iostream>
#include <vector>
#include <SFML/graphics.h>
#include "Player.h"
#include <math.h>
#include "Enemy.h"
#include "CreateEnemies.h"
#include "Collision.h"
#include "ScreenResolution.cpp"
#include "GameOver.h"
#include "DestructionEffect.h"

void Game(sfRenderWindow * window)
{

	float Time_Enemy_Spawn = 1.5; // co jaki czas bêdzie tworzony przeciwnik
	float Accumulator = 0.0;
	float Show_Message_Time_Step = 20.0;
	float Message_Accumulator= 0.0;
	int Total_Score = 0; // Punkty
	int collisionBE = false; // zmienna pomocnicza w kolizji
	int ShowMessage = 0; // zmienna informujaca czy wyswietlic aktualnie wiadomosc

	sfClock * Enemy_Spawn_Clock = sfClock_create();
	sfClock * Message_Clock = sfClock_create();

	std::vector<Bullet*> Bullets;
	std::vector<Enemy*> Enemies; // Vector przechowuj¹cy struktury Enemy

	std::vector<DestructionEffect*>	Destruction_Effects;


	

	Player * player = new Player;
	sfVector2f Sprite_Origin;//
	sfVector2f Player_Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	sfFloatRect Player_Rect;
	player->Player_Texture = sfTexture_createFromFile("img/player.png", NULL);	//
	player->Player_Sprite = sfSprite_create();									//
	sfSprite_setTexture(player->Player_Sprite, player->Player_Texture, sfTrue);	//
	Player_Rect = sfSprite_getGlobalBounds(player->Player_Sprite);				// pobieranie rect'a
	Sprite_Origin = { Player_Rect.width / 2, Player_Rect.height / 2 };			//
	sfSprite_setOrigin(player->Player_Sprite, Sprite_Origin);					//
	sfSprite_setPosition(player->Player_Sprite, Player_Position);				//
	player->Accumulator = 0.0;													//
	player->Time_Step = 0.5;													//
	player->Shoot_Timer = sfClock_create();										// Inicjalizacja gracza
	player->Lives = 3;


	//PUNKTY
	
	sfFont* Font; // font
	Font = sfFont_createFromFile("img/Mecha_Bold.ttf"); // wczytanie czcionki

	sfText* Score_Text;
	sfVector2f position = {10,10};
	Score_Text = sfText_create(); // stworzenie textu
	sfText_setString(Score_Text, "0");
	sfText_setFont(Score_Text, Font);
	sfText_setCharacterSize(Score_Text, 40);
	sfText_setPosition(Score_Text, position);

	//POZIOMY
	int Next_Level_Score = 500; // zmienna okresj¹ca ile punktów nale¿y zdobyæ do nastêpnego poziomu
	position = { 120,10 };
	sfText* Next_Level_Text;
	Next_Level_Text = sfText_create(); // stworzenie textu
	sfText_setString(Next_Level_Text, "500");
	sfText_setFont(Next_Level_Text, Font);
	sfText_setCharacterSize(Next_Level_Text, 40);
	sfText_setPosition(Next_Level_Text, position);
	//
	//ukoœnik

	sfText* Slash;
	position = { 95,10 };
	Slash = sfText_create(); // stworzenie textu
	sfText_setString(Slash, "/");
	sfText_setFont(Slash, Font);
	sfText_setCharacterSize(Slash, 40);
	sfText_setPosition(Slash, position);

	//
	
	sfVector2f Text_Origin;
	sfFloatRect Text_Rect;
	sfText* Message;
	position = { (float)SCREEN_WIDTH / 2,(float)SCREEN_HEIGHT - 100 };
	Message = sfText_create(); // stworzenie textu
	sfText_setString(Message, "Kolejny poziom !!!");
	sfText_setFont(Message, Font);
	sfText_setCharacterSize(Message, 40);
	sfText_setPosition(Message, position);

	Text_Rect = sfText_getGlobalBounds(Message);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(Message, Text_Origin);

	//



	//

	//Serca

	sfTexture * Heart_Texture = sfTexture_createFromFile("img/heart.png", NULL);

	sfVector2f Heart_Position = { 1200,20 };

	sfSprite * Heart1_Sprite;
	Heart1_Sprite = sfSprite_create();

	sfSprite_setTexture(Heart1_Sprite, Heart_Texture, sfTrue);
	sfSprite_setPosition(Heart1_Sprite, Heart_Position);

	Heart_Position = { 1230, 20 };

	sfSprite * Heart2_Sprite;
	Heart2_Sprite = sfSprite_create();

	sfSprite_setTexture(Heart2_Sprite, Heart_Texture, sfTrue);
	sfSprite_setPosition(Heart2_Sprite, Heart_Position);

	Heart_Position = { 1260, 20 };

	sfSprite * Heart3_Sprite;
	Heart3_Sprite = sfSprite_create();

	sfSprite_setTexture(Heart3_Sprite, Heart_Texture, sfTrue);
	sfSprite_setPosition(Heart3_Sprite, Heart_Position);

	//

	sfTexture * Background_Texture = sfTexture_createFromFile("img/background.png", NULL);
	sfSprite * Background_Sprite = sfSprite_create();
	
	sfSprite_setTexture(Background_Sprite, Background_Texture, NULL);

	//
	
	while (sfRenderWindow_isOpen(window))
	{
		if (Accumulator <= Time_Enemy_Spawn)
			Accumulator += sfTime_asSeconds(sfClock_restart(Enemy_Spawn_Clock)); // zegar rusza

		if (ShowMessage)
			Message_Accumulator += sfTime_asSeconds(sfClock_restart(Message_Clock)); // lecznik leci wtedy gdy wiadomosc jest widoczna



		sfEvent ev;
		while (sfRenderWindow_pollEvent(window, &ev))
		{
			if (ev.type == sfEvtClosed)
				sfRenderWindow_close(window);

		}

		if (sfKeyboard_isKeyPressed(sfKeyEscape))
			sfRenderWindow_close(window);

		if (Accumulator >= Time_Enemy_Spawn)
		{
			Create_Enemies(&Enemies);
			Accumulator = 0.0;
		}



		if (Message_Accumulator >= Show_Message_Time_Step)
		{

			ShowMessage = 0;
			Message_Accumulator = 0;

		}


		/// UPDATE & COLLISION

		Player_Update(player, &Bullets); // aktualizacja gracza

		for (int i = 0; i < Bullets.size(); i++) // aktualizcja pocisków
			Bullet_Update(Bullets[i]);
		

		for (int i = 0; i < Enemies.size(); i++) // aktualizcja przeciwników
			Enemy_Update(Enemies[i], player->Player_Position);
		

		for (int i = 0; i < Destruction_Effects.size(); i++)
			Destruction_Effect_Update(Destruction_Effects[i], &Destruction_Effects);


		for (int i = 0; i < Enemies.size(); i++) // Kolizja gracza z przeciwnikiem
		{
			if (Check_Collision_Player_Enemy(player, Enemies[i]))
			{
				Remove_Enemy_From_Vector(Enemies[i], &Enemies);
				player->Lives--;
				if (player->Lives == 3)
				{
					sfSprite_destroy(Heart3_Sprite);
					Heart3_Sprite = NULL;
				}
				if (player->Lives == 2)
				{
					sfSprite_destroy(Heart1_Sprite);
					Heart1_Sprite = NULL;
				}
				if (player->Lives == 1)
				{
					sfSprite_destroy(Heart2_Sprite);
					Heart2_Sprite = NULL;
				}
			}
		}

		for (int i = 0; i < Enemies.size(); i++) // Kolizja Pocisku i przeciwników
		{
			for (int j = 0; j < Bullets.size(); j++)
			{
				if (collisionBE)
					continue;

				if (!Bullets.empty() && !Enemies.empty() && Check_Collision_Bullet_Enemy(Bullets[j], Enemies[i]))
				{
					// Usuwanie Pocisku

					Remove_Bullets_From_Vector(Bullets[j], &Bullets); // funkcja usuwaj¹ca kule 
					collisionBE = 1;

					Total_Score += 50;

					char s[20];
					sprintf(s, "%d", Total_Score); //zamiana int'a na tablice znaków
					sfText_setString(Score_Text, s);

					break;
				}

				if ((Bullets[j]->Bullet_Position.x > SCREEN_WIDTH || Bullets[j]->Bullet_Position.x < 0)
					|| Bullets[j]->Bullet_Position.y > SCREEN_HEIGHT || Bullets[j]->Bullet_Position.y < 0)
				{
					Remove_Bullets_From_Vector(Bullets[j], &Bullets);
				}


			}

			if (collisionBE)
			{
				Add_Destruction_Effect(Enemies[i]->Enemy_Position, &Destruction_Effects);
				Remove_Enemy_From_Vector(Enemies[i], &Enemies);
				collisionBE = 0;
			}

		}

		//

		if (Total_Score == Next_Level_Score) // Zwiêkszenie poziomu trudnoœci
		{
			Next_Level_Score += 500;

			if (Time_Enemy_Spawn > 0.1)
				Time_Enemy_Spawn -= 0.1;

			if (player->Time_Step > 0.15)
				player->Time_Step -= 0.05;

			char s[20];
			sprintf(s, "%d", Next_Level_Score); //zamiana int'a na tablice znaków
			sfText_setString(Next_Level_Text, s);

			ShowMessage = 1;

		}

		if (player->Lives == 0)
		{

			if (Enemies.size() != 0)
			{
				for (int i = 0; i < Enemies.size(); i++)
					Remove_Enemy_From_Vector(Enemies[i], &Enemies);
			}

			if (Bullets.size() != 0)
			{
				for (int i = 0; i < Bullets.size(); i++)
					Remove_Bullets_From_Vector(Bullets[i], &Bullets);
			}



			Bullets.clear();
			Enemies.clear();


			sfText_destroy(Score_Text);
			Score_Text = NULL;
			sfText_destroy(Next_Level_Text);
			Next_Level_Text = NULL;
			sfText_destroy(Slash);
			Slash = NULL;
			sfText_destroy(Message);
			Message = NULL;
			sfSprite_destroy(Background_Sprite);
			Background_Sprite = NULL;


			sfSprite_destroy(player->Player_Sprite);
			sfTexture_destroy(player->Player_Texture);
			sfClock_destroy(player->Shoot_Timer);

			delete player;

			Enemy::ID = -1;
			Bullet::ID = -1;


			GameOver(window, Total_Score);
		}


		///

		sfRenderWindow_clear(window, sfBlack); // czyszczenia okna

		///Render
		if (Background_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Background_Sprite, NULL); // rysowanie t³a

		sfRenderWindow_drawSprite(window, player->Player_Sprite, NULL); // rysowanie gracza

		if (!Bullets.empty())
			for (int i = 0; i < Bullets.size(); i++) // rysowanie pocisków
			{
				sfRenderWindow_drawSprite(window, Bullets[i]->Bullet_Sprite, NULL);
			}

		if (!Enemies.empty() && window != NULL);
		for (int i = 0; i < Enemies.size(); i++) // rysowanie przeciwników
		{
			if (Enemies[i]->Enemy_Sprite != NULL)
				sfRenderWindow_drawSprite(window, Enemies[i]->Enemy_Sprite, NULL);
		}

		if (Heart1_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Heart1_Sprite, NULL);
		if (Heart2_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Heart2_Sprite, NULL);
		if (Heart3_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Heart3_Sprite, NULL);

		if (Score_Text != NULL)
			sfRenderWindow_drawText(window, Score_Text, NULL);
		if (Next_Level_Score != NULL)
			sfRenderWindow_drawText(window, Next_Level_Text, NULL);
		if (Slash != NULL)
			sfRenderWindow_drawText(window, Slash, NULL);

		if (ShowMessage && Message != NULL)
			sfRenderWindow_drawText(window, Message, NULL);
		
		if (!Destruction_Effects.empty())
			for (int i = 0; i < Destruction_Effects.size(); i++)
			{
				if (Destruction_Effects[i]->DE_Sprite1 != NULL && Destruction_Effects[i]->DE_Sprite2 != NULL
					&& Destruction_Effects[i]->DE_Sprite3 != NULL && Destruction_Effects[i]->DE_Sprite4 != NULL)
				{
					sfRenderWindow_drawSprite(window, Destruction_Effects[i]->DE_Sprite1, NULL);
					sfRenderWindow_drawSprite(window, Destruction_Effects[i]->DE_Sprite2, NULL);
					sfRenderWindow_drawSprite(window, Destruction_Effects[i]->DE_Sprite3, NULL);
					sfRenderWindow_drawSprite(window, Destruction_Effects[i]->DE_Sprite4, NULL);
				}
			}
			

		///
			sfRenderWindow_display(window); // Pokazywanie okna
	}

}
