#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Menu.h"
#include "block.h"
#include "Animetion.h"


#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

using namespace std;

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
		window.setFramerateLimit(60);
		float dt;  //(deltatime)

		//viewSet
		sf::View view;
		view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
		view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
		sf::Vector2f position(window.getSize().x, window.getSize().y);

		//background
		sf::Texture bg;
		bg.loadFromFile("map1r.png");
		sf::RectangleShape bground;
		bground.setSize(sf::Vector2f(12000, 780));
		bground.setTexture(&bg);

		//main music
		sf::Music music;
		music.openFromFile("mainSong.ogg");
		music.setVolume(5.0);
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

		//upperText
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

		sf::Text lblTime;
		lblTime.setCharacterSize(30);
		lblTime.setPosition({ 1420,50 });
		lblTime.setFont(font);

		//Mana+Hp
		ostringstream pickmana;
		ostringstream pickheart;

		sf::Texture h6, m4;
		h6.loadFromFile("h6.png");
		sf::Sprite heart;
		heart.setTexture(h6);
		heart.setPosition(0, 0);

		m4.loadFromFile("m4.png");
		sf::Sprite mana;
		mana.setTexture(m4);
		mana.setPosition(0, 50);

		//BackGroundAnimation
		sf::Texture heli1, heli2, texrope;
		heli1.loadFromFile("helicopterRanimation.png");
		heli2.loadFromFile("helicopterLanimation.png");
		texrope.loadFromFile("rope.png");
		sf::Sprite heliR, heliL[2], rope;
		heliR.setTexture(heli1);
		heliL[0].setTexture(heli2);
		heliL[0].setPosition(7472.0, 15.0);
		heliL[1].setTexture(heli2);
		heliL[1].setPosition(8778, 15.0);
		heliR.setPosition(11567.0, 44.0);
		Animetion helicopR(&heli1, sf::Vector2u(1, 4), 0.05f);
		Animetion helicopL(&heli2, sf::Vector2u(1, 4), 0.05f);
		rope.setTexture(texrope);
		rope.setPosition(11666.0, 162.0);

		//Clock_use
		sf::Clock co1; //Lswitch
		sf::Clock co2; //Jswitch
		sf::Clock co3; //Ulti
		sf::Clock dtclock; //deltaTime
		sf::Clock cmanaClock; //manaGain







		//PlayerObject
		Player player({ 84.0,112.0 });
		player.setOrigin();
		player.setPos({ 300.0,664.0 });
		sf::Vector2f playerHalf = player.getSize()/2.0f;

		//item
		Item item;
		item.setPOs({ 1300.0,380.0 });

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



		Block b1;
		vector<Block> blocks;

		sf::Vector2f pos[26],siz[26];
		pos[0] = { 5373 ,511 };			//truck
		pos[1] = { 5531 ,482 };
		pos[2] = { 5373 + 4478,511 };
		pos[3] = { 5531 + 4478,482 };
		pos[4] = { 1543.0,640.5 };		//singCar
		pos[5] = { 1636,605 };
		pos[6] = { 1767.5,652.5 };
		pos[7] = { 1770.5,664.5 };
		pos[8] = { 1543.0 + 3546,637 };
		pos[9] = { 5181.5,600.5 };
		pos[10] = { 3407,559 };			//doubCar
		pos[11] = { 3506,521 };
		pos[12] = { 3638.5,567.5 };
		pos[13] = { 3642,584 };
		pos[14] = { 3417 + 3749,559 };
		pos[15] = { 3506 + 3749,521 };
		pos[16] = { 7391,569 };
		pos[17] = { 7393,590 };
		pos[18] = { 7639.5,330 };		//box
		pos[19] = { 6777,627 };
		pos[20] = { 9745,613 };
		pos[21] = { 7540,127 };			//helicopter
		pos[22] = { 7717,27 };
		pos[23] = { 8860,24 };
		pos[24] = { 9037,93 };
		pos[25] = { 11666.0,620 };		//finish

		siz[0] = { 158,216 };			//truck
		siz[1] = { 428,250 };
		siz[2] = { 158,216 };
		siz[3] = { 428,250 };
		siz[4] = { 234.5,93.0 };		//singCar
		siz[5] = { 16,41 };
		siz[6] = { 22,23 };
		siz[7] = { 38,69 };
		siz[8] = { 284,93 };
		siz[9] = { 16,41 };
		siz[10] = { 243,175 };			//doubCar
		siz[11] = { 16,41 };
		siz[12] = { 22,23 };
		siz[13] = { 35,150 };
		siz[14] = { 244,175 };
		siz[15] = { 16,41 };
		siz[16] = { 25,22 };
		siz[17] = { 38,139 };
		siz[18] = { 1433.0,31.0 };		//box
		siz[19] = { 103.0,103.0 };
		siz[20] = { 103.0,103.0 };
		siz[21] = { 190,25 };			//helicopter
		siz[22] = { 170,104 };
		siz[23] = { 190,124 };
		siz[24] = { 145,32 };
		siz[25] = { 168,23 };			//finish


		int size = 0;

		//variableSwitch
		int isMove = 0, isJump = 0, ulti = 0, faceRight = 1;

		//variableSkill
		int change = 0, isSkilli[16], isSkillf[16], isSkillu[16], scount = 0, sdir[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		int cmana=4,manax=4;

		//variablePlayerDoing
		float speed = 600.0f, Yspeed, retard = 25.0f,fallspeed=0,Rspeed=600.0f,Lspeed=600.0f;
		int  onGround = 1, groundHeigh = 662,boxx=0;

		int cheart = 6;

		//block
		float dx, dy;
		float intersectX,intersectY;

		
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

			//RunTime
			elapsed = clock.getElapsedTime();
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

			//Cooldown
			sf::Time Lcool = co1.getElapsedTime();
			sf::Time Jcool = co2.getElapsedTime();
			sf::Time Utime = co3.getElapsedTime();
			sf::Time gainMana = cmanaClock.getElapsedTime();



			
			//controlKey
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (onGround == 1)
				{
					sJump.play();
					isJump = 1;
					onGround = 0;
					Yspeed = -750.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				Lspeed = 600.0f;
				faceRight = -1;
				isMove = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				Rspeed = 600.0f;
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
				if (cmana > 0)
				{
					cmana -= 1;
					pickmana << "m" << cmana << ".png";
					m4.loadFromFile(pickmana.str());
					pickmana.str("");
					mana.setTexture(m4);

					co2.restart();
					sBang.play();
					scount += 1;
					if (ulti == 1)
					{
						skillu[scount].setPos({ player.getX() , player.getY()-5});
						isSkillu[scount] = 1;
					}
					else if (change == 0)
					{
						skilli[scount].setPos({ player.getX() , player.getY()-5 });
						isSkilli[scount] = 1;
					}
					else
					{
						skillf[scount].setPos({ player.getX() , player.getY()-5 });
						isSkillf[scount] = 1;
					}
				}
			}

			//Cant move LimitMap
			if (player.getX()-player.getSize().x/2.0f <= 0)
			{
				Lspeed = 0;
			}
			if (player.getX() + player.getSize().x / 2.0f >= 11999)
			{
				Rspeed = 0;
			}
			
			//Mana_Charge & Use
			if (cmana == manax)
			{
				cmanaClock.restart();
			}
			if (gainMana.asSeconds()>=1.5)
			{
				if (cmana < manax)
				{
					cmana += 1;
					pickmana << "m" << cmana << ".png";
					m4.loadFromFile(pickmana.str());
					pickmana.str("");
					mana.setTexture(m4);
					cmanaClock.restart();
				}
			}

			/*
			cheart -= 1;
			pickheart << "h" << cheart << ".png";
			h6.loadFromFile(pickheart.str());
			pickheart.str("");
			*/




			//CheckBlock
			if (size < 27)
			{
				b1.set({ pos[size] }, { siz[size] });
				blocks.push_back(b1);
				size++;
			}
			for (size_t i = 0; i < blocks.size(); i++)
			{
				if (player.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
				{
					dx = player.getX() - blocks[i].getPos().x;
					dy = player.getY() - blocks[i].getPos().y;
					float intersectX = abs(dx) - (playerHalf.x + blocks[i].getSize().x / 2.0f);
					float intersectY = abs(dy) - (playerHalf.y + blocks[i].getSize().y / 2.0f);
					if (intersectX > intersectY)
					{
						if (dx > 0.0f)
						{
							Lspeed = 0;
						}
						else
						{
							Rspeed = 0;
						}
					}
					else
					{
						if (dy < 0.0f)
						{
							isJump = 0;
							onGround = 1;
							Yspeed = -25.0f;
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
							{
								if (onGround == 1)
								{
									sJump.play();
									isJump = 1;
									onGround = 0;
									Yspeed = -750.0f;
								}
							}
						}
						else
						{

						}
					}
				}
			}



			//playerDoing

			if (isMove == 1)
			{
				player.moveRight(Rspeed * dt);
				isMove = 0;
			}
			if (isMove == -1)
			{
				player.moveLeft(Lspeed * dt);
				isMove = 0;
			}
			if (isJump == 1 && onGround == 0)
			{
				player.moveY(Yspeed * dt);
				Yspeed += retard;

				if (player.getY() >= groundHeigh)
				{
					onGround = 1;
					isJump = 0;
				}
			}
			if (isJump == 0 && player.getY() < groundHeigh)
			{
				Yspeed += 25.0f;
				player.moveY(Yspeed* dt);
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
				co3.restart();
				item.setPOs({ -50.0f,-50.0f });
				ulti = 1;
			}
			if (Utime.asSeconds() >= 12)
			{
				ulti = 0;
				co3.restart();
			}


		
			


			
			
			

			

			
			




















			//viewUpdate

			position.x = player.getX() + 400 - (window.getSize().x / 2.0f);
			position.y = player.getY() + 10 - (window.getSize().y / 1.0f);
			if (position.x < 0)
			{
				position.x = 0;
			}
			if (position.x >= 10439)
			{
				position.x = 10440;
			}
			if (position.y < 0)
			{
				position.y = 0;
			}
			view.reset(sf::FloatRect(position.x, position.y, window.getSize().x, window.getSize().y));
			lblStage.setPosition({position.x+1420.0f,10.0f});
			lblTime.setPosition({ position.x + 1420.0f,50.0f });
			heart.setPosition(10 + position.x, 10);
			mana.setPosition(19+position.x,57);

			//ToDraw
			window.clear();
			window.setView(view);
			window.draw(bground);
			
			
			window.draw(rope);
			helicopR.Update(0,dt);
			heliR.setTextureRect(helicopR.uvRect);
			window.draw(heliR);
			helicopL.Update(0, dt);
			heliL[0].setTextureRect(helicopL.uvRect);
			heliL[1].setTextureRect(helicopL.uvRect);
			window.draw(heliL[0]);
			window.draw(heliL[1]);
			

			/*for (size_t i = 0; i < blocks.size(); i++)
			{
				window.draw(blocks[i].body);
			}*/

			for (int i = 1; i <= scount; i++)
			{
				skilli[i].toDraw(window);
				skillf[i].toDraw(window);
				skillu[i].toDraw(window);
			}

			window.draw(heart);
			window.draw(mana);
			window.draw(lblStage);
			window.draw(lblTime);
			

			//enemy0.toDraw(window);
			//enemy1.toDraw(window);
			//enemy2.toDraw(window);
			//enemy3.toDraw(window);

			item.toDraw(window);

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

