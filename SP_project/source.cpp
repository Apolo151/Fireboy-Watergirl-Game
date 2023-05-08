#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include<string>
#include"Menu.h"
#include "Menu1.h"
#include "structs.cpp"

using namespace std;
using namespace sf;

//const string RESOURCES = "resources/";
bool z = false; int e1 = 0;
/* Write functions declarations */
void draw_all(RenderWindow& window, Sprite red_diamonds[], Sprite blue_diamonds[]);
// Score
void score(Sprite Red[], Sprite Blue[], int& Sc, Text& Scboard);
void setup_score_and_sound(Sprite red_diamonds[], Sprite blue_diamonds[] /*Text& ScoreBoard,*/);
void game_win_end();
// Env
void setup_env_and_lakes();
void deal_with_interactions();

// Background
void setup_blocks(Sprite blocks[]);
void setup_background();
void check_background_collisions(RenderWindow& window);
template <typename T>
void handle_character_collisions(T block, Player &Character);
// Character & Animation
int animate_func();
void animate2(float delta_time);
void create_characters();

/* Declare global variables*/

// Score
Font ScoreFont;
Text ScoreBoard;
Text ScoreSheet;
int Score = 0, waterdoor = 3, firedoor = 3;
int HighestScore=0;
//
Texture GameEndWindow_Texture;	//Texture when game end
Sprite GameEndWindow;	//sprite for game end
String GameState = "running";	//State variable to check if game ended or not ("win", "lose", "running")
fstream Highest;	//file for save the highest score
// Music
Music music;
bool MusicOn = true;

// Background
Texture tg1, tg2, wdoor, fdoor, tback;
Sprite swdoor, sfdoor, sback;
sf::RectangleShape g1(sf::Vector2f(35.f, 1280.f)), g2(sf::Vector2f(1280.f, 35.f)),
g3(sf::Vector2f(35.f, 1280.f)), g4(sf::Vector2f(1280.f, 35.f));
Sprite blocks[11];
Texture Tb1, Tb2, Tb3, Tb4, Tb5;
// Env
Texture load_photo1, load_photo2, R_diamondTexture, B_diamondTexture, FireLakeTexture,
WaterLakeTexture, WireTexture, RopeTexture, txg, t2, tx2;
Sprite LeverBase, LeverArm;
//Sprite Fireboy, Watergirl;
Sprite FireLake, WaterLake, GreenLake, Wire, Rope;// , red_diamonds[4], blue_diamonds[4];

pair<int, int> WINDOW_DIMENSIONS = { 1280, 900 };
/* Character Animation Sprite Sheet Cutting numbers*/
int row1_B = 10, row2_B = 20, StopRow_B = 10;
double jumpV_B = 0; bool isgrounded_B = false;
int row1_G = 22, row2_G = 5, StopRow_G = 20;
double jumpV_G = 0; bool isgrounded_G = false;

bool FB_onground = false;
bool WG_onground = false;

/* Levers, Buttons, etc.. Sprite sheet cutting numbers */

int Lever_row = 0, Button1_row, Button2_row;

// for making rectangle for jumping on it
sf::RectangleShape rec1(sf::Vector2f(300.f, 35.f)),
rect(Vector2f(1500, 50)),
f4(sf::Vector2f(845.f, 35.f)),
block5(sf::Vector2f(120.f, 105.f));

// Game Objects
Lever lever(false);
Elevator elevators[] = {Elevator(300, 500)};
Button buttons[] = { Button(382, 470, &elevators[0]), Button(950, 328, &elevators[0]) };
Box box1;
const float SPEED = 200;
float delta_time;
Player Fireboy("sprites/fireboy_sprite.png", SPEED), Watergirl("sprites/watergirl_sprite.png", SPEED);

/*--------------------------*/

