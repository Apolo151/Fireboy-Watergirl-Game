#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Menu1
{
public:
	Text mainmenu1[3];
	Menu1(float width, float height);
	void draw1(RenderWindow& window);
	void MoveUp1();
	void MoveDown1();
	void setSelected1(int n);
	int pressed1() {
		return selected1;
	}
	~Menu1();
private:
	int selected1;
	Font font1;

};

