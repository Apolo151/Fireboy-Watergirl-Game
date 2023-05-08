#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;

const string RESOURCES = "resources/";

const float ROTATE_ANGLE = 33.f;
static int ground = 865;

// This is struct for lever objects
struct Lever {
	// checks if lever is on or off
	bool isOn=false;
	// 0 off, 1 on, 2 rotating
	// 
	// Defines lever Base and Arm
	Sprite Base, Arm;
	Texture LeverT;
	
	// Constructor
	Lever(bool isOn) : isOn(isOn) {
		LeverT.loadFromFile(RESOURCES + "images/lever_assets.png");
		this->Base.setTexture(LeverT);
		this->Arm.setTexture(LeverT);
		// set scales (found these scales to be suitable)
		this->Base.setTextureRect(IntRect(0, 45, 120, 80));
		this->Arm.setTextureRect(IntRect(382, 3, 22, 63));
		this->Base.setScale(0.8, 0.8);
		this->Arm.setScale(0.9, 0.9);
	}

	void set_pos(int baseX, int baseY, int armX, int armY, float rot) {
		this->Base.setPosition(baseX, baseY);
		this->Arm.setPosition(armX, armY);
		//
		this->Arm.setOrigin(11.f, 60.f);
		this->Arm.setRotation(rot);
	}

	// the lever is rotated left if off, right elsewise
	void turn_on() {
		if (this->Arm.getRotation() > -ROTATE_ANGLE) {
			this->Arm.rotate(-1);
		}
		else isOn = true;
	}

	void turn_off() {
		if (this->Arm.getRotation() < ROTATE_ANGLE) {
			this->Arm.rotate(1);
		}
		else isOn = false;
	}
};

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
		sprite.setScale(0.9, 0.9);
		this->speed = speed;
	}

	void jump() {
		velocity.y = -sqrtf(2.0f * jump_height * 981.0f*0.5);
		//velocity.y = -speed;
	}

	void moveLeft(float delta_time) {
		velocity.x = -speed; // saves the movement in velocity
	}

	void moveRight(float delta_time) {
		velocity.x = speed;
	}

	void update(float delta_time) {
		/* Updates the character position according to velocity */
		sprite.move(velocity * delta_time);
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
		sprite.setScale(x, y);
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

	Button(int X, int Y, Elevator* elev) {
		buttonT.loadFromFile(RESOURCES + "images/buttons_assets.png");
		button.setTexture(buttonT);
		button.setTextureRect(IntRect(518, 30, 77, 26));
		button.setScale(0.8, 0.8);
		button.setPosition(X, Y);
		this->elev_pnt = elev;
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
};


struct Diamond {
	string color;
	Texture diamondT;
	Sprite diamond;

	Diamond(string color) {
		if (color == "red") {
			diamondT.loadFromFile(RESOURCES + "images/diamonds.png");
		}
	}
};

struct Box {
	Texture BoxT;
	Sprite box;

	Box() {
		BoxT.loadFromFile(RESOURCES + "images/lever&box_assets.png");
		box.setTexture(BoxT);
		box.setTextureRect(IntRect(666, 5, 67, 66));
		box.setScale(0.8, 0.8);
	}

	void set_pos(int X, int Y) {
		box.setPosition(X, Y);
	}
};