/* General Functions */
int main()
{
	//make a main menu window (old (950, 750))
	RenderWindow window(VideoMode(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second), "Fireboy & watergirl", Style::Default);
	Menu menu(window.getSize().x, window.getSize().y);

	//set background for main menu
	RectangleShape backg;
	backg.setSize(Vector2f(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second));
	Texture Maintexture;
	Maintexture.loadFromFile(RESOURCES + "images/bgr.jpg");
	backg.setTexture(&Maintexture);
	//setting background for settings
	RectangleShape sbackg;
	sbackg.setSize(Vector2f(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second));
	Texture sMaintexture;
	sMaintexture.loadFromFile(RESOURCES + "images/tem.jpg");
	sbackg.setTexture(&sMaintexture);
	//
	//Taking the value of highest score at the bigening of the game
	Highest.open("ScoreSheet.txt", ios::in | ios::out);
	Highest >> HighestScore;
	Highest.close();

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
					sf::Clock clock;
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
						// check if game ended or not
						game_win_end();
						/*-------------------------------------------*/
						while (PLAY.isOpen()) {
							delta_time = clock.restart().asSeconds();
							//
							if (Keyboard::isKeyPressed(Keyboard::Key::F))
							{
								GameState = "win";
							}
							// calcuate score
							score(red_diamonds, blue_diamonds, Score, ScoreBoard);
							// interactions with lakes, levers, buttons, etc...
							deal_with_interactions();
							// character movement and animations function
							//animate_func();
							animate2(delta_time);
							PLAY.clear();
							draw_all(PLAY, red_diamonds, blue_diamonds);
							//
							//Fireboy.move(0, -jumpV_B);
							//Watergirl.move(0, -jumpV_G);
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
										GameState = "lose";
										PLAY.close();
									}
								}
							}
						}
					}
					if (x == 1)
					{
						RenderWindow SETTINGS(VideoMode(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second), "Settings");
						Menu1 menu1(WINDOW_DIMENSIONS.first, WINDOW_DIMENSIONS.second);
						while (SETTINGS.isOpen())
						{
							Event aevent;
							while (SETTINGS.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									SETTINGS.close();
								}
								else if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										SETTINGS.close();
									}
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Up)
									{
										menu1.MoveUp1();

									}
									if (aevent.key.code == Keyboard::Down)
									{
										menu1.MoveDown1();

									}

									if (aevent.key.code == Keyboard::Enter)
									{
										int x1 = menu1.pressed1();
										if (x1 == 1)
										{
											MusicOn = true;
											SETTINGS.close();
										}
										if (x1 == 2)
										{
											MusicOn = false;
											SETTINGS.close();
										}
									}
								}
							}
							SETTINGS.clear();
							SETTINGS.draw(sbackg);
							menu1.draw1(SETTINGS);
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
// This function draws all needed game stuff on game window (diamonds, characters, etc...
void draw_all(RenderWindow& window, Sprite red_diamonds[], Sprite blue_diamonds[]) {
	/* Background */
	window.draw(sback);
	/* Map */
	// background
	window.clear();
	window.draw(sback);
	window.draw(g1);
	window.draw(g2);
	window.draw(g3);
	window.draw(g4);
	// Buttons
	for (Button button : buttons) {
		window.draw(button.button);
	}
	for (int i = 0; i < 11; i++)
	{
		window.draw(blocks[i]);
	}
	// Doors
	window.draw(sfdoor);
	window.draw(swdoor);
	// Levers & Elevators & boxes
	//window.draw(lever.Arm);
	//window.draw(lever.Base);
	window.draw(elevators[0].elevator);
	//window.draw(box1.box);
	// characters
	//window.draw(rect);
	window.draw(Fireboy.sprite);
	window.draw(Watergirl.sprite);
	// Score
	window.draw(ScoreBoard);
	// environment
	//window.draw(Rope);
	//window.draw(Wire);
	window.draw(WaterLake);
	window.draw(FireLake);
	// diamonds
	for (int i = 0; i < 4; ++i)
	{
		window.draw(red_diamonds[i]);
		window.draw(blue_diamonds[i]);
	}
	// Score
	//ScoreSheet
	if (GameState == "win") {
		window.draw(GameEndWindow);
		window.draw(ScoreSheet);
	}

	return;
}

/* Background & ENV*/

