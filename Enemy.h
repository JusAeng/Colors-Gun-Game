#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Player.h"

class Enemy {
public:
    
    Enemy(int type) 
    {
        enemy.setSize(sf::Vector2f(120.0,90.0));
        enemy.setOrigin(sf::Vector2f(enemy.getGlobalBounds().width / 2,enemy.getGlobalBounds().height / 2));
        if (type == 0)
        {
            enemy.setFillColor(sf::Color::White);
            texture.loadFromFile("enemy0.png");
            enemy.setTexture(&texture);
        }
        else if (type == 1)
        {
            enemy.setFillColor(sf::Color::Blue);
            texture.loadFromFile("enemy1.png");
            enemy.setTexture(&texture);
        }
        else if (type == 2)
        {
            enemy.setFillColor(sf::Color::Red);
            texture.loadFromFile("enemy2.png");
            enemy.setTexture(&texture);
        }
        else if (type == 3)
        {
            enemy.setFillColor(sf::Color(128, 0, 128));
            texture.loadFromFile("enemy3.png");
            enemy.setTexture(&texture);
        }
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
