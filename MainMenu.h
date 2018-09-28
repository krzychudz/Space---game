#pragma once
#include "stdafx.h"
#include <SFML/Graphics.h>
#include "Game.h"
#include "ScreenResolution.cpp"
#include "Scoreboard.h"


void Main_Menu(sfRenderWindow * window)
{

	sfFont* Font;
	Font = sfFont_createFromFile("img/Mecha_Bold.ttf"); // wczytanie czcionki


	sfVector2f Txt_Origin;
	sfVector2f Txt_Pos;

	//
	sfText* Title;
	sfFloatRect Title_Rect;

	Title = sfText_create(); // stworzenie textu
	sfText_setString(Title, "Super Gierka");
	sfText_setFont(Title, Font);
	sfText_setCharacterSize(Title, 80);

	Title_Rect = sfText_getGlobalBounds(Title);
	Txt_Origin = { Title_Rect.width / 2, Title_Rect.height / 2 };
	Txt_Pos = { (float)SCREEN_WIDTH / 2 , 50 };

	sfText_setOrigin(Title, Txt_Origin);
	sfText_setPosition(Title, Txt_Pos);

	Title_Rect = sfText_getGlobalBounds(Title);

	// 

	sfText * New_Game;
	sfFloatRect New_Game_Rect;

	New_Game = sfText_create();
	sfText_setString(New_Game, "Nowa Gra");
	sfText_setFont(New_Game, Font);
	sfText_setCharacterSize(New_Game, 60);

	New_Game_Rect = sfText_getGlobalBounds(New_Game);
	Txt_Origin = { New_Game_Rect.width / 2, New_Game_Rect.height / 2 };
	Txt_Pos = { (float)SCREEN_WIDTH / 2, 250 };

	sfText_setOrigin(New_Game, Txt_Origin);
	sfText_setPosition(New_Game, Txt_Pos);

	New_Game_Rect = sfText_getGlobalBounds(New_Game);

	//

	sfText * Scoreboard;
	sfFloatRect Scoreboard_Rect;

	Scoreboard = sfText_create();
	sfText_setString(Scoreboard, "Tablica wyników");
	sfText_setFont(Scoreboard, Font);
	sfText_setCharacterSize(Scoreboard, 60);

	Scoreboard_Rect = sfText_getGlobalBounds(Scoreboard);
	Txt_Origin = { Scoreboard_Rect.width / 2, Scoreboard_Rect.height / 2 };
	Txt_Pos = { (float)SCREEN_WIDTH / 2, 350 };

	sfText_setOrigin(Scoreboard, Txt_Origin);
	sfText_setPosition(Scoreboard, Txt_Pos);

	Scoreboard_Rect = sfText_getGlobalBounds(Scoreboard);

	//

	sfText * Exit;
	sfFloatRect Exit_Rect;

	Exit = sfText_create();
	sfText_setString(Exit, "Koniec");
	sfText_setFont(Exit, Font);
	sfText_setCharacterSize(Exit, 60);

	Exit_Rect = sfText_getGlobalBounds(Exit);
	Txt_Origin = { Exit_Rect.width / 2, Exit_Rect.height / 2 };
	Txt_Pos = { (float)SCREEN_WIDTH / 2, 450 };

	sfText_setOrigin(Exit, Txt_Origin);
	sfText_setPosition(Exit, Txt_Pos);

	Exit_Rect = sfText_getGlobalBounds(Exit);

	// t³o
	sfTexture * Background_Texture = sfTexture_createFromFile("img/background.png", NULL);
	sfSprite * Background_Sprite = sfSprite_create();
	sfSprite_setTexture(Background_Sprite, Background_Texture, NULL);

	// Planeta
	float Planet_Rot = 0;
	sfFloatRect Planet_Rect;
	sfVector2f Planet_Origin;
	sfTexture * Planet_Texture = sfTexture_createFromFile("img/planet.png", NULL);
	sfSprite * Planet_Sprite = sfSprite_create();
	sfSprite_setTexture(Planet_Sprite, Planet_Texture, NULL);

	Planet_Rect = sfSprite_getGlobalBounds(Planet_Sprite);
	Planet_Origin = { Planet_Rect.width / 2, Planet_Rect.height / 2 };

	sfSprite_setOrigin(Planet_Sprite, Planet_Origin);

	sfVector2f Planet_Position = { 230, (float)SCREEN_HEIGHT - 250 };
	sfSprite_setPosition(Planet_Sprite, Planet_Position);

	//



	while (sfRenderWindow_isOpen(window))
	{

		Planet_Rot = 0.5;
		sfSprite_rotate(Planet_Sprite, Planet_Rot);

		sfVector2i Mouse_Position = sfMouse_getPosition(NULL);


		sfEvent ev;
		while (sfRenderWindow_pollEvent(window, &ev))
		{
			if (ev.type == sfEvtClosed)
				sfRenderWindow_close(window);

		}


		//
		if (New_Game != NULL)
		{
			if (sfFloatRect_contains(&New_Game_Rect, Mouse_Position.x, Mouse_Position.y)) // jeœli myszka najedzie na przycisk nowej gry
			{
				sfText_setColor(New_Game, sfCyan);

				if (sfMouse_isButtonPressed(sfMouseLeft))
				{

					sfText_destroy(Title);
					Title = NULL;
					sfText_destroy(New_Game);
					New_Game = NULL;
					sfText_destroy(Scoreboard);
					Scoreboard = NULL;
					sfText_destroy(Exit);
					Exit = NULL;
					sfFont_destroy(Font);
					Font = NULL;
					sfSprite_destroy(Background_Sprite);
					Background_Sprite = NULL;
					sfSprite_destroy(Planet_Sprite);
					Planet_Sprite = NULL;

					Game(window);

				}

			}


			if (!sfFloatRect_contains(&New_Game_Rect, Mouse_Position.x, Mouse_Position.y)) // jeœli myszka zjedzie z tego pola
				sfText_setColor(New_Game, sfWhite);
		}
		//

		if (Scoreboard != NULL)
		{
			if (sfFloatRect_contains(&Scoreboard_Rect, Mouse_Position.x, Mouse_Position.y))
			{
				sfText_setColor(Scoreboard, sfCyan);

				if (sfMouse_isButtonPressed(sfMouseLeft))
				{
					sfText_setColor(Scoreboard, sfCyan);
					Scoreboard_menu(window);


				}

			}


			if (!sfFloatRect_contains(&Scoreboard_Rect, Mouse_Position.x, Mouse_Position.y))
				sfText_setColor(Scoreboard, sfWhite);
		}
		//

		if (Exit != NULL)
		{
			if (sfFloatRect_contains(&Exit_Rect, Mouse_Position.x, Mouse_Position.y))
			{
				sfText_setColor(Exit, sfCyan);

				if (sfMouse_isButtonPressed(sfMouseLeft))
				{
					sfText_destroy(Title);
					Title = NULL;
					sfText_destroy(New_Game);
					New_Game = NULL;
					sfText_destroy(Scoreboard);
					Scoreboard = NULL;
					sfText_destroy(Exit);
					Exit = NULL;
					sfFont_destroy(Font);
					Font = NULL;

					exit(0);
				}
			}


			if (!sfFloatRect_contains(&Exit_Rect, Mouse_Position.x, Mouse_Position.y))
				sfText_setColor(Exit, sfWhite);
		}
		//


		sfRenderWindow_clear(window, sfBlack);

		if (Background_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Background_Sprite, NULL);

		if (Planet_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Planet_Sprite, NULL);

		if (Title != NULL)
			sfRenderWindow_drawText(window, Title, NULL);
		if (New_Game != NULL)
			sfRenderWindow_drawText(window, New_Game, NULL);
		if (Scoreboard != NULL)
			sfRenderWindow_drawText(window, Scoreboard, NULL);
		if (Exit != NULL)
			sfRenderWindow_drawText(window, Exit, NULL);

		sfRenderWindow_display(window);
	}

}