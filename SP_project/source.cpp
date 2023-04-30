#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include"Menu.h"

using namespace std;
using namespace sf;
const string RESOURCES = "resources/";
bool z = false;

/* Write functions declarations*/
void score(Sprite Red[], Sprite Blue[], int& Sc, Text& Scboard);
//int animate_func(RenderWindow& window, Sprite& player1, Sprite& player2);
void create_characters();
void setup_score_and_sound(Sprite red_diamonds[], Sprite blue_diamonds[] /*Text& ScoreBoard,*/);
void setup_env_and_lakes();
void draw_all(RenderWindow& window, Sprite red_diamonds[], Sprite blue_diamonds[]); 
void deal_with_interactions();
void background(RenderWindow& window);

/* Declare global variables*/
Font ScoreFont;
Text ScoreBoard;
int Score = 0;
Music music;
Sprite Fireboy, Watergirl, FireLake, WaterLake, Wire, Rope;// , red_diamonds[4], blue_diamonds[4];
Texture load_photo1, load_photo2, R_diamondTexture, B_diamondTexture, FireLakeTexture, WaterLakeTexture, WireTexture, RopeTexture;




int GamePlay(RenderWindow& window);



int main()
{
	//make a main window
	RenderWindow window(VideoMode(950, 750), "Fireboy & watergirl", Style::Default);
	Menu menu(window.getSize().x, window.getSize().y);
	//set background
	RectangleShape backg;
	backg.setSize(Vector2f(950, 750));
	Texture Maintexture;
	Maintexture.loadFromFile(RESOURCES+"images/menu_image.jpg");
	backg.setTexture(&Maintexture);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					menu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					menu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Enter)
				{	
					//RenderWindow SETTINGS(VideoMode(950, 750), "Settings");
					int x = menu.pressed();
					if (x == 0)
					{
						Score = 0;
						// Create Game window
						RenderWindow PLAY(VideoMode(1280, 720), "Game");
						PLAY.setFramerateLimit(30);

						/*--Setup stuff before going into game loop--*/
						Sprite red_diamonds[4], blue_diamonds[4];
						// setup score & diamonds & sound
						setup_score_and_sound(red_diamonds, blue_diamonds);
						// setup ENV
						setup_env_and_lakes();
						// Setup Characters texture
						create_characters();
						// Setup Stuff for animation
						int row1_B = 10, row2_B = 20, StopRow_B = 10;
						double jumpV_B = 0; bool isgrounded_B = false;
						int row1_G = 22, row2_G = 5, StopRow_G = 20;
						double jumpV_G = 0; bool isgrounded_G = false;
						// for making rectangle for jumping on it
						RectangleShape rect(Vector2f(1500, 50));
						rect.setPosition(0, 700);
						/*-------------------------------------------*/
						while (PLAY.isOpen()) {
							// setup animation
							// calcuate score
							score(red_diamonds, blue_diamonds, Score, ScoreBoard);
							deal_with_interactions();

							// fireboy controls :
							if (Keyboard::isKeyPressed(Keyboard::Key::Right))
							{
								Fireboy.move(10, 0);
								Fireboy.setTextureRect(IntRect(row1_B, -22, 70, 100));
								row1_B += 80;
								row1_B %= 320;
							}


							else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
							{
								Fireboy.move(-10, 0);
								Fireboy.setTextureRect(IntRect(row2_B, 78, 70, 100));
								row2_B += 80;
								row2_B %= 320;
							}

							else
							{
								Fireboy.setTextureRect(IntRect(StopRow_B, 400, 55, 100));
								StopRow_B += 80;
								StopRow_B %= 400;
							}

							// wategirl controls :

							if (Keyboard::isKeyPressed(Keyboard::Key::A))
							{
								Watergirl.move(-10, 0);
								Watergirl.setTextureRect(IntRect(row1_G, 18, 90, 80));
								row1_G += 100;
								row1_G %= 400;
							}

							else if (Keyboard::isKeyPressed(Keyboard::Key::D))
							{
								Watergirl.move(10, 0);
								Watergirl.setTextureRect(IntRect(row2_G, 118, 96, 80));
								row2_G += 100;
								row2_G %= 400;
							}
							else
							{
								Watergirl.setTextureRect(IntRect(StopRow_G, 472, 56, 86));
								StopRow_G += 80;
								StopRow_G %= 320;
							}

							// fire boy jumping code

							if (rect.getGlobalBounds().intersects(Fireboy.getGlobalBounds()))
							{
								isgrounded_B = true;
								jumpV_B = 0;

								if (Keyboard::isKeyPressed(Keyboard::Key::Up))
								{
									jumpV_B = 20;
								}
							}
							else
							{
								isgrounded_B = false;
								jumpV_B -= 1.5;
							}

							// water girl jumping code 

							if (rect.getGlobalBounds().intersects(Watergirl.getGlobalBounds()))
							{
								isgrounded_G = true;
								jumpV_G = 0;

								if (Keyboard::isKeyPressed(Keyboard::Key::W))
								{
									jumpV_G = 20;
								}
							}
							else
							{
								isgrounded_G = false;
								jumpV_G -= 1.5;
							}

							//
							PLAY.draw(rect);	
							draw_all(PLAY, red_diamonds, blue_diamonds);
							Fireboy.move(0, -jumpV_B);
							Watergirl.move(0, -jumpV_G);
							PLAY.display();
							Event aevent;
							while (PLAY.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									music.stop();
									PLAY.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{	
										music.stop();
										PLAY.close();
									}
								}
							}
						}
						
					}
					if (x == 1)
					{
						RenderWindow SETTINGS(VideoMode(950, 750), "Settings");
						while (SETTINGS.isOpen())
						{
							Event aevent;
							while (SETTINGS.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									SETTINGS.close();
								}
								/*if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										PLAY.close();
									}
								}
								*/
							}
							//PLAY.close();
							SETTINGS.clear();
							SETTINGS.display();
						}
					}
					if (x == 2)

						window.close();
					break;

				}
			}
		}
		window.clear();
		window.draw(backg);
		menu.draw(window);
		window.display();
	}
	return 0;
}

