#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	Block()
	{
	}
		
	void set(sf::Vector2f position, sf::Vector2f size)
	{
		body.setSize(size);
		body.setPosition(position.x + body.getSize().x / 2, position.y + body.getSize().y / 2);
		body.setOrigin(sf::Vector2f(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2));
		body.setFillColor(sf::Color::Red);
	}
	sf::FloatRect getGlobalBounds()
	{
		return body.getGlobalBounds();
	}
	sf::Vector2f getSize()
	{
		return body.getSize();
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
	void setPos(sf::Vector2f pos)
	{
		body.setPosition(pos);
	}





	sf::RectangleShape body;
};
