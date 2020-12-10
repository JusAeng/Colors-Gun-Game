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

    void Pattern0(float dt)     //moveUpDown
    {
        if (speed0 >= 0)
        {
            if (direct0 == 1)
            {
                enemy.move(0, -speed0 * dt);
            }
            else
            {
                enemy.move(0, speed0 * dt);
               
            }
            speed0 -= retard0;
        }
        else
        {
            speed0 = 200;
            if (direct0 == 1)
            {
                direct0 = -1;
                
            }
            else
            {
                direct0 = 1;
            }
        }
    }
    void Pattern1(float dt,float point_return1,float point_return2)     //moveLeftRigt
    {
        if (direct1 == 1)
        {
            enemy.move(speed1*dt, 0);
        }
        else
        {
            enemy.move(-speed1*dt,0);
        }


        if (enemy.getPosition().x >= point_return2)
        {
            direct1 = -1;
        }
        if (enemy.getPosition().x <= point_return1)
        {
            direct1 = 1;
        }
    }
    void Pattern2(float dt,int go,int jumpPoint,int downPoint)      //Dash
    {
        if (go == 1)
        {
            enemy.move(speed2 * dt, 0);
        }
        if (downPoint==1)
        {
            if (enemy.getPosition().y >= 664)
            {
                fall2=0;
            }
            enemy.move(0, -fall2*dt);
            fall2 -= retard2;
        }
        if (jumpPoint ==1)
        {
            enemy.move(0, -Yspeed2*dt);
            Yspeed2 -= retard2;
            if (enemy.getPosition().y >= 664)
            {
               Yspeed2 = 0;
            }
        }
    }

    void Pattern3(float dt, int go,int direct,int sp)
    {
        if (go == 1)
        {
            if (sp == 0)
            {
                if (direct == 1)
                {
                    enemy.move(speed3 * dt, 0);
                }
                if (direct == -1)
                {
                    enemy.move(-speed3 * dt, 0);
                }
            }
            else
            {
                if (direct == 1)
                {
                    enemy.move(speed31 * dt, 0);
                }
                if (direct == -1)
                {
                    enemy.move(-speed31 * dt, 0);
                }
            }
        }
    }





    sf::Vector2f getPos()
    {
        return enemy.getPosition();
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

    //patern direct
    int direct0 = 1;
    float retard0 = 25.0;
    float speed0 = 300;

    int direct1 = -1;
    float speed1 = 400;

    float speed2 = 1200;
    float Yspeed2 = 800;
    float fall2 = 0;
    float retard2 = 25;

    float speed3 = 800;
    float speed31 = 1000;


};
