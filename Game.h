#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class HP {
public:
	HP()
	{
		hp.setSize(sf::Vector2f(47.0,40.0));
		texture.loadFromFile("HPF.png");
		hp.setTexture(&texture);
	}
	void setPos(sf::Vector2f pos)
	{
		hp.setPosition(pos);
	}
	void toDraw(sf::RenderWindow& window)
	{
		window.draw(hp);
	}


private:
	sf::RectangleShape hp;
	sf::Texture texture;

};

class Mana {
public:
	Mana()
	{
		mana.setRadius(11.0);
		mana.setFillColor(sf::Color(0,204,255));
	}
	void setPos(sf::Vector2f pos)
	{
		mana.setPosition(pos);
	}
	void toDraw(sf::RenderWindow& window)
	{
		window.draw(mana);
	}


private:
	sf::CircleShape mana;
};

class Item {
public:
	Item()
	{
		item.setSize(sf::Vector2f(40.0,40.0));
		item.setFillColor(sf::Color::Yellow);
		texture.loadFromFile("");
		item.setTexture(&texture);
	}
	void setPOs(sf::Vector2f pos)
	{
		item.setPosition(pos);
	}
	sf::FloatRect getGlobalBounds()
	{
		return item.getGlobalBounds();
	}
	void toDraw(sf::RenderWindow& window)
	{
		window.draw(item);
	}



private:
	sf::RectangleShape item;
	sf::Texture texture;

};

class Solid {
public:
	Solid(sf::Vector2f pos);
	
	
	void toDraw(sf::RenderWindow& window)
	{
		window.draw(solid[0]);
		window.draw(solid[1]);
		window.draw(solid[2]);
		window.draw(solid[3]);
		window.draw(solid[4]);
	}

private:
	sf::RectangleShape solid[5];

};
