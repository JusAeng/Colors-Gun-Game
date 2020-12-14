#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("BAUHS93.TTF"))
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(255, 240, 180));
	menu[0].setString("PLAY");
	menu[0].setPosition(sf::Vector2f(680, 95));
	menu[0].setCharacterSize(120);
	menu[0].setOutlineColor(sf::Color(255,209,77));
	menu[0].setOutlineThickness(10);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("SCOREBOARD");
	menu[1].setPosition(sf::Vector2f(675,340));
	menu[1].setCharacterSize(80);
	menu[1].setOutlineColor(sf::Color(255, 209, 77));
	menu[1].setOutlineThickness(10);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("EXIT");
	menu[2].setPosition(sf::Vector2f(680,548));
	menu[2].setCharacterSize(80);
	menu[2].setOutlineColor(sf::Color(255, 209, 77));
	menu[2].setOutlineThickness(10);

	selectItemIndex = 0;

}
void Menu::toDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < max_menu; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectItemIndex - 1 >= 0)
	{
		menu[selectItemIndex].setFillColor(sf::Color::White);
		selectItemIndex--;
		menu[selectItemIndex].setFillColor(sf::Color(255, 240, 180));

	}
}

void Menu::moveDown()
{
	if (selectItemIndex + 1 <= 2)
	{
		menu[selectItemIndex].setFillColor(sf::Color::White);
		selectItemIndex++;
		menu[selectItemIndex].setFillColor(sf::Color(255, 240, 180));

	}
}
