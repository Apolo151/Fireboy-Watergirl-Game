#include <SFML/Graphics.hpp>
#include <iostream>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;
void score(Sprite Red[],RectangleShape& player1, Sprite Blue[], RectangleShape& player2,int& Sc,Text& Scboard);
int score_func()
{
	RenderWindow window(sf::VideoMode(1280, 720), "Fire boy & Water girl");
	window.setFramerateLimit(30);
	//player1
	Texture player1;
	player1.loadFromFile("resources/images/tb.png");
	RectangleShape p1(Vector2f(200, 200));
	p1.setTexture(&player1);
	p1.setPosition(30, 500);
	//
	//player2
	RectangleShape p2(Vector2f(200, 200));
	Texture player2;
	player2.loadFromFile("resources/images/gg.png");
	p2.setTexture(&player2);
	p2.setPosition(100, 500);
	//
	//Arrays of daimonds
	Sprite B_daimond[4];
	Sprite R_daimond[4];
	//
	// Texture of daimonds
	Texture R_daimondTexture;
	R_daimondTexture.loadFromFile("resources/images/CharAssets.png");

	Texture B_daimondTexture;
	B_daimondTexture.loadFromFile("resources/images/CharAssets.png");

	for (int i = 0; i < 4; ++i)
		{
		   R_daimond[i].setTexture(R_daimondTexture);
		   R_daimond[i].setScale(0.5, 0.5);
		   R_daimond[i].setPosition(200 + (60 * (pow(i, 2) - 1)), 100 + (50 * (pow(i, 2) - 1)));
		   R_daimond[i].setTextureRect(IntRect(136 * 8, 136 * 10, 136, 136));
		}

	for (int i = 0; i < 4; ++i)
		{
			B_daimond[i].setTexture(B_daimondTexture);
			B_daimond[i].setScale(0.5, 0.5);
			B_daimond[i].setPosition(200 + (60 * (pow(i, 2) + 5)), 150 + (30 * (pow(i, 2) +4)));
			B_daimond[i].setTextureRect(IntRect(136 * 7, 136 * 10, 136, 136));
		}
	//
	//Score board
	int Score=0;
	Font font;
	font.loadFromFile("TrajanPro-Bold.otf");

	Text ScoreBoard;
	ScoreBoard.setFont(font);
	ScoreBoard.setString("Score: " + to_string(Score));
	ScoreBoard.setFillColor(Color(220, 220, 50, 255));
	ScoreBoard.setPosition(20, 20);
	ScoreBoard.setCharacterSize(35);
	ScoreBoard.Bold;
	//
	//Music
	Music music;
	music.openFromFile("MenuMusic.ogg");
	music.play();
	//
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//
		//player1 movement
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
		{
			p1.move(0, -5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			p1.move(0,5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			p1.move(5,0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			p1.move(-5, 0);
		}
		//
		//player2 movement
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			p2.move(0, -5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			p2.move(0, 5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		{
			p2.move(5, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			p2.move(-5, 0);
		}
		//
		//Score
		score(R_daimond, p1, B_daimond, p2, Score, ScoreBoard);
		//
		window.clear();
		window.draw(p1);
		window.draw(p2);
		for (int i = 0; i < 4; ++i)
		{
			window.draw(R_daimond[i]);
			window.draw(B_daimond[i]);
		}
		window.draw(ScoreBoard);
		window.display();
	}
	
	return 0;
} 
//Score
void score(Sprite Red[], RectangleShape& player1, Sprite Blue[], RectangleShape& player2,int& Sc,Text& Scboard)
{
	//red daimonds
	for (int i = 0; i < 4; ++i)
		{
		  if (player1.getGlobalBounds().intersects(Red[i].getGlobalBounds()))
			{
				Red[i].setScale(0, 0);
				++Sc;
				Scboard.setString("Score: " + to_string(Sc));
			}
		}
    //blue daimonds
	for (int i = 0; i < 4; ++i)
		{
		  if (player2.getGlobalBounds().intersects(Blue[i].getGlobalBounds()))
			{
				Blue[i].setScale(0, 0);
				++Sc;
				Scboard.setString("Score: " + to_string(Sc));
			}
		}
}