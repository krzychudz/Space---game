#pragma once
#include <SFML/Graphics.h>
#include <stdio.h>
#include "MainMenu.h"
#include <cstdlib>

void Main_Menu(sfRenderWindow *);

void GameOver(sfRenderWindow * window, int Total_Score)
{

	sfFont* Font;
	Font = sfFont_createFromFile("img/Mecha_Bold.ttf"); // wczytanie czcionki

	sfVector2f Text_Position;
	sfVector2f Text_Origin;
	sfFloatRect Text_Rect;
	
	//

	Text_Position = { (float)SCREEN_WIDTH / 2, 50 };
	sfText * Text;
	Text = sfText_create();
	sfText_setString(Text, "Koniec gry");
	sfText_setFont(Text, Font);
	sfText_setCharacterSize(Text, 60);
	sfText_setPosition(Text, Text_Position);

	Text_Rect = sfText_getGlobalBounds(Text);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(Text, Text_Origin);

	//

	Text_Position = { ((float)SCREEN_WIDTH / 2) - 170,150 };
	sfText * Text1;
	Text1 = sfText_create();
	sfText_setString(Text1, "Masz");
	sfText_setFont(Text1, Font);
	sfText_setCharacterSize(Text1, 60);
	sfText_setPosition(Text1, Text_Position);

	Text_Rect = sfText_getGlobalBounds(Text1);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(Text1, Text_Origin);

	//
	sfFloatRect Continue_Text_Rect;

	Text_Position = { ((float)SCREEN_WIDTH / 2),(float)SCREEN_HEIGHT - 100  };
	sfText * Continue_Text;
	Continue_Text = sfText_create();
	sfText_setString(Continue_Text, "Kontynuuj");
	sfText_setFont(Continue_Text, Font);
	sfText_setCharacterSize(Continue_Text, 60);
	sfText_setPosition(Continue_Text, Text_Position);

	Continue_Text_Rect = sfText_getGlobalBounds(Continue_Text);
	Text_Origin = { Continue_Text_Rect.width / 2, Continue_Text_Rect.height / 2 };

	sfText_setOrigin(Continue_Text, Text_Origin);

	Continue_Text_Rect = sfText_getGlobalBounds(Continue_Text);


	//

	char s[20];
	sprintf(s, "%d", Total_Score); // zamiana int na char*

	Text_Position = { ((float)SCREEN_WIDTH / 2) - 30,150 };
	sfText * Total_Score_Text;
	Total_Score_Text = sfText_create();
	sfText_setString(Total_Score_Text, s);
	sfText_setFont(Total_Score_Text, Font);
	sfText_setCharacterSize(Total_Score_Text, 60);
	sfText_setPosition(Total_Score_Text, Text_Position);

	Text_Rect = sfText_getGlobalBounds(Total_Score_Text);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(Total_Score_Text, Text_Origin);

	//
	Text_Position = { ((float)SCREEN_WIDTH / 2) + 150,150 };
	sfText * Text2;
	Text2 = sfText_create();
	sfText_setString(Text2, "punktów");
	sfText_setFont(Text2, Font);
	sfText_setCharacterSize(Text2, 60);
	sfText_setPosition(Text2, Text_Position);

	Text_Rect = sfText_getGlobalBounds(Text2);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(Text2, Text_Origin);

	//
	Text_Position = { ((float)SCREEN_WIDTH / 2),300 };
	sfText * Text3;
	Text3 = sfText_create();
	sfText_setString(Text3, "Dopisz sie do listy");
	sfText_setFont(Text3, Font);
	sfText_setCharacterSize(Text3, 60);
	sfText_setPosition(Text3, Text_Position);

	Text_Rect = sfText_getGlobalBounds(Text3);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(Text3, Text_Origin);

	//

	string name_str;

	Text_Position = {float(SCREEN_WIDTH / 2) ,(float)SCREEN_HEIGHT / 2 + 100 };
	sfText * name; // Text w ktorym bêdzie przechowywana nazwa gracza
	name = sfText_create();
	sfText_setString(name, "");
	sfText_setFont(name, Font);
	sfText_setCharacterSize(name, 60);
	sfText_setPosition(name, Text_Position);

	Text_Rect = sfText_getGlobalBounds(name);
	Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };

	sfText_setOrigin(name, Text_Origin);

	// T³o

	sfTexture * Background_Texture = sfTexture_createFromFile("img/background.png", NULL);
	sfSprite * Background_Sprite = sfSprite_create();
	sfSprite_setTexture(Background_Sprite, Background_Texture, NULL);

	//
	

	sfEvent event;
	

	while (sfRenderWindow_isOpen(window))
	{
		sfEvent event;
		while (sfRenderWindow_pollEvent(window, &event))
		{

				if (event.type == sfEvtTextEntered)
				{
					if (event.text.unicode < 128 && event.text.unicode != 8 && name_str.size() <= 6)
					{
						name_str += static_cast<char>(event.text.unicode);
					}

				}

				if (event.type == sfEvtKeyPressed)
				{
					if (event.key.code == 59 && name_str.size() != 0) // BS
					{
						name_str.pop_back();
					}
					
				}

				
		}

		// UPDATE

		Text_Rect = sfText_getGlobalBounds(name);						// Aktualizacja tekstu wpisywanego przez gracza
		Text_Origin = { Text_Rect.width / 2, Text_Rect.height / 2 };	// tak aby zawsze byl na œrodku
		sfText_setOrigin(name, Text_Origin);							//
		sfText_setString(name, name_str.c_str());						//

		sfVector2i Mouse_Position = sfMouse_getPosition(NULL);

		
		if (sfFloatRect_contains(&Continue_Text_Rect, (float)Mouse_Position.x, (float)Mouse_Position.y ))
		{
			sfText_setColor(Continue_Text, sfCyan);

			if (sfMouse_isButtonPressed(sfMouseLeft) && !name_str.empty())
			{
				FILE * file; // deskryptor pliku
				cout << "Zapis" << endl;
				file = fopen("scoreboard.txt", "a");
				if (file == NULL) {
					printf("Wystapil blad przy otwieraniu pliku %s !\n", "scoreboard.txt");
				}

				fprintf(file, "%s %d", name_str.c_str(), Total_Score);
				fprintf(file, "\n");
				fclose(file);

				sfText_destroy(Text);
				sfText_destroy(Text1);
				sfText_destroy(Text2);
				sfText_destroy(Text3);
				sfText_destroy(Total_Score_Text);
				sfText_destroy(name);
				sfText_destroy(Continue_Text);

				Main_Menu(window);
		

			}
		}

		if (!sfFloatRect_contains(&Continue_Text_Rect, (float)Mouse_Position.x, (float)Mouse_Position.y))
			sfText_setColor(Continue_Text, sfWhite);


		if (sfKeyboard_isKeyPressed(sfKeyEscape))
			sfRenderWindow_close(window);


		//
		

		sfText_setPosition(name, Text_Position);

		sfRenderWindow_clear(window, sfBlack);

		sfRenderWindow_drawSprite(window, Background_Sprite, NULL);

		sfRenderWindow_drawText(window, Text1, NULL);
		sfRenderWindow_drawText(window, Text, NULL);
		sfRenderWindow_drawText(window, Text2, NULL);
		sfRenderWindow_drawText(window, Text3, NULL);
		sfRenderWindow_drawText(window, Total_Score_Text, NULL);
		sfRenderWindow_drawText(window, name, NULL);
		sfRenderWindow_drawText(window, Continue_Text, NULL);

		sfRenderWindow_display(window);
	}

}