//Sets up background
void setup_background() {
	tback.loadFromFile(RESOURCES+"images/background2.png");
	tback.setRepeated(true);

	sback.setTexture(tback);
	sback.setTextureRect({ 0, 0,1280, 900 });
	// framebackground
	tg1.loadFromFile(RESOURCES + "images/bground1.png");
	tg1.setRepeated(true);
;
	tg2.loadFromFile(RESOURCES + "images/bground2.png");
	tg2.setRepeated(true);
	/*--------------------*/
	g1.setPosition(0, 0);
	g1.setTexture(&tg2);

	g2.setPosition(0, 865);
	g2.setTexture(&tg1);

	g3.setPosition(1245, 0);
	g3.setTexture(&tg2);

	g4.setPosition(0, 0);
	g4.setTexture(&tg1);
	// Textures
	Tb1.loadFromFile(RESOURCES + "images/Tb1.png");
	Tb1.setRepeated(true);

	Tb2.loadFromFile(RESOURCES + "images/Tb2.png");
	Tb2.setRepeated(true);

	Tb3.loadFromFile(RESOURCES + "images/Tb3.png");
	Tb3.setRepeated(true);

	Tb4.loadFromFile(RESOURCES + "images/Tb4.png");
	Tb4.setRepeated(true);

	Tb5.loadFromFile(RESOURCES + "images/Tb5.png");
	Tb5.setRepeated(true);
	//
	setup_blocks(blocks);
	for (int i = 0; i < 11; i++)
	{
		if (i == 0 || i == 1) {
			blocks[i].setTexture(Tb1);
		}
		else if (i == 2 || i == 3 || i == 4 || i == 5)
			blocks[i].setTexture(Tb2);

		else if (i == 6 || i == 7 || i == 8)
			blocks[i].setTexture(Tb3);

		else if (i == 9)
			blocks[i].setTexture(Tb4);
		else if (i == 10)
			blocks[i].setTexture(Tb5);
	}
	/*-------------*/
	/* Doors */
	// Water door
	wdoor.loadFromFile(RESOURCES + "images/water door1.PNG");
	swdoor.setTexture(wdoor);
	swdoor.setTextureRect(IntRect(waterdoor, 1, 110, 125));
	swdoor.setPosition(1050, 50);
	swdoor.scale(0.75, 0.75);
	// Fire door
	fdoor.loadFromFile(RESOURCES + "images/fire door1.PNG");
	sfdoor.setTexture(fdoor);
	sfdoor.setTextureRect(IntRect(firedoor, 1, 110, 125));
	sfdoor.setPosition(1150, 50);
	sfdoor.scale(0.75, 0.75);

	return;
}
// Sets blocks for background
void setup_blocks(Sprite blocks[]) {
	//1
	blocks[0].setPosition(35, 605);
	blocks[0].setScale(1, 1);

	blocks[1].setPosition(760, 520);
	blocks[1].setScale(1, 1);
	//2

	blocks[3].setPosition(490, 640);
	blocks[3].setScale(1, 1);

	blocks[4].setPosition(175, 490);
	blocks[4].setScale(1, 1);

	blocks[5].setPosition(165, 345);
	blocks[5].setScale(1, 1);

	blocks[2].setPosition(504, 140);
	blocks[2].setScale(1.5, 1);
	//3
	blocks[6].setPosition(1115, 753);
	blocks[6].setScale(1.25, 0.75);

	blocks[7].setPosition(35, 230);
	blocks[7].setScale(1, 1);

	blocks[8].setPosition(667, 250);
	blocks[8].setScale(1.25, 0.75);
	//4
	blocks[9].setPosition(35, 740);
	blocks[9].setScale(1, 1);
	//5
	blocks[10].setPosition(825, 345);
	blocks[10].setScale(0.8, 1);

}

// Handles background collisions 
void check_background_collisions(RenderWindow& window) {

	return;
}
// Sets up lakes
void setup_env_and_lakes(){
	// FireLake
	/*FireLakeTexture.loadFromFile(RESOURCES + "images/flake.png");
	FireLake.setTexture(FireLakeTexture);
	FireLake.setPosition(550, 860);
	FireLake.setScale(0.2, 0.4);*/
	tx2.loadFromFile(RESOURCES + "images/lakef3.png");
	FireLake.setTexture(tx2);
	FireLake.setTextureRect(IntRect(52.46, 0, 52.46, 68));
	FireLake.setPosition(400, 675);
	FireLake.setScale(1, 1);

	//  WaterLake
	/*WaterLakeTexture.loadFromFile(RESOURCES + "images/wlake.png");
	WaterLake.setTexture(WaterLakeTexture);
	WaterLake.setPosition(750, 860);
	WaterLake.setScale(0.2, 0.4);*/

	t2.loadFromFile(RESOURCES + "images/w12.png");
	WaterLake.setTexture(t2);
	WaterLake.setPosition(750, 677);
	WaterLake.setTextureRect(IntRect(0, 0, 156.67, 28));
	WaterLake.setScale(1, 1);

	txg.loadFromFile("glake.png");
	GreenLake.setTexture(txg);
	GreenLake.setTextureRect(IntRect(0, 0, 166, 71));
	GreenLake.setPosition(750, 488);
	GreenLake.setScale(1, 1);

	/* Elevators */
	elevators[0].set_pos(1030, 400, 1000, 200);
	elevators[0].setScale(1.6, 1.4);
	/* Buttons */

	/* Boxes*/
	//box1.set_pos(606, 220);
}

