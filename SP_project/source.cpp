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
void setup_background();
void check_background_collisions(RenderWindow& window);
int animate_func();

/* Declare global variables*/
Font ScoreFont;
Text ScoreBoard;
int Score = 0, waterdoor = 3, firedoor = 3;
Music music;
Sprite Fireboy, Watergirl, FireLake, WaterLake, Wire, Rope;// , red_diamonds[4], blue_diamonds[4];
Texture load_photo1, load_photo2, R_diamondTexture, B_diamondTexture, FireLakeTexture, WaterLakeTexture, WireTexture, RopeTexture;
Texture tg, tg2, tg3, tg4, wdoor, fdoor, tback, tbback;
Sprite swdoor, sfdoor, sback, sbback;
VertexArray f1(sf::TriangleStrip, 9), f2(sf::TriangleStrip, 8), f3(sf::TriangleStrip, 4),
g1(sf::TriangleStrip, 4), g2(sf::TriangleStrip, 4), g3(sf::TriangleStrip, 4), g4(sf::TriangleStrip, 4),
block1(sf::TriangleStrip, 5), block2(sf::TriangleStrip, 4), block3(sf::TriangleStrip, 8), block4(sf::TriangleStrip, 6),
block6(sf::TriangleStrip, 8);
//
pair<int, int> WINDOW_DIMENSIONS = { 1280, 900 };
///
int row1_B = 10, row2_B = 20, StopRow_B = 10;
double jumpV_B = 0; bool isgrounded_B = false;
int row1_G = 22, row2_G = 5, StopRow_G = 20;
double jumpV_G = 0; bool isgrounded_G = false;

// for making rectangle for jumping on it
sf::RectangleShape rec1(sf::Vector2f(300.f, 35.f)),
rect(Vector2f(1500, 50)),
f4(sf::Vector2f(845.f, 35.f)),
block5(sf::Vector2f(120.f, 105.f));

/*--------------------------*/

