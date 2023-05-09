#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;

const string RESOURCES = "resources/";
static int ground = 865;

struct Player {
	sf::Sprite sprite;
	sf::Vector2f velocity;
	sf::Texture characterT;
	float speed; // speed of moving right or left
	bool CanJump = true;
	float jump_height = 170;

	Player(string TextureFile, float speed) {
		characterT.loadFromFile(RESOURCES + TextureFile);
		sprite.setTexture(characterT);
		sprite.setScale(0.85, 0.85);
		this->speed = speed;
	}

	void jump() {
		velocity.y = -sqrtf(2.0f * jump_height * 981.0f*0.5);
		//OR just : velocity.y = -speed;
	}

	void moveLeft() {
		velocity.x += -speed; // saves the movement in velocity
	}

	void moveRight() {
		velocity.x += speed; // saves the movement in velocity
	}

	void update(float delta_time) {
		/* Updates the character position according to velocity */
		sprite.move(velocity * delta_time);
		// Add Gravity
		if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height < 870) {
			velocity.y += 981.0f*0.6 * delta_time;
		}
		else {
			velocity.y = 0.0f;
		}
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}

	void setScale(int x, int y) {
		this->sprite.setScale(x, y);
	}

	void move(float x, float y) {
		sprite.move(x, y);
	}

	Vector2f getPosition() {
		return sprite.getPosition();
	}

	void setPosition(int x, int y) {
		return sprite.setPosition(x, y);
	}

	void setTextureRect(IntRect rec) {
		sprite.setTextureRect(rec);
	}

};

struct Elevator {
	pair<int, int> init_pos, end_pos;
	Sprite elevator;
	Texture elevatorT;
	float mn_height, mx_height;


	Elevator(int mx_height, int mn_height) {
		elevatorT.loadFromFile(RESOURCES + "images/buttons_assets.png");
		elevator.setTexture(elevatorT);
		elevator.setTextureRect(IntRect(6, 7, 133, 16));
		elevator.setScale(1.3, 1.3);
		//
		this->mn_height = mn_height;
		this->mx_height = mx_height;
	}

	void move_up() {
		elevator.move(0, 5);
	}

	void move_down() {
		elevator.move(0, -5);
	}

	void set_pos(int initX, int initY, int endX, int endY) {
		elevator.setPosition(initX, initY);
		init_pos = { initX, initY };
		end_pos = { endX, endY };
	}

	void setScale(float x, float y) {
		elevator.setScale(x, y);
	}

	FloatRect getGlobalBounds() {
		return elevator.getGlobalBounds();
	}
};

struct Button {
	Sprite button;
	Texture buttonT;
	bool isOn = false;
	Elevator* elev_pnt;
	int initY;


	Button(int X, int Y, Elevator* elev) {
		buttonT.loadFromFile(RESOURCES + "images/buttons_assets.png");
		button.setTexture(buttonT);
		button.setTextureRect(IntRect(518, 30, 77, 26));
		button.setScale(0.8, 0.8);
		button.setPosition(X, Y);
		this->elev_pnt = elev;
		initY = Y;
	}


	void move_elev_up() {
		if (elev_pnt->getGlobalBounds().top > elev_pnt->mx_height) {
			elev_pnt->elevator.move(0, -2);
		}
		
	}

	void move_elev_down() {
		if (elev_pnt->getGlobalBounds().top+elev_pnt->getGlobalBounds().height < elev_pnt->mn_height) {
			elev_pnt->elevator.move(0, 3);
		}
	}

	FloatRect getGlobalBounds() {
		return button.getGlobalBounds();
	}
};