/* Collisions */

// TO BE FINISHED
void deal_with_interactions() {
	/* Get current objects bounds */
	FloatRect fireboy_bounds = Fireboy.getGlobalBounds();
	FloatRect watergirl_bounds = Watergirl.getGlobalBounds();
	/*---------------------------*/
	/*// Back ground*/
	for (int i = 0; i < 11; ++i) {
		handle_character_collisions(blocks[i], Fireboy);
		handle_character_collisions(blocks[i], Watergirl);
	}
	//
	handle_character_collisions(g1, Fireboy);
	handle_character_collisions(g2, Fireboy);
	handle_character_collisions(g3, Fireboy);
	handle_character_collisions(g4, Fireboy);
	//
	handle_character_collisions(g1, Watergirl);
	handle_character_collisions(g2, Watergirl);
	handle_character_collisions(g3, Watergirl);
	handle_character_collisions(g4, Watergirl);

	/* Lakes interactions */
	// Fireboy
	if (fireboy_bounds.intersects(WaterLake.getGlobalBounds()))
	{
		Fireboy.setScale(0, 0);
		GameState = "lose";
	}
	// Water girl
	if (Watergirl.getGlobalBounds().intersects(FireLake.getGlobalBounds()))
	{
		Watergirl.setScale(0, 0);
		GameState = "lose";
	}

	/* Elevators interactions */
	for (Elevator elev : elevators) {
		handle_character_collisions(elev, Fireboy);
		handle_character_collisions(elev, Watergirl);
	}

	/* Buttons interactions */
	// Collisions
	for (Button &button : buttons) {
		FloatRect intersection;
		if (fireboy_bounds.intersects(button.button.getGlobalBounds(), intersection) ||
			watergirl_bounds.intersects(button.button.getGlobalBounds(), intersection)) {
			if (intersection.width > intersection.height) {
				button.isOn = true;
			}
			else button.isOn = false;
		}
		else button.isOn = false;
	}

	// Working
	for (Button &button : buttons) {
		if (button.isOn)
		{	
			button.move_elev_down();
		}
		else{
			button.move_elev_up();
		}
	}
	//
	
	z++;
	e1++;
	e1 %= 3;
	z %= 5;
}

// Handles background collisions
template <typename T>
void handle_character_collisions(T block, Player &Character) {
	// Get character & block bounds
	FloatRect char_bounds = Character.getGlobalBounds();
	FloatRect block_bounds = block.getGlobalBounds();
	// Cases: Above / Under / To the left of / to the right of

	// Determine the overlap between the character and the block
	if(char_bounds.intersects(block_bounds)){
		// Determine the overlap between the character and the rectangle
		sf::FloatRect overlap;
		if (char_bounds.top < block_bounds.top)
		{
			overlap.top = char_bounds.top + char_bounds.height - block_bounds.top;
		}
		else
		{
			overlap.top = block_bounds.top + block_bounds.height - char_bounds.top;
		}
		if (char_bounds.left < block_bounds.left)
		{
			overlap.left = char_bounds.left + char_bounds.width - block_bounds.left;
		}
		else
		{
			overlap.left = block_bounds.left + block_bounds.width - char_bounds.left;
		}

		// Resolve the collision based on the overlap direction
		if (overlap.width < overlap.height)
		{
			if (char_bounds.left < block_bounds.left)
			{
				//Fireboy.move(-overlap.width, 0.0f);
				//Fireboy.velocity.x = 0.0f;
				//Character.velocity.x = -overlap.width;
				Character.velocity.x = -10;
				//Fireboy.velocity.y += 981.0f * delta_time;
			}
			else
			{
				//Fireboy.move(overlap.width, 0.0f);
				//Fireboy.velocity.x = 0.0f;
				//Character.velocity.x = overlap.width;
				Character.velocity.x = 10;
				//Fireboy.velocity.y += 981.0f * delta_time;
			}
		}
		else
		{	// from top of block
			if (char_bounds.top + (char_bounds.height * 0.1)  < block_bounds.top)
			{
				//Fireboy.move(0.0f, -overlap.height);
				Character.CanJump = true;
				//Fireboy.velocity.y+= -overlap.height;
				Character.velocity.y = 0;
				//Fireboy.velocity.y += 981.0f * delta_time;
			}
			// from bottom
			else
			{
				//Fireboy.move(0.0f, overlap.height);
				Character.velocity.y = overlap.height;
				Character.velocity.y += 981.0f*0.6 * delta_time;
			}
		}
	}
}

