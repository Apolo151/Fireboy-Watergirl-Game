#include "menu.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Menu::Menu(float width, float height) {
	font.loadFromFile("resources/fonts/Font1.ttf");
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color{ 250,200,80 });
	mainmenu[0].setString("PLAY");
	mainmenu[0].setCharacterSize(30);
	mainmenu[0].setPosition(Vector2f(width / 2.2, height / (4) + 130));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color{ 250,200,80 });
	mainmenu[1].setString("SETTINGS");
	mainmenu[1].setCharacterSize(30);
	mainmenu[1].setPosition(Vector2f(width / 2.45, height / 4 + 200));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color{ 250,200,80 });
	mainmenu[2].setString("QUIT");
	mainmenu[2].setCharacterSize(30);
	mainmenu[2].setPosition(Vector2f(width / 2.2, height / (4) + 270));

	selected = 0;
}
Menu::~Menu() {}
void Menu::setSelected(int n) {
	selected = n;
}
void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainmenu[i]);
	}


}
void Menu::MoveDown() {
	if (selected + 1 <= 3) {

		mainmenu[selected].setCharacterSize(30);
		selected++;
		if (selected == 3) {
			selected = 0;
		}

		mainmenu[selected].setCharacterSize(35);
	}
}
void Menu::MoveUp() {
	if (selected - 1 >= -1) {

		mainmenu[selected].setCharacterSize(30);
		selected--;
		if (selected == -1) {
			selected = 2;
		}

		mainmenu[selected].setCharacterSize(35);
	}
}