int GamePlay(RenderWindow& PLAY){

	while (PLAY.isOpen())
	{
		
		
	}
	return 0;
}

void create_characters() {
	// for charachter fireboy
	
	load_photo1.loadFromFile(RESOURCES + "sprites/fireboy_sprite.png");
	Fireboy.setTexture(load_photo1);
	Fireboy.setTextureRect(IntRect(467, 277, 55, 100));
	Fireboy.setPosition(100, 100);
	Fireboy.scale(1, 1);

	// for charachter watergirl
	load_photo2.loadFromFile(RESOURCES + "sprites/watergirl_sprite.png");
	Watergirl.setTexture(load_photo2);
	Watergirl.setTextureRect(IntRect(340, 472, 56, 86));
	Watergirl.setPosition(150, 100);
	Watergirl.scale(1, 1);
	//
	return;
}

void background(RenderWindow& window) {
	Texture tbback;
	tbback.loadFromFile("bbackground.png");
	tbback.setRepeated(true);

	Sprite sbback;
	sbback.setTexture(tbback);
	sbback.setTextureRect({ 0, 0,1280, 720 });

	Texture tback;
	tback.loadFromFile("background2.png");
	tback.setRepeated(true);

	Sprite sback;
	sback.setTexture(tback);
	sback.setTextureRect({ 0, 0,1280, 720 });



	sf::VertexArray f1(sf::TriangleStrip, 9);
	f1[0].position = sf::Vector2f(30.f, 425.f);
	f1[1].position = sf::Vector2f(30.f, 450.f);
	f1[2].position = sf::Vector2f(470.f, 425.f);
	f1[3].position = sf::Vector2f(420.f, 450.f);
	f1[4].position = sf::Vector2f(520.f, 500.f);
	f1[5].position = sf::Vector2f(470.f, 525.f);
	f1[6].position = sf::Vector2f(1025.f, 500.f);
	f1[7].position = sf::Vector2f(645.f, 525.f);
	f1[8].position = sf::Vector2f(1090.f, 525.f);

	f1[0].texCoords = sf::Vector2f(30.f, 425.f);
	f1[1].texCoords = sf::Vector2f(30.f, 450.f);
	f1[2].texCoords = sf::Vector2f(470.f, 425.f);
	f1[3].texCoords = sf::Vector2f(420.f, 450.f);
	f1[4].texCoords = sf::Vector2f(520.f, 500.f);
	f1[5].texCoords = sf::Vector2f(470.f, 525.f);
	f1[6].texCoords = sf::Vector2f(1025.f, 500.f);
	f1[7].texCoords = sf::Vector2f(645.f, 525.f);
	f1[8].texCoords = sf::Vector2f(1090.f, 525.f);

	sf::VertexArray f2(sf::TriangleStrip, 8);
	f2[0].position = sf::Vector2f(175.f, 310.f);
	f2[1].position = sf::Vector2f(175.f, 340.f);
	f2[2].position = sf::Vector2f(580.f, 310.f);
	f2[3].position = sf::Vector2f(530.f, 340.f);
	f2[4].position = sf::Vector2f(600.f, 340.f);
	f2[5].position = sf::Vector2f(550.f, 370.f);
	f2[6].position = sf::Vector2f(1280.f, 340.f);
	f2[7].position = sf::Vector2f(1280.f, 370.f);

	f2[0].texCoords = sf::Vector2f(175.f, 310.f);
	f2[1].texCoords = sf::Vector2f(175.f, 340.f);
	f2[2].texCoords = sf::Vector2f(580.f, 310.f);
	f2[3].texCoords = sf::Vector2f(530.f, 340.f);
	f2[4].texCoords = sf::Vector2f(600.f, 340.f);
	f2[5].texCoords = sf::Vector2f(550.f, 370.f);
	f2[6].texCoords = sf::Vector2f(1280.f, 340.f);
	f2[7].texCoords = sf::Vector2f(1280.f, 370.f);

	sf::VertexArray f3(sf::TriangleStrip, 4);
	f3[0].position = sf::Vector2f(29.f, 130.f);
	f3[1].position = sf::Vector2f(29.f, 230.f);
	f3[2].position = sf::Vector2f(230.f, 130.f);
	f3[3].position = sf::Vector2f(230.f, 230.f);

	f3[0].texCoords = sf::Vector2f(29.f, 130.f);
	f3[1].texCoords = sf::Vector2f(29.f, 230.f);
	f3[2].texCoords = sf::Vector2f(230.f, 130.f);
	f3[3].texCoords = sf::Vector2f(230.f, 230.f);

	sf::VertexArray g1(sf::TriangleStrip, 4);
	g1[0].position = sf::Vector2f(0.f, 0.f);
	g1[1].position = sf::Vector2f(0.f, 720.f);
	g1[2].position = sf::Vector2f(30.f, 0.f);
	g1[3].position = sf::Vector2f(30.f, 720.f);

	g1[0].texCoords = sf::Vector2f(0.f, 0.f);
	g1[1].texCoords = sf::Vector2f(0.f, 720.f);
	g1[2].texCoords = sf::Vector2f(30.f, 0.f);
	g1[3].texCoords = sf::Vector2f(30.f, 720.f);

	sf::VertexArray g2(sf::TriangleStrip, 4);
	g2[0].position = sf::Vector2f(0.f, 690.f);
	g2[1].position = sf::Vector2f(0.f, 720.f);
	g2[2].position = sf::Vector2f(1280.f, 690.f);
	g2[3].position = sf::Vector2f(1280.f, 720.f);

	g2[0].texCoords = sf::Vector2f(0.f, 690.f);
	g2[1].texCoords = sf::Vector2f(0.f, 720.f);
	g2[2].texCoords = sf::Vector2f(1280.f, 690.f);
	g2[3].texCoords = sf::Vector2f(1280.f, 720.f);

	sf::VertexArray g3(sf::TriangleStrip, 4);
	g3[0].position = sf::Vector2f(1250.f, 0.f);
	g3[1].position = sf::Vector2f(1250.f, 720.f);
	g3[2].position = sf::Vector2f(1280.f, 0.f);
	g3[3].position = sf::Vector2f(1280.f, 720.f);

	g3[0].texCoords = sf::Vector2f(1250.f, 0.f);
	g3[1].texCoords = sf::Vector2f(1250.f, 720.f);
	g3[2].texCoords = sf::Vector2f(1280.f, 0.f);
	g3[3].texCoords = sf::Vector2f(1280.f, 720.f);

	sf::VertexArray g4(sf::TriangleStrip, 4);
	g4[0].position = sf::Vector2f(0.f, 0.f);
	g4[1].position = sf::Vector2f(0.f, 30.f);
	g4[2].position = sf::Vector2f(1280.f, 0.f);
	g4[3].position = sf::Vector2f(1280.f, 30.f);

	g4[0].texCoords = sf::Vector2f(0.f, 0.f);
	g4[1].texCoords = sf::Vector2f(0.f, 30.f);
	g4[2].texCoords = sf::Vector2f(1280.f, 0.f);
	g4[3].texCoords = sf::Vector2f(1280.f, 30.f);

	sf::VertexArray block1(sf::TriangleStrip, 5);
	block1[0].position = sf::Vector2f(1150.f, 570.f);
	block1[1].position = sf::Vector2f(1115.f, 615.f);
	block1[2].position = sf::Vector2f(1280.f, 570.f);
	block1[3].position = sf::Vector2f(1115.f, 720.f);
	block1[4].position = sf::Vector2f(1280.f, 720.f);

	block1[0].texCoords = sf::Vector2f(1150.f, 570.f);
	block1[1].texCoords = sf::Vector2f(1115.f, 615.f);
	block1[2].texCoords = sf::Vector2f(1280.f, 570.f);
	block1[3].texCoords = sf::Vector2f(1115.f, 720.f);
	block1[4].texCoords = sf::Vector2f(1280.f, 720.f);

	sf::VertexArray block2(sf::TriangleStrip, 4);
	block2[0].position = sf::Vector2f(225.f, 195.f);
	block2[1].position = sf::Vector2f(225.f, 230.f);
	block2[2].position = sf::Vector2f(520.f, 195.f);
	block2[3].position = sf::Vector2f(520.f, 230.f);

	block2[0].texCoords = sf::Vector2f(225.f, 195.f);
	block2[1].texCoords = sf::Vector2f(225.f, 230.f);
	block2[2].texCoords = sf::Vector2f(520.f, 195.f);
	block2[3].texCoords = sf::Vector2f(520.f, 230.f);

	sf::VertexArray block3(sf::TriangleStrip, 8);
	block3[0].position = sf::Vector2f(515.f, 150.f);
	block3[1].position = sf::Vector2f(515.f, 230.f);
	block3[2].position = sf::Vector2f(705.f, 150.f);
	block3[3].position = sf::Vector2f(850.f, 230.f);
	block3[4].position = sf::Vector2f(850.f, 195.f);
	block3[5].position = sf::Vector2f(900.f, 250.f);
	block3[6].position = sf::Vector2f(1100.f, 195.f);
	block3[7].position = sf::Vector2f(1100.f, 250.f);

	block3[0].texCoords = sf::Vector2f(515.f, 150.f);
	block3[1].texCoords = sf::Vector2f(515.f, 230.f);
	block3[2].texCoords = sf::Vector2f(705.f, 150.f);
	block3[3].texCoords = sf::Vector2f(850.f, 230.f);
	block3[4].texCoords = sf::Vector2f(850.f, 195.f);
	block3[5].texCoords = sf::Vector2f(900.f, 250.f);
	block3[6].texCoords = sf::Vector2f(1100.f, 195.f);
	block3[7].texCoords = sf::Vector2f(1100.f, 250.f);

	Texture tg;
	tg.loadFromFile("background1.png");
	tg.setRepeated(true);


	Texture tg2;
	tg2.loadFromFile("background3.png");
	tg2.setRepeated(true);


	sf::RectangleShape rec1(sf::Vector2f(300.f, 35.f));
	rec1.setPosition(30, 560);
	rec1.setTexture(&tg2);


	// doors
	int waterdoor = 3;

	Texture wdoor;
	wdoor.loadFromFile("water door1.PNG");
	Sprite swdoor;
	swdoor.setTexture(wdoor);
	swdoor.setTextureRect(IntRect(waterdoor, 1, 110, 125));
	swdoor.setPosition(140, 36);
	swdoor.scale(0.75, 0.75);

	int firedoor = 3;

	Texture fdoor;
	fdoor.loadFromFile("fire door1.PNG");
	Sprite sfdoor;
	sfdoor.setTexture(fdoor);
	sfdoor.setTextureRect(IntRect(firedoor, 1, 110, 125));
	sfdoor.setPosition(33, 36);
	sfdoor.scale(0.75, 0.75);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i mousepo = Mouse::getPosition(window);
				cout << mousepo.x << " " << mousepo.y << endl;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				swdoor.setTextureRect(IntRect(waterdoor, 1, 110, 125));
				waterdoor += 160;
				waterdoor %= 3040;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
				sfdoor.setTextureRect(IntRect(firedoor, 1, 110, 125));
				firedoor += 160;
				firedoor %= 2720;
			}


		}

		window.clear();
		window.draw(sbback);
		window.draw(sback);
		window.draw(f1, &tg);
		window.draw(f2, &tg);
		window.draw(f3, &tg);
		window.draw(rec1);
		window.draw(g1, &tg);
		window.draw(g2, &tg);
		window.draw(g3, &tg);
		window.draw(g4, &tg);
		window.draw(block1, &tg);
		window.draw(block2, &tg);
		window.draw(block3, &tg);
		window.draw(sfdoor);
		window.draw(swdoor);
}
void setup_env_and_lakes() {
	//rope:
	RopeTexture.loadFromFile(RESOURCES+"images/rope.png");
	Rope.setTexture(RopeTexture);
	Rope.setPosition(750, 340);
	Rope.setScale(0.25, 0.25);
	//firelake:
	FireLakeTexture.loadFromFile(RESOURCES + "images/flake.png");
	FireLake.setTexture(FireLakeTexture);
	FireLake.setPosition(550, 350);
	FireLake.setScale(0.7, 0.7);

	//wirewire.png"
	WireTexture.loadFromFile(RESOURCES + "images/wire.png");
	Wire.setTexture(WireTexture);
	Wire.setPosition(550, 550);
	Wire.setScale(0.4, 0.4);
	//waterlake
	WaterLakeTexture.loadFromFile(RESOURCES + "images/wlake.png");
	WaterLake.setTexture(WaterLakeTexture);
	WaterLake.setPosition(750, 620);
	WaterLake.setScale(0.6, 0.6);
}

