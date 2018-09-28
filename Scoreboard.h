#pragma once
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MainMenu.h"
#include <iostream>
#include "ScreenResolution.cpp"

struct _Text
{
	sfText * text;
	sfText * text1;
	sfVector2f Txt_Origin;
	sfVector2f Txt_Pos;

};


void Scoreboard_menu(sfRenderWindow * window)
{

	sfFont* Font;
	Font = sfFont_createFromFile("img/Mecha_Bold.ttf"); // wczytanie czcionki

	std::vector<_Text *>Txt;

	sfEvent event;

	char zp = 'k';
	char tab[10];
	int NumberOfLine = 0;

	FILE * file = fopen("scoreboard.txt", "rt");

	while (zp != EOF)			// Liczenie iloœæ linijek w pliku
	{							//
		zp = fgetc(file);		//
								//
		if (zp == '\n')			//
			NumberOfLine += 1;	//
	}							//
	fclose(file);


	int * Points = new int[NumberOfLine];
	int tmp; // tymczasowa zmienna pomocnicza do konwersji z char* na int

	file = fopen("scoreboard.txt", "rt");

	std::vector<string> Names;
	std::string tmp_str;

	for (int i = 0; i < NumberOfLine; i++)
	{
		fscanf(file, "%s", tab);
		tmp_str = tab;
		Names.push_back(tmp_str);
		
		fscanf(file, "%s", tab);
		tmp = atoi(tab);
		Points[i] = tmp; 

	}
	
	fclose(file);

	cout << Names.size() << endl;

	for (int i = 0; i < Names.size(); i++)
		cout << Names[i].c_str() << " " << Points[i] << endl;

	
	
	for(int i = 0; i < NumberOfLine; i++)
		for (int j = 0; j < NumberOfLine - 1; j++)
		{
			if (Points[i] > Points[j])
			{
					std::swap(Points[i], Points[j]);
					std::swap(Names[i], Names[j]);
			}
		}
		
	
	sfText * Scoreboard;
	sfFloatRect Scoreboard_Rect;
	sfVector2f Txt_Origin;
	sfVector2f Txt_Pos;

	Scoreboard = sfText_create();
	sfText_setString(Scoreboard, "Tablica wyników");
	sfText_setFont(Scoreboard, Font);
	sfText_setCharacterSize(Scoreboard, 60);

	Scoreboard_Rect = sfText_getGlobalBounds(Scoreboard);
	Txt_Origin = { Scoreboard_Rect.width / 2, Scoreboard_Rect.height / 2 };
	Txt_Pos = { (float)SCREEN_WIDTH / 2, 50 };

	sfText_setOrigin(Scoreboard, Txt_Origin);
	sfText_setPosition(Scoreboard, Txt_Pos);

	Scoreboard_Rect = sfText_getGlobalBounds(Scoreboard);

	//

	sfText * Back;
	sfFloatRect Back_Rect;

	Back = sfText_create();
	sfText_setString(Back, "Powrót");
	sfText_setFont(Back, Font);
	sfText_setCharacterSize(Back, 60);

	Back_Rect = sfText_getGlobalBounds(Back);
	Txt_Origin = { Back_Rect.width / 2, Back_Rect.height / 2 };
	Txt_Pos = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT - 100 };

	sfText_setOrigin(Back, Txt_Origin);
	sfText_setPosition(Back, Txt_Pos);

	Back_Rect = sfText_getGlobalBounds(Back);


	// Konwersja char* do Text

	float posX = 50; // Pocz¹tkowa pozycja pierwszego wyniku 
	float posY = 130; //

	for (int i = 0; i < NumberOfLine; i++)
	{

		char s[20];
		sprintf(s, "%d", Points[i]); //zamiana int'a na tablice znaków

		_Text * str = new _Text;
		str->text = sfText_create();
		str->text1 = sfText_create();
		str->Txt_Pos = { posX,posY };
		sfText_setString(str->text, Names[i].c_str());
		sfText_setString(str->text1, s);
		sfText_setFont(str->text, Font);
		sfText_setFont(str->text1, Font);
		sfText_setCharacterSize(str->text, 30);
		sfText_setCharacterSize(str->text1, 30);
		sfText_setPosition(str->text, str->Txt_Pos);
		str->Txt_Pos = { posX + 150,posY };
		sfText_setPosition(str->text1, str->Txt_Pos);

		Txt.push_back(str);

		posY += 40;

		if (posY >= SCREEN_HEIGHT - 120)
		{
			posX += 300;
			posY = 130;
		}
	}

	// t³o
	sfTexture * Background_Texture = sfTexture_createFromFile("img/background.png", NULL);
	sfSprite * Background_Sprite = sfSprite_create();
	sfSprite_setTexture(Background_Sprite, Background_Texture, NULL);

	//

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{


		}

		sfVector2i Mouse_Position = sfMouse_getPosition(NULL);

		if (Scoreboard != NULL)
		{
			if (sfFloatRect_contains(&Back_Rect, Mouse_Position.x, Mouse_Position.y))
			{
				sfText_setColor(Back, sfCyan);

				if (sfMouse_isButtonPressed(sfMouseLeft))
				{
					
					for (int i = 0; i < Txt.size(); i++)
					{
						sfText_destroy(Txt[i]->text);
						sfText_destroy(Txt[i]->text1);
						delete Txt[i];
					}

					sfText_destroy(Scoreboard);
					sfSprite_destroy(Background_Sprite);
					Background_Sprite = NULL;
				
						Txt.clear();
						Main_Menu(window);


				}

			}


			if (!sfFloatRect_contains(&Back_Rect, Mouse_Position.x, Mouse_Position.y))
				sfText_setColor(Back, sfWhite);
		}


		sfRenderWindow_clear(window, sfBlack);

		if(Background_Sprite != NULL)
			sfRenderWindow_drawSprite(window, Background_Sprite, NULL);

		for (int i = 0; i < Txt.size(); i++)
		{
			sfRenderWindow_drawText(window, Txt[i]->text, NULL);
			sfRenderWindow_drawText(window, Txt[i]->text1, NULL);
		}

		sfRenderWindow_drawText(window, Scoreboard, NULL);
		sfRenderWindow_drawText(window, Back, NULL);


		sfRenderWindow_display(window);
	}



}