int main()
{
	//make a main menu window (old (950, 750))
	RenderWindow window(VideoMode(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second), "Fireboy & watergirl", Style::Default);
	Menu menu(window.getSize().x, window.getSize().y);
	//set background for main menu
	RectangleShape backg;
	backg.setSize(Vector2f(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second));
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
					int x = menu.pressed();
					// If Player Choose play
					if (x == 0)
					{
						Score = 0;
						// Create Game window
						RenderWindow PLAY(VideoMode(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second), "Game");
						PLAY.setFramerateLimit(30);
						/*--Setup stuff before going into game loop--*/
						Sprite red_diamonds[4], blue_diamonds[4];
						// setup score & diamonds & sound
						setup_score_and_sound(red_diamonds, blue_diamonds);
						// setup ENV
						setup_env_and_lakes();
						// Setup Characters texture
						create_characters();
						// Setup the background
						setup_background();
						/*-------------------------------------------*/
						while (PLAY.isOpen()) {
							// calcuate score
							score(red_diamonds, blue_diamonds, Score, ScoreBoard);
							// interactions with lakes, levers, buttons, etc...
							deal_with_interactions();
							// character movement and animations function
							animate_func();
							// check for colliding with the background
							check_background_collisions(PLAY);
							PLAY.clear();
							draw_all(PLAY, red_diamonds, blue_diamonds);
							//
							Fireboy.move(0, -jumpV_B);
							Watergirl.move(0, -jumpV_G);
							//
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
						RenderWindow SETTINGS(VideoMode(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second), "Settings");
						while (SETTINGS.isOpen())
						{
							Event aevent;
							while (SETTINGS.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									SETTINGS.close();
								}
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

/* Create the two characters */
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

/* Sets up background*/
void setup_background() {

	tg.loadFromFile(RESOURCES + "images/background1.png");
	tg.setRepeated(true);

	tg2.loadFromFile(RESOURCES + "images/background3.png");
	tg2.setRepeated(true);

	tg3.loadFromFile(RESOURCES + "images/bground1.png");
	tg4.loadFromFile(RESOURCES + "images/bground2.png");

	tbback.loadFromFile(RESOURCES + "images/bbackground.png");
	tbback.setRepeated(true);

	sbback.setTexture(tbback);
	sbback.setTextureRect({ 0, 0,1280, 900 });

	tback.loadFromFile(RESOURCES + "images/background2.png");
	tback.setRepeated(true);

	sback.setTexture(tback);
	sback.setTextureRect({ 0, 0,1280, 900 });
	/*-------------*/
	f1[0].position = sf::Vector2f(30.f, 605.f);
	f1[1].position = sf::Vector2f(30.f, 630.f);
	f1[2].position = sf::Vector2f(470.f, 605.f);
	f1[3].position = sf::Vector2f(420.f, 630.f);
	f1[4].position = sf::Vector2f(520.f, 680.f);
	f1[5].position = sf::Vector2f(470.f, 705.f);
	f1[6].position = sf::Vector2f(1020.f, 680.f);
	f1[7].position = sf::Vector2f(615.f, 705.f);
	f1[8].position = sf::Vector2f(1045.f, 705.f);

	f1[0].texCoords = sf::Vector2f(30.f, 605.f);
	f1[1].texCoords = sf::Vector2f(30.f, 630.f);
	f1[2].texCoords = sf::Vector2f(470.f, 605.f);
	f1[3].texCoords = sf::Vector2f(420.f, 630.f);
	f1[4].texCoords = sf::Vector2f(520.f, 680.f);
	f1[5].texCoords = sf::Vector2f(470.f, 705.f);
	f1[6].texCoords = sf::Vector2f(1020.f, 680.f);
	f1[7].texCoords = sf::Vector2f(615.f, 705.f);
	f1[8].texCoords = sf::Vector2f(1045.f, 705.f);


	f2[0].position = sf::Vector2f(175.f, 490.f);
	f2[1].position = sf::Vector2f(175.f, 520.f);
	f2[2].position = sf::Vector2f(580.f, 490.f);
	f2[3].position = sf::Vector2f(530.f, 520.f);
	f2[4].position = sf::Vector2f(600.f, 520.f);
	f2[5].position = sf::Vector2f(550.f, 550.f);
	f2[6].position = sf::Vector2f(1280.f, 520.f);
	f2[7].position = sf::Vector2f(1280.f, 550.f);

	f2[0].texCoords = sf::Vector2f(175.f, 490.f);
	f2[1].texCoords = sf::Vector2f(175.f, 520.f);
	f2[2].texCoords = sf::Vector2f(580.f, 490.f);
	f2[3].texCoords = sf::Vector2f(530.f, 520.f);
	f2[4].texCoords = sf::Vector2f(600.f, 520.f);
	f2[5].texCoords = sf::Vector2f(550.f, 550.f);
	f2[6].texCoords = sf::Vector2f(1280.f, 520.f);
	f2[7].texCoords = sf::Vector2f(1280.f, 550.f);


	f3[0].position = sf::Vector2f(29.f, 225.f);
	f3[1].position = sf::Vector2f(29.f, 380.f);
	f3[2].position = sf::Vector2f(160.f, 225.f);
	f3[3].position = sf::Vector2f(160.f, 380.f);

	f3[0].texCoords = sf::Vector2f(29.f, 225.f);
	f3[1].texCoords = sf::Vector2f(29.f, 380.f);
	f3[2].texCoords = sf::Vector2f(160.f, 225.f);
	f3[3].texCoords = sf::Vector2f(160.f, 380.f);



	f4.setPosition(435, 180);
	f4.setTexture(&tg3);


	g1[0].position = sf::Vector2f(0.f, 0.f);
	g1[1].position = sf::Vector2f(0.f, 900.f);
	g1[2].position = sf::Vector2f(30.f, 0.f);
	g1[3].position = sf::Vector2f(30.f, 900.f);

	g1[0].texCoords = sf::Vector2f(0.f, 0.f);
	g1[1].texCoords = sf::Vector2f(0.f, 900.f);
	g1[2].texCoords = sf::Vector2f(30.f, 0.f);
	g1[3].texCoords = sf::Vector2f(30.f, 900.f);


	g2[0].position = sf::Vector2f(0.f, 870.f);
	g2[1].position = sf::Vector2f(0.f, 900.f);
	g2[2].position = sf::Vector2f(1280.f, 870.f);
	g2[3].position = sf::Vector2f(1280.f, 900.f);

	g2[0].texCoords = sf::Vector2f(0.f, 870.f);
	g2[1].texCoords = sf::Vector2f(0.f, 900.f);
	g2[2].texCoords = sf::Vector2f(1280.f, 870.f);
	g2[3].texCoords = sf::Vector2f(1280.f, 900.f);


	g3[0].position = sf::Vector2f(1250.f, 0.f);
	g3[1].position = sf::Vector2f(1250.f, 900.f);
	g3[2].position = sf::Vector2f(1280.f, 0.f);
	g3[3].position = sf::Vector2f(1280.f, 900.f);

	g3[0].texCoords = sf::Vector2f(1250.f, 0.f);
	g3[1].texCoords = sf::Vector2f(1250.f, 900.f);
	g3[2].texCoords = sf::Vector2f(1280.f, 0.f);
	g3[3].texCoords = sf::Vector2f(1280.f, 900.f);


	g4[0].position = sf::Vector2f(0.f, 0.f);
	g4[1].position = sf::Vector2f(0.f, 30.f);
	g4[2].position = sf::Vector2f(1280.f, 0.f);
	g4[3].position = sf::Vector2f(1280.f, 30.f);

	g4[0].texCoords = sf::Vector2f(0.f, 0.f);
	g4[1].texCoords = sf::Vector2f(0.f, 30.f);
	g4[2].texCoords = sf::Vector2f(1280.f, 0.f);
	g4[3].texCoords = sf::Vector2f(1280.f, 30.f);


	block1[0].position = sf::Vector2f(1150.f, 750.f);
	block1[1].position = sf::Vector2f(1115.f, 795.f);
	block1[2].position = sf::Vector2f(1280.f, 750.f);
	block1[3].position = sf::Vector2f(1115.f, 900.f);
	block1[4].position = sf::Vector2f(1280.f, 900.f);

	block1[0].texCoords = sf::Vector2f(1150.f, 750.f);
	block1[1].texCoords = sf::Vector2f(1115.f, 795.f);
	block1[2].texCoords = sf::Vector2f(1280.f, 750.f);
	block1[3].texCoords = sf::Vector2f(1115.f, 900.f);
	block1[4].texCoords = sf::Vector2f(1280.f, 900.f);

	block2[0].position = sf::Vector2f(155.f, 345.f);
	block2[1].position = sf::Vector2f(155.f, 380.f);
	block2[2].position = sf::Vector2f(520.f, 345.f);
	block2[3].position = sf::Vector2f(520.f, 380.f);

	block2[0].texCoords = sf::Vector2f(155.f, 345.f);
	block2[1].texCoords = sf::Vector2f(155.f, 380.f);
	block2[2].texCoords = sf::Vector2f(520.f, 345.f);
	block2[3].texCoords = sf::Vector2f(520.f, 380.f);


	block3[0].position = sf::Vector2f(515.f, 270.f);
	block3[1].position = sf::Vector2f(515.f, 380.f);
	block3[2].position = sf::Vector2f(705.f, 270.f);
	block3[3].position = sf::Vector2f(850.f, 380.f);
	block3[4].position = sf::Vector2f(850.f, 345.f);
	block3[5].position = sf::Vector2f(900.f, 400.f);
	block3[6].position = sf::Vector2f(1100.f, 345.f);
	block3[7].position = sf::Vector2f(1100.f, 400.f);

	block3[0].texCoords = sf::Vector2f(515.f, 270.f);
	block3[1].texCoords = sf::Vector2f(515.f, 380.f);
	block3[2].texCoords = sf::Vector2f(705.f, 270.f);
	block3[3].texCoords = sf::Vector2f(850.f, 380.f);
	block3[4].texCoords = sf::Vector2f(850.f, 345.f);
	block3[5].texCoords = sf::Vector2f(900.f, 400.f);
	block3[6].texCoords = sf::Vector2f(1100.f, 345.f);
	block3[7].texCoords = sf::Vector2f(1100.f, 400.f);

	block4[0].position = sf::Vector2f(1000.f, 550.f);
	block4[1].position = sf::Vector2f(1020.f, 580.f);
	block4[2].position = sf::Vector2f(1280.f, 550.f);
	block4[3].position = sf::Vector2f(1115.f, 580.f);
	block4[4].position = sf::Vector2f(1280.f, 630.f);
	block4[5].position = sf::Vector2f(1150.f, 630.f);

	block4[0].texCoords = sf::Vector2f(1000.f, 550.f);
	block4[1].texCoords = sf::Vector2f(1020.f, 580.f);
	block4[2].texCoords = sf::Vector2f(1280.f, 550.f);
	block4[3].texCoords = sf::Vector2f(1115.f, 580.f);
	block4[4].texCoords = sf::Vector2f(1280.f, 630.f);
	block4[5].texCoords = sf::Vector2f(1150.f, 630.f);

	block5.setPosition(315, 180);
	block5.setTexture(&tg4);

	block6[0].position = sf::Vector2f(260.f, 120.f);
	block6[1].position = sf::Vector2f(240.f, 150.f);
	block6[2].position = sf::Vector2f(340.f, 120.f);
	block6[3].position = sf::Vector2f(300.f, 150.f);
	block6[4].position = sf::Vector2f(365.f, 150.f);
	block6[5].position = sf::Vector2f(315.f, 180.f);
	block6[6].position = sf::Vector2f(395.f, 150.f);
	block6[7].position = sf::Vector2f(410.f, 180.f);

	block6[0].texCoords = sf::Vector2f(260.f, 120.f);
	block6[1].texCoords = sf::Vector2f(240.f, 150.f);
	block6[2].texCoords = sf::Vector2f(340.f, 120.f);
	block6[3].texCoords = sf::Vector2f(300.f, 150.f);
	block6[4].texCoords = sf::Vector2f(365.f, 150.f);
	block6[5].texCoords = sf::Vector2f(315.f, 180.f);
	block6[6].texCoords = sf::Vector2f(395.f, 150.f);
	block6[7].texCoords = sf::Vector2f(410.f, 180.f);

	rec1.setPosition(30, 740);
	rec1.setTexture(&tg2);

	/* Doors */
	// Water door
	wdoor.loadFromFile(RESOURCES + "images/water_door1.PNG");
	swdoor.setTexture(wdoor);
	swdoor.setTextureRect(IntRect(waterdoor, 1, 110, 125));
	swdoor.setPosition(1050, 90);
	swdoor.scale(0.75, 0.75);
	// Fire door
	fdoor.loadFromFile(RESOURCES + "images/fire_door1.PNG");
	sfdoor.setTexture(fdoor);
	sfdoor.setTextureRect(IntRect(firedoor, 1, 110, 125));
	sfdoor.setPosition(1150, 90);
	sfdoor.scale(0.75, 0.75);

	return;
}

/* Handles background collisions */
void check_background_collisions(RenderWindow& window) {

	return;
}

/* Sets up lakes */
void setup_env_and_lakes(){
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

/* Sets up the score and sound of the game*/
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
	//music.play();

	return;
}

/*TODO*/
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
	// background
	window.draw(sbback);
	window.draw(sback);
	window.draw(f1, &tg);
	window.draw(f2, &tg);
	window.draw(f3, &tg);
	window.draw(f4);
	window.draw(rec1);
	window.draw(g1, &tg);
	window.draw(g2, &tg);
	window.draw(g3, &tg);
	window.draw(g4, &tg);
	window.draw(block1, &tg);
	window.draw(block2, &tg);
	window.draw(block3, &tg);
	window.draw(block4, &tg);
	window.draw(block5);
	window.draw(block6, &tg);
	window.draw(sfdoor);
	window.draw(swdoor);
	
	// characters
	//window.draw(rect);
	window.draw(Fireboy);
	window.draw(Watergirl);
	// Score
	window.draw(ScoreBoard);
	// environment
	window.draw(Rope);
	window.draw(Wire);
	window.draw(WaterLake);
	window.draw(FireLake);
	// diamonds
	for (int i = 0; i < 4; ++i)
	{
		window.draw(red_diamonds[i]);
		window.draw(blue_diamonds[i]);
	}
	return;
}

/*Calculates the current score */
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

/*Handles the movement and animation of the characters*/
int animate_func()
{
	// for making rectangle for jumping on it
	rect.setPosition(0, 700);

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
	return 0;
}