void setup_score_and_sound(Sprite red_diamonds[], Sprite blue_diamonds[] /*Text& ScoreBoard,*/)
{
	// Texture of diamonds
	R_diamondTexture.loadFromFile(RESOURCES+"images/CharAssets.png");
	B_diamondTexture.loadFromFile(RESOURCES + "images/CharAssets.png");

	for (int i = 0; i < 4; ++i)
	{
		red_diamonds[i].setTexture(R_diamondTexture);
		red_diamonds[i].setScale(0.5, 0.5);
		red_diamonds[i].setPosition(200 + (60 * (pow(i, 2) - 1)), 100 + (50 * (pow(i, 2) - 1)));
		red_diamonds[i].setTextureRect(IntRect(136 * 8, 136 * 10, 136, 136));
	}

	for (int i = 0; i < 4; ++i)
	{
		blue_diamonds[i].setTexture(B_diamondTexture);
		blue_diamonds[i].setScale(0.5, 0.5);
		blue_diamonds[i] .setPosition(200 + (60 * (pow(i, 2) + 5)), 150 + (30 * (pow(i, 2) + 4)));
		blue_diamonds[i].setTextureRect(IntRect(136 * 7, 136 * 10, 136, 136));
	}

	//Score
	ScoreFont.loadFromFile(RESOURCES + "fonts/TrajanPro-Bold.otf");
	ScoreBoard.setFont(ScoreFont);
	ScoreBoard.setString("Score: " + to_string(Score));
	ScoreBoard.setFillColor(Color(220, 220, 50, 255));
	ScoreBoard.setPosition(20, 20);
	ScoreBoard.setCharacterSize(35);
	ScoreBoard.Bold;
	
	//Music
	music.openFromFile(RESOURCES + "sound/MenuMusic.ogg");
	music.play();

	return;
}

