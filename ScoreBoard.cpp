#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(float width, float height)
{
	if (!font.loadFromFile("BAUHS93.TTF"))
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("BACK TO MENU");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (max_menu + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Option");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (max_menu + 1) * 2));


	selectItemIndex = 0;

}
void ScoreBoard::toDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < max_menu; i++)
	{
		window.draw(menu[i]);
	}
}

void ScoreBoard::moveRight()
{
	if (selectItemIndex - 1 >= 0)
	{
		menu[selectItemIndex].setFillColor(sf::Color::White);
		selectItemIndex--;
		menu[selectItemIndex].setFillColor(sf::Color::Red);

	}
}

void ScoreBoard::moveLeft()
{
	if (selectItemIndex + 1 <= 1)
	{
		menu[selectItemIndex].setFillColor(sf::Color::White);
		selectItemIndex++;
		menu[selectItemIndex].setFillColor(sf::Color::Red);

	}
}
