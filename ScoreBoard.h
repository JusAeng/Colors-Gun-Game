#pragma once
#include "SFML/Graphics.hpp"

#define max_menu 2
class ScoreBoard
{
public:
	ScoreBoard(float width, float height);

	void toDraw(sf::RenderWindow& window);
	void moveRight();
	void moveLeft();
	int getPressItem() { return selectItemIndex; }

private:
	int selectItemIndex;
	sf::Font font;
	sf::Text menu[max_menu];

};

