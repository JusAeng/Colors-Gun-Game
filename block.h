#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	Block(sf::Vector2f size,sf::Vector2f position)
	{
		body.setSize(size);
		body.setPosition(position.x+body.getSize().x/2, position.y + body.getSize().y / 2);
		body.setOrigin(sf::Vector2f(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2));
		body.setFillColor(sf::Color::Red);
	}
	sf::FloatRect getGlobalBounds()
	{
		return body.getGlobalBounds();
	}
	sf::Vector2f getPos()
	{
		return body.getPosition();
	}
	void rotate(float degree)
	{
		body.rotate(degree);
	}
	void toDraw(sf::RenderWindow& window)
	{
		window.draw(body);
	}




private:
	sf::RectangleShape body;
};
