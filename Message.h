#pragma once

#include <SFML/Graphics.h>

void ShowMessage(sfRenderWindow * window, sfVector2f Position, char string[], float time)
{
	sfFont* Font; // font
	Font = sfFont_createFromFile("img/Mecha_Bold.ttf"); // wczytanie czcionki

	sfText* Message;
	sfVector2f pos = Position;
	Score_Text = sfText_create(); // stworzenie textu
	sfText_setString(Score_Text, "0");
	sfText_setFont(Score_Text, Font);
	sfText_setCharacterSize(Score_Text, 40);
	sfText_setPosition(Score_Text, position);
	


}