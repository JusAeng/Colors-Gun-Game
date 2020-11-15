#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Player.h"

class Enemy {
public:
    
    Enemy() 
    {
        enemy.setSize(sf::Vector2f(120.0,90.0));
        enemy.setOrigin(sf::Vector2f(enemy.getGlobalBounds().width / 2,enemy.getGlobalBounds().height / 2));
    }
    void set0()
    {
        enemy.setFillColor(sf::Color::White);
        texture.loadFromFile("enemy0.png");
        enemy.setTexture(&texture);
    }
    void set1()
    {
        enemy.setFillColor(sf::Color::Blue);
        texture.loadFromFile("enemy1.png");
        enemy.setTexture(&texture);
    }
    void set2()
    {
        enemy.setFillColor(sf::Color::Red);
        texture.loadFromFile("enemy2.png");
        enemy.setTexture(&texture);
    }
    void set3()
    {
        enemy.setFillColor(sf::Color(128, 0, 128));
        texture.loadFromFile("enemy3.png");
        enemy.setTexture(&texture);
    }

    void setPos(sf::Vector2f newPos) 
    {
        enemy.setPosition(newPos);
    }

    void toDraw(sf::RenderWindow& window)
    {
        window.draw(enemy);
    }

    sf::FloatRect getGlobalBounds()
    {
        return enemy.getGlobalBounds();
    }
   
private:
    sf::RectangleShape enemy;
    sf::Texture texture;
};
