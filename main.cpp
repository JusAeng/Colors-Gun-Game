#include <iostream>
#include <sstream>
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

//int checkBump();

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
		bg.loadFromFile("map1r.png");
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
		player.setPos({ 3000.0,600.0 });

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

		sf::Texture heli1, heli2,texrope;
		heli1.loadFromFile("helicopterRanimation.png");
		heli2.loadFromFile("helicopterLanimation.png");
		texrope.loadFromFile("rope.png");
		sf::Sprite heliR, heliL[2],rope;
		heliR.setTexture(heli1);
		heliL[0].setTexture(heli2);
		heliL[0].setPosition(7472.0,15.0);
		heliL[1].setTexture(heli2);
		heliL[1].setPosition(8778, 15.0);
		heliR.setPosition(11567.0, 44.0);
		Animetion helicopR(&heli1,sf::Vector2u(1,4),0.05f);
		Animetion helicopL(&heli2, sf::Vector2u(1, 4), 0.05f);
		rope.setTexture(texrope);
		rope.setPosition(11666.0,162.0);
		
		
		
		
		
		//block
		Block finish({168,23}, {11666.0,620});

		Block h1box1({71,9}, { 7548.5,144.5});
		Block h1box2({149,19}, { 7581.5 ,122.5});
		Block h1box3({ 40,8 }, { 7728.5  ,119.5  });
		Block h1box4({ 132,12 }, { 7727.5  ,109.5 });
		Block h2box1({ 71,9 }, { 8855.5 ,145.5  });
		Block h2box2({ 149,19 }, { 8888.5  ,123.5  });
		Block h2box3({40,8}, { 9035.5 ,120.5  });
		Block h2box4({ 132,12 }, { 9034.5  ,110.5});

		Block woodair({ 1433.0,31.0 }, { 7639.5,330 });
		Block woodbox1({ 103.0,103.0 }, {6777,627});
		Block woodbox2({ 103.0,103.0 }, { 9745,613 });

		Block b1car1({ 234.5,93.0 }, {1543.0,640.5});
		Block b2car1({ 16,41 }, { 1636,605 });
		Block b3car1({ 17,78 }, {1788,645});
		b3car1.rotate(-30.38);
		Block b1car2({ 234.5,93.0 }, { 1543.0 + 3546,640.5 });
		Block b2car2({ 16,41 }, { 1636 + 3546,605 });
		Block b3car2({ 17,78 }, { 1788 + 3546,645 });
		b3car2.rotate(-30.38);

		Block d1car1({ 233,175 }, {3417,559});
		Block d2car1({ 16,41 }, {3506,521});
		Block d3car1({ 17,78 }, {3655.4,562});
		d3car1.rotate(-30.38);
		Block d4car1({17,78}, {3655,645});
		d4car1.rotate(-30.38);

		Block d1car2({ 233,175 }, { 3417 + 3749,559 });
		Block d2car2({ 16,41 }, { 3506 + 3749,521 });
		Block d3car2({ 17,78 }, { 3655.4 + 3749,562 });
		d3car2.rotate(-30.38);
		Block d4car2({ 17,78 }, { 3655 + 3749,645 });
		d4car2.rotate(-30.38);

		Block b1truck1({ 158,216 }, { 5373 ,511 });
		Block b2truck1({ 428,250 }, {5531 ,482});
		Block b1truck2({ 158,216 }, { 5373 + 4478,511 });
		Block b2truck2({ 428,250 }, { 5531 + 4478,482 });




		//variableSwitch
		int isMove = 0, isJump = 0, ulti = 0, faceRight = 1;

		//variableSkill
		int change = 0, isSkilli[16], isSkillf[16], isSkillu[16], scount = 0, sdir[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		//variablePlayerDoing
		float speed = 600.0f, gravitySpeed, retard = 25.0f,fallspeed=0;
		int  onGround = 1, groundHeigh = 600,onBox=0;



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

			//collide

			if (player.getGlobalBounds().intersects(woodbox2.getGlobalBounds()))
			{
				if (player.getX() - woodbox2.getPos().x <= 0 && isMove == 1 || player.getX() - woodbox2.getPos().x >= 0 && isMove == -1)
				{
					isMove = 0;
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
			if (isJump == 1 && onGround == 0)
			{
				player.jump(gravitySpeed * dt);
				gravitySpeed += retard;

				if (player.getY() >= groundHeigh)
				{
					onGround = 1;
					isJump = 0;
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
			
			window.setView(view);

			window.draw(rope);
			helicopR.Update(0,dt);
			heliR.setTextureRect(helicopR.uvRect);
			window.draw(heliR);
			helicopL.Update(0, dt);
			heliL[0].setTextureRect(helicopL.uvRect);
			heliL[1].setTextureRect(helicopL.uvRect);
			window.draw(heliL[0]);
			window.draw(heliL[1]);


			//blockcheck
			woodair.toDraw(window);
			woodbox1.toDraw(window);
			woodbox2.toDraw(window);

			h1box1.toDraw(window);
			h1box2.toDraw(window);
			h1box3.toDraw(window);
			h1box4.toDraw(window);
			h2box1.toDraw(window);
			h2box2.toDraw(window);
			h2box3.toDraw(window);
			h2box4.toDraw(window);

			b1car1.toDraw(window);
			b2car1.toDraw(window);
			b3car1.toDraw(window);
			b1car2.toDraw(window);
			b2car2.toDraw(window);
			b3car2.toDraw(window);

			d1car1.toDraw(window);
			d2car1.toDraw(window);
			d3car1.toDraw(window);
			d4car1.toDraw(window);
			d1car2.toDraw(window);
			d2car2.toDraw(window);
			d3car2.toDraw(window);
			d4car2.toDraw(window);

			b1truck1.toDraw(window);
			b2truck1.toDraw(window);
			b1truck2.toDraw(window);
			b2truck2.toDraw(window);

			finish.toDraw(window);
			//--------------------


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
			window.draw(lblStage);
			window.draw(lblTime);


			//enemy0.toDraw(window);
			//enemy1.toDraw(window);
			//enemy2.toDraw(window);
			//enemy3.toDraw(window);

			//item.toDraw(window);

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


/*int checkBump(Player player,Block block)
{
	if (player.getGlobalBounds().intersects(block.getGlobalBounds()) && )
}*/