void deal_with_interactions() {
	if (Fireboy.getGlobalBounds().intersects(WaterLake.getGlobalBounds()))
	{
		Fireboy.setScale(0, 0);
	}
	if (Watergirl.getGlobalBounds().intersects(FireLake.getGlobalBounds()))
	{
		Watergirl.setScale(0, 0);
	}
	if (Fireboy.getGlobalBounds().intersects(Rope.getGlobalBounds()))
	{
		z = true;
	}
	if (Watergirl.getGlobalBounds().intersects(Rope.getGlobalBounds()) && z)
	{
		Watergirl.setScale(0, 0);
	}
}

/*This function draws all needed game stuff on game window (diamonds, characters, etc...*/
void draw_all(RenderWindow& window, Sprite red_diamonds[], Sprite blue_diamonds[]) {
	window.clear();
	// characters
	window.draw(Fireboy);
	window.draw(Watergirl);
	// Score
	window.draw(ScoreBoard);
	// environment
	window.draw(Rope);
	window.draw(Wire);
	window.draw(WaterLake);
	window.draw(FireLake);
	// Diamonds
	for (int i = 0; i < 4; ++i)
	{
		window.draw(red_diamonds[i]);
		window.draw(blue_diamonds[i]);
	}
	return;
}

void score(Sprite red_diamonds[], Sprite blue_diamonds[], int& Sc, Text& Scboard)
{
	//red daimonds
	for (int i = 0; i < 4; ++i)
	{
		if (Fireboy.getGlobalBounds().intersects(red_diamonds[i].getGlobalBounds()))
		{
			red_diamonds[i].setScale(0, 0);
			++Sc;
			Scboard.setString("Score: " + to_string(Sc));
		}
	}
	//blue daimonds
	for (int i = 0; i < 4; ++i)
	{
		if (Watergirl.getGlobalBounds().intersects(blue_diamonds[i].getGlobalBounds()))
		{
			blue_diamonds[i].setScale(0, 0);
			++Sc;
			Scboard.setString("Score: " + to_string(Sc));
		}
	}
}

