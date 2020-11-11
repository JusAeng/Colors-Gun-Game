#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>


//---------------------------------------------------------Player---------------------------------
class Player {
public:

    //Basic
    Player(sf::Vector2f size)
    {
        player.setSize(size);
       
    }
    void setPos(sf::Vector2f pos)
    {
        player.setPosition(pos);
    }
    float getX()
    {
        return player.getPosition().x;
    }
    float getY()
    {
        return player.getPosition().y;
    }
    sf::FloatRect getGlobalBounds()
    {
        return player.getGlobalBounds();
    }
    void setOrigin()
    {
        player.setOrigin(sf::Vector2f(player.getGlobalBounds().width/2,player.getGlobalBounds().height/2));
    }
    void toDrawR(sf::RenderWindow& window)
    {
        texture.loadFromFile("playerR.png");
        player.setTexture(&texture);
        window.draw(player);
    }
    void toDrawL(sf::RenderWindow& window)
    {
        texture.loadFromFile("playerL.png");
        player.setTexture(&texture);
        window.draw(player);
    }

    //control

    void moveLeft(float speed)
    {
        player.move(-speed, 0.0f);
    }
    void moveRight(float speed)
    {
        player.move(speed, 0.0f);
    }
    void jump(float gravitySpeed)
    {
        player.move(0.0f, gravitySpeed);
    }
    void fall(float down)
    {
        player.move(0.0f,down );
    }
    

    //colliding
    
    void colEnemy()
    {

    }
    void Item()
    {

    }

private:
    sf::RectangleShape player;
    sf::Texture texture;
};


//-----------------------------------------------------------Skill---------------------------------------------

class Skill {
public:
    Skill()
    {
        skill.setRadius(8.0f);
        skill.setPosition(-15.0f, -15.0f);
    }
    void setColor(const sf::Color& color)
    {
        skill.setFillColor(color);
    }
    void move(float speed)
    {
        skill.move(speed, 0.0f);
    }
    void setPos(sf::Vector2f pos)
    {
        skill.setPosition(pos);
    }
    float getX()
    {
        return skill.getPosition().x;
    }
    float getY()
    {
        return skill.getPosition().y;
    }
    sf::FloatRect getGlobalBounds()
    {
        return skill.getGlobalBounds();
    }
    void toDraw(sf::RenderWindow& window)
    {
        window.draw(skill);
    }







private:
    sf::CircleShape skill;
};