/* Score */

// Sets up the score and sound of the game
void setup_score_and_sound(Sprite red_diamonds[], Sprite blue_diamonds[] /*Text& ScoreBoard,*/)
{
	// Texture of diamonds
	R_diamondTexture.loadFromFile(RESOURCES + "images/CharAssets.png");
	B_diamondTexture.loadFromFile(RESOURCES + "images/CharAssets.png");

	for (int i = 0; i < 4; ++i)
	{
		red_diamonds[i].setTexture(R_diamondTexture);
		red_diamonds[i].setScale(1, 1);
		red_diamonds[i].setPosition(500 - (110 * i), 710 - (i * 170));
		red_diamonds[i].setTextureRect(IntRect(136 * 8, 136 * 10, 136, 136));
	}

	for (int i = 0; i < 4; ++i)
	{
		blue_diamonds[i].setTexture(B_diamondTexture);
		blue_diamonds[i].setScale(1, 1);
		blue_diamonds[i].setPosition(1000 - (70 * i), 750 - (i * 170));
		blue_diamonds[i].setTextureRect(IntRect(136 * 7, 136 * 10, 136, 136));
	}

	//Score
	ScoreFont.loadFromFile(RESOURCES + "fonts/TrajanPro-Bold.otf");
	ScoreBoard.setFont(ScoreFont);
	ScoreBoard.setString("Score: " + to_string(Score));
	ScoreBoard.setFillColor(Color(220, 220, 50, 255));
	ScoreBoard.setPosition(30, 30);
	ScoreBoard.setCharacterSize(35);
	ScoreBoard.Bold;

	//Music
	music.openFromFile(RESOURCES + "sound/MenuMusic.ogg");
	if(MusicOn) music.play();

	return;
}
/* Calculates the current score */
void score(Sprite red_diamonds[], Sprite blue_diamonds[], int& Sc, Text& Scboard)
{
	//red diamonds
	for (int i = 0; i < 4; ++i)
	{
		if (Fireboy.getGlobalBounds().intersects(red_diamonds[i].getGlobalBounds()))
		{
			red_diamonds[i].setScale(0, 0);
			++Sc;
			Scboard.setString("Score: " + to_string(Sc));
			ScoreSheet.setString("       \tYOU WIN!   \t\n\nYour Score:\t\t\t     " + to_string(Score) + "\n\n" + "The highest score:\t" + to_string(HighestScore));
		}
	}
	//blue diamonds
	for (int i = 0; i < 4; ++i)
	{
		if (Watergirl.getGlobalBounds().intersects(blue_diamonds[i].getGlobalBounds()))
		{
			blue_diamonds[i].setScale(0, 0);
			++Sc;
			Scboard.setString("Score: " + to_string(Sc));
			ScoreSheet.setString("       \tYOU WIN!   \t\n\nYour Score:\t\t\t     " + to_string(Score) + "\n\n" + "The highest score:\t" + to_string(HighestScore));
		}
	}
	//
	if (GameState == "win")
	{
		if (Sc > HighestScore)
		{
			HighestScore = Sc;
			Highest.open("ScoreSheet.txt", ios::in | ios::out);
			Highest << HighestScore;
			Highest.close();
		}
	}
}
/* Show the scoresheet after reaching the gates*/
void game_win_end()
{
	GameEndWindow_Texture.loadFromFile("resources/images/PopupAssets.png");

	GameEndWindow.setTexture(GameEndWindow_Texture);
	GameEndWindow.setScale(0.75, 0.75);
	GameEndWindow.setPosition(260, 180);
	GameEndWindow.setTextureRect(IntRect(0, 225, 1060, 409 * 1.45));

	ScoreSheet.setFont(ScoreFont);
	ScoreSheet.setString("       \tYOU WIN!   \t\n\nYour Score:\t\t\t     " + to_string(Score) + "\n\n" + "The highest score:\t" + to_string(HighestScore));
	ScoreSheet.setFillColor(Color(220, 220, 50, 255));
	ScoreSheet.setPosition(420, 280);
	ScoreSheet.setCharacterSize(35);
	ScoreSheet.Bold;
}