int animate_func(RenderWindow &window, Sprite &FB, Sprite &WG)
{
	int row1_B = 10, row2_B = 20, StopRow_B = 10;
	double jumpV_B = 0; bool isgrounded_B = false;

	int row1_G = 22, row2_G = 5, StopRow_G = 20;
	double jumpV_G = 0; bool isgrounded_G = false;

	// for making rectangle for jumping on it

	RectangleShape rect(Vector2f(1500, 50));
	rect.setPosition(0, 700);

	

		/*
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		*/

		// fireboy controls :
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		{
			FB.move(10, 0);
			FB.setTextureRect(IntRect(row1_B, -22, 70, 100));
			row1_B += 80;
			row1_B %= 320;
		}


		else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			FB.move(-10, 0);
			FB.setTextureRect(IntRect(row2_B, 78, 70, 100));
			row2_B += 80;
			row2_B %= 320;
		}

		else
		{
			FB.setTextureRect(IntRect(StopRow_B, 400, 55, 100));
			StopRow_B += 80;
			StopRow_B %= 400;
		}

		// wategirl controls :

		if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			WG.move(-10, 0);
			WG.setTextureRect(IntRect(row1_G, 18, 90, 80));
			row1_G += 100;
			row1_G %= 400;
		}

		else if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			WG.move(10, 0);
			WG.setTextureRect(IntRect(row2_G, 118, 96, 80));
			row2_G += 100;
			row2_G %= 400;
		}
		else
		{
			WG.setTextureRect(IntRect(StopRow_G, 472, 56, 86));
			StopRow_G += 80;
			StopRow_G %= 320;
		}

		// fire boy jumping code

		if (rect.getGlobalBounds().intersects(FB.getGlobalBounds()))
		{
			isgrounded_B = true;
			jumpV_B = 0;

			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				jumpV_B = 20;
			}
		}
		else
		{
			isgrounded_B = false;
			jumpV_B -= 1.5;
		}

		// water girl jumping code 

		if (rect.getGlobalBounds().intersects(WG.getGlobalBounds()))
		{
			isgrounded_G = true;
			jumpV_G = 0;

			if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				jumpV_G = 20;
			}
		}
		else
		{
			isgrounded_G = false;
			jumpV_G -= 1.5;
		}
		FB.move(0, -jumpV_B);
		WG.move(0, -jumpV_G);
		//for execute
		/*
		window.clear();
		window.draw(rect);
		window.draw(FB);
		window.draw(WG);
		
		window.display();
		*/
	return 0;
}