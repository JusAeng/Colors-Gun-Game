#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	Block(sf::Vector2f size)
	{
		body.setSize(size);
	}




private:
	sf::RectangleShape body;
};
