#include "Menu1.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const string RESOURCES = "resources/";

Menu1::Menu1(float width, float height) {
	font1.loadFromFile(RESOURCES+"fonts/Font1.ttf");
	mainmenu1[0].setFont(font1);
	mainmenu1[0].setFillColor(Color{ 250,200,80 });
	mainmenu1[0].setString("Game audio");
	mainmenu1[0].setCharacterSize(70);
	mainmenu1[0].setPosition(Vector2f(width / 3.5 + 60, height /5 - 10));

	mainmenu1[1].setFont(font1);
	mainmenu1[1].setFillColor(Color{ 250,200,80 });
	mainmenu1[1].setString("On");
	mainmenu1[1].setCharacterSize(70);
	mainmenu1[1].setPosition(Vector2f(width / 2.24, height / 4 + 90));

	mainmenu1[2].setFont(font1);
	mainmenu1[2].setFillColor(Color{ 250,200,80 });
	mainmenu1[2].setString("Off");
	mainmenu1[2].setCharacterSize(70);
	mainmenu1[2].setPosition(Vector2f(width / 2.3, height / (4) + 230));

	selected1 = 0;
}
Menu1::~Menu1() {}
void Menu1::setSelected1(int n) {
	selected1= n;
}
void Menu1::draw1(RenderWindow& window) {
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainmenu1[i]);
	}


}
void Menu1::MoveDown1() {
	if (selected1 + 1 <= 3) {

		mainmenu1[selected1].setCharacterSize(70);
		mainmenu1[selected1].setFillColor(Color{ 250,200,80 });
		selected1++;
		if (selected1 == 3) {
			selected1 =1;
		}

		
		mainmenu1[selected1].setFillColor(Color{ 100,100,250 });
	}
}
void Menu1::MoveUp1() {
	if (selected1 - 1 >= -1) {

		mainmenu1[selected1].setCharacterSize(70);
		mainmenu1[selected1].setFillColor(Color{ 250,200,80 });
		selected1--;
		if (selected1 == 0) {
			selected1 = 2;
		}

		
		mainmenu1[selected1].setFillColor(Color{ 100,100,250 });
	}
}