#include <iostream>
#include <sstream>
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Menu.h"




#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

using namespace std;

int checkBump();

int main()
{
	sf::RenderWindow window(sf::VideoMode(1560, 780), "JusGame", sf::Style::Close| sf::Style::Resize);
	sf::Event ev;




	int stage = 0;

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::KeyReleased:
				switch (ev.key.code)
				{
				case sf::Keyboard::W:
					menu.moveUp();
					break;
				case sf::Keyboard::S:
					menu.moveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.getPressItem())
					{
					case 0:
						stage = 1;
						break;
					case 1:
						std::cout << "option !!";
						break;
					case 2:
						window.close();
						break;
					}
				}
			}
		}
		window.clear();
		menu.toDraw(window);
		window.display();
		if (stage == 1)
		{
			break;
		}
	}

	if (stage == 1)//-----------------------------------------Stage I-----------------------------
	{
		//viewSet
		sf::View view;
		view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
		view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
		sf::Vector2f position(window.getSize().x, window.getSize().y);

		window.setFramerateLimit(60);
		float dt;  //(deltatime)

		//background
		sf::Texture bg;
		bg.loadFromFile("map1.png");
		sf::RectangleShape bground;
		bground.setSize(sf::Vector2f(12000, 780));
		bground.setTexture(&bg);




		//main music
		sf::Music music;
		//music.openFromFile("mainSong.ogg");
		music.setVolume(15.0);
		music.play();
		//skill music
		sf::SoundBuffer soundBang, soundJump;
		soundBang.loadFromFile("bang.wav");
		soundJump.loadFromFile("musJump.wav");
		sf::Sound sBang, sJump;
		sBang.setBuffer(soundBang);
		sJump.setBuffer(soundJump);
		sBang.setVolume(30.0);
		sJump.setVolume(30.0);


		//PlayerObject
		Player player({ 84.0,112.0 });	
		player.setPos({ 0.0,600.0 });

		//skillPlayer
		Skill skilli[16], skillf[16], skillu[16];
		for (int i = 1; i <= 15; i++)
		{
			skilli[i].setColor(sf::Color::Blue);
			skillf[i].setColor(sf::Color::Red);
			skillu[i].setColor(sf::Color(128, 0, 128));
		}

		//enemy
		Enemy enemy0(0);
		enemy0.setPos({ 0.0,600.0 });
		Enemy enemy1(1);
		enemy1.setPos({ 1400.0, 450.0 });
		Enemy enemy2(2);
		enemy2.setPos({ 1400.0,600.0 });
		Enemy enemy3(3);
		enemy3.setPos({ 10.0,450.0 });


		//item
		Item item;
		item.setPOs({ 1300.0,380.0 });





		//timeObject+Stage
		sf::Font font;
		font.loadFromFile("BAUHS93.TTF");

		ostringstream showStage;
		showStage << "Stage 1";
		sf::Text lblStage;
		lblStage.setCharacterSize(30);
		lblStage.setPosition({ 1420,10 });
		lblStage.setFont(font);
		lblStage.setString(showStage.str());

		int f2sec = 0, f1min = 0, f2min = 0;
		sf::Clock clock;
		sf::Time elapsed = clock.getElapsedTime();
		ostringstream showTime;
		showTime << f2min << f1min << ":" << f2sec << (int)elapsed.asSeconds() << ":" << elapsed.asMilliseconds() % 1000 / 10;
		sf::Text lblTime;
		lblTime.setCharacterSize(30);
		lblTime.setPosition({ 1420,50 });
		lblTime.setFont(font);
		lblTime.setString(showTime.str());

		sf::Clock co1; //Lswitch
		sf::Clock co2; //Jswitch
		sf::Clock co3; //Ulti
		sf::Clock dtclock; //deltaTime


		//Mana+Hp
		Mana mana1, mana2, mana3, mana4, mana5;
		
		HP hp1,hp2,hp3;

		sf::Texture heli1, heli2;
		heli1.loadFromFile("helicopter.png");
		heli2.loadFromFile("helicopterL.png");
		sf::Sprite heliR, heliL;
		heliR.setTexture(heli1);
		heliL.setTexture(heli2);
		heliL.setPosition(7472.0,15.0);
		heliR.setPosition(11567.0, 44.0);
		
		
		
		//solid
		sf::RectangleShape sol1;
		sol1.setFillColor(sf::Color::Red);
		sol1.setPosition(0, 350);
		sol1.setSize({ 100.0,100 });
		sf::FloatRect ss = sol1.getGlobalBounds();
		sol1.setOrigin(sf::Vector2f(ss.width / 2, ss.height / 2));

		



		//variableSwitch
		int isMove = 0, isJump = 0, ulti = 0, faceRight = 1;

		//variableSkill
		int change = 0, isSkilli[16], isSkillf[16], isSkillu[16], scount = 0, sdir[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		//variablePlayerDoing
		float speed = 600.0f, gravitySpeed, retard = 25.0f;
		int  onGround = 1, groundHeigh = 600;



		//------------------------------------------------------IN Game stage I------------------------
		while (window.isOpen())
		{
			dt = dtclock.restart().asSeconds();
			while (window.pollEvent(ev))
			{
				switch (ev.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (ev.key.code == sf::Keyboard::Escape)
						window.close();
					break;
				}
			}

			//runTimeLogic+gameTIme
			sf::Time elapsed = clock.getElapsedTime();
			showTime << f2min << f1min << ":" << f2sec << (int)elapsed.asSeconds() << ":" << elapsed.asMilliseconds() % 1000 / 10;
			if (elapsed.asSeconds() >= 10)
			{
				clock.restart();
				f2sec += 1;
			}
			if (f2sec >= 6)
			{
				f1min += 1;
				f2sec = 0;
			}
			if (f2min >= 10)
			{
				f1min += 1;
				f2min = 0;
			}
			lblTime.setString(showTime.str());
			showTime.str("");


			sf::Time Lcool = co1.getElapsedTime();
			sf::Time Jcool = co2.getElapsedTime();
			sf::Time Ucool = co3.getElapsedTime();


			//controlKey
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (onGround == 1)
				{
					sJump.play();
					isJump = 1;
					onGround = 0;
					gravitySpeed = -750.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				faceRight = -1;
				isMove = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				faceRight = 1;
				isMove = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
			{
				if (change == 0 && (Lcool.asSeconds() >= 0.5))
				{
					change = 1;
					co1.restart();
				}
				else if (change == 1 && (Lcool.asSeconds() >= 0.5))
				{
					change = 0;
					co1.restart();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && (Jcool.asSeconds() >= 0.2))
			{
				co2.restart();
				sBang.play();
				scount += 1;
				if (ulti == 1)
				{
					skillu[scount].setPos({ player.getX() + 30.0f, player.getY() + 53.0f });
					isSkillu[scount] = 1;
				}
				else if (change == 0)
				{
					skilli[scount].setPos({ player.getX() + 30.0f, player.getY() + 53.0f });
					isSkilli[scount] = 1;
				}
				else
				{
					skillf[scount].setPos({ player.getX() + 30.0f, player.getY() + 53.0f });
					isSkillf[scount] = 1;
				}
			}

			//playerDoing

			if (isMove == 1)
			{
				player.moveRight(speed * dt);
				isMove = 0;
			}
			if (isMove == -1)
			{
				player.moveLeft(speed * dt);
				isMove = 0;
			}
			if (isJump == 1)
			{
				if (onGround == 0)
				{
					player.jump(gravitySpeed * dt);
					gravitySpeed += retard;

					if (player.getY() >= groundHeigh)
					{
						onGround = 1;
						isJump = 0;
					}
				}
			}
			

			

			//skill+kill

			for (int i = 1; i <= scount; i++)
			{
				if (isSkillu[i] == 1)
				{
					if (sdir[i] == 0)
					{
						sdir[i] = faceRight;
					}
					if (sdir[i] == 1)
					{
						skillu[i].move((speed + 500) * dt);
					}
					if (sdir[i] == -1)
					{
						skillu[i].move(-(speed + 500) * dt);
					}
					if (enemy0.getGlobalBounds().intersects(skillu[i].getGlobalBounds()))
					{
						skillu[i].setPos({ -50.0f,-50.0f });
						enemy0.setPos({ -200.0f,-200.0f });
					}
					if (enemy1.getGlobalBounds().intersects(skillu[i].getGlobalBounds()))
					{
						skillu[i].setPos({ -50.0f,-50.0f });
						enemy1.setPos({ -200.0f,-200.0f });
					}
					if (enemy2.getGlobalBounds().intersects(skillu[i].getGlobalBounds()))
					{
						skillu[i].setPos({ -50.0f,-50.0f });
						enemy2.setPos({ -200.0f,-200.0f });
					}
					if (enemy3.getGlobalBounds().intersects(skillu[i].getGlobalBounds()))
					{
						skillu[i].setPos({ -50.0f,-50.0f });
						enemy3.setPos({ -200.0f,-200.0f });
					}
				}
				if (isSkilli[i] == 1)
				{
					if (sdir[i] == 0)
					{
						sdir[i] = faceRight;
					}
					if (sdir[i] == 1)
					{
						skilli[i].move((speed + 500) * dt);
					}
					if (sdir[i] == -1)
					{
						skilli[i].move(-(speed + 500) * dt);
					}
					if (enemy0.getGlobalBounds().intersects(skilli[i].getGlobalBounds()))
					{
						skilli[i].setPos({ -50.0f,-50.0f });
						enemy0.setPos({ -200.0f,-200.0f });
					}
					if (enemy1.getGlobalBounds().intersects(skilli[i].getGlobalBounds()))
					{
						skilli[i].setPos({ -50.0f,-50.0f });
						enemy1.setPos({ -200.0f,-200.0f });
					}

				}
				if (isSkillf[i] == 1)
				{
					if (sdir[i] == 0)
					{
						sdir[i] = faceRight;
					}
					if (sdir[i] == 1)
					{
						skillf[i].move((speed + 500) * dt);
					}
					if (sdir[i] == -1)
					{
						skillf[i].move(-(speed + 500) * dt);
					}
					if (enemy0.getGlobalBounds().intersects(skillf[i].getGlobalBounds()))
					{
						skillf[i].setPos({ -50.0f,-50.0f });
						enemy0.setPos({ -200.0f,-200.0f });
					}
					if (enemy2.getGlobalBounds().intersects(skillf[i].getGlobalBounds()))
					{
						skillf[i].setPos({ -50.0f,-50.0f });
						enemy2.setPos({ -200.0f,-200.0f });
					}
				}
			}
			if (scount == 15)
			{
				for (int i = 1; i <= 15; i++)
				{
					sdir[i] = 0;
				}
				scount = 1;
				//close_isSkill
			}


			if (player.getGlobalBounds().intersects(item.getGlobalBounds()))
			{
				item.setPOs({ -50.0f,-50.0f });
				ulti = 1;
			}

			if (player.getGlobalBounds().intersects(sol1.getGlobalBounds()))
			{
				std::cout <<"True" << endl;
			}
			else
			{
				std::cout <<player.getY() << endl;
			}
			






			//viewUpdate

			position.x = player.getX() + 400 - (window.getSize().x / 2.0f);
			position.y = player.getY() + 10 - (window.getSize().y / 1.0f);
			if (position.x < 0)
			{
				position.x = 0;
			}
			if (position.y < 0)
			{
				position.y = 0;
			}

			view.reset(sf::FloatRect(position.x, position.y, window.getSize().x, window.getSize().y));
			
			//updateUPPER
			hp1.setPos({ position.x + 10.0f,10.0f });
			hp2.setPos({ position.x + 60.0f,10.0f });
			hp3.setPos({ position.x + 110.0f,10.0f });
			mana1.setPos({ position.x + 10.0f,60.0f });
			mana2.setPos({ position.x + 40.0f,60.0f });
			mana3.setPos({ position.x + 70.0f,60.0f });
			mana4.setPos({ position.x + 100.0f,60.0f });
			mana5.setPos({ position.x + 130.0f,60.0f });
			
			lblStage.setPosition({position.x+1420.0f,10.0f});
			lblTime.setPosition({ position.x + 1420.0f,50.0f });
			//ToDraw
			window.clear();

			window.draw(bground);

			
			
			window.draw(sol1);
			


			window.setView(view);

			//enemy0.toDraw(window);
			//enemy1.toDraw(window);
			//enemy2.toDraw(window);
			//enemy3.toDraw(window);


			for (int i = 1; i <= scount; i++)
			{
				skilli[i].toDraw(window);
				skillf[i].toDraw(window);
				skillu[i].toDraw(window);
			}
			hp1.toDraw(window);
			hp2.toDraw(window);
			hp3.toDraw(window);
			mana1.toDraw(window);
			mana2.toDraw(window);
			mana3.toDraw(window);
			mana4.toDraw(window);
			mana5.toDraw(window);
			window.draw(heliR);
			window.draw(heliL);
			

			//item.toDraw(window);
			window.draw(lblStage);
			window.draw(lblTime);
			if (faceRight == 1)
			{
				player.toDrawR(window);
			}
			else
			{
				player.toDrawL(window);
			}
			//Draw
			window.display();
			
		}
	}


	


	return 0;
}


int checkBump(Player player)
{

}