/* Characters */

// Create the two characters 
void create_characters() {
	// for charachter fireboy
	Fireboy.setTextureRect(IntRect(467, 277, 55, 100));
	Fireboy.setPosition(100, 630);
	// for charachter watergirl
	Watergirl.setTextureRect(IntRect(340, 472, 56, 86));
	//(150, 100)
	Watergirl.setPosition(200, 630);
	//
	return;
}
// Handles the movement and animation of the characters
int animate_func()
{
	// for making rectangle for jumping on it
	//rect.setPosition(0, 750);

	// fireboy controls :
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) && Fireboy.getPosition().x < 1245)
	{
		Fireboy.move(10, 0);
		Fireboy.setTextureRect(IntRect(row1_B, -22, 70, 100));
		row1_B += 80;
		row1_B %= 320;
	}


	else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && Fireboy.getPosition().x > 35)
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
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && Watergirl.getPosition().x > 35)
	{
		Watergirl.move(-10, 0);
		Watergirl.setTextureRect(IntRect(row1_G, 18, 90, 80));
		row1_G += 100;
		row1_G %= 400;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::D) && Watergirl.getPosition().x < 1245)
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
		isgrounded_G = true;
		jumpV_G -= 1.5;
	}
	return 0;
}
// 
void animate2(float delta_time) {
	// reset velocity at start of each frame
	Fireboy.velocity.x = 0.0f;
	Watergirl.velocity.x = 0.0f;

	// Fireboy control & animation
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && Fireboy.CanJump){
		Fireboy.CanJump = false;
		Fireboy.jump();
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		// (row1_B, -22, 70, 100)
		Fireboy.setTextureRect(IntRect(row1_B, -5, 70, 85));
		row1_B += 80;
		row1_B %= 320;
		// if in window bounds
		if (Fireboy.getPosition().x < 1175) {
			Fireboy.moveRight(delta_time);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		// (row2_B, 78, 70, 100)
		Fireboy.setTextureRect(IntRect(row2_B, 95, 70, 85));
		row2_B += 80;
		row2_B %= 320;
		if (Fireboy.getPosition().x > 42) {
			Fireboy.moveLeft(delta_time);
		}
	}
	else {
		// (StopRow_B, 400, 55, 100)
		Fireboy.setTextureRect(IntRect(StopRow_B, 415, 55, 85));
		StopRow_B += 80;
		StopRow_B %= 400;
	}

	// Watergirl control & animation
	if (Keyboard::isKeyPressed(Keyboard::Key::W) && Watergirl.CanJump) {
		Watergirl.CanJump = false;
		Watergirl.jump();
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		Watergirl.setTextureRect(IntRect(row1_G, 18, 90, 80));
		row1_G += 100;
		row1_G %= 400;
		if (Watergirl.getPosition().x > 35) {
			Watergirl.moveLeft(delta_time);
		}
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		Watergirl.setTextureRect(IntRect(row2_G, 118, 96, 80));
		row2_G += 100;
		row2_G %= 400;
		if (Watergirl.getPosition().x < 1175) {
			Watergirl.moveRight(delta_time);
		}
	}
	else
	{
		Watergirl.setTextureRect(IntRect(StopRow_G, 472, 56, 86));
		StopRow_G += 80;
		StopRow_G %= 320;
	}
	//
	Fireboy.update(delta_time);
	Watergirl.update(delta_time);
}
