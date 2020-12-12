#pragma once
#include "SFML/Graphics.hpp"

#define max_menu 3
class Naming
{
public:
	Naming(float width, float height);

	void toDraw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getPressItem() { return selectItemIndex; }

private:
	int selectItemIndex;
	sf::Font font;
	sf::Text menu[max_menu];

};