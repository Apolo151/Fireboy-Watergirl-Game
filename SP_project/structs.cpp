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
	float speed=300; // speed of moving right or left
	bool CanJump = true;
	float jump_height = 200;

	Player(string TextureFile, float speed) {
		characterT.loadFromFile(RESOURCES + TextureFile);
		sprite.setTexture(characterT);
		sprite.setScale(1, 1);
		this->speed = speed;
	}

	void jump() {
		velocity.y = -sqrtf(2.0f * jump_height * 981.0f);
	}

	void moveLeft(float delta_time) {
		velocity.x = -speed;//-speed*1e5;
	}

	void moveRight(float delta_time) {
		velocity.x = speed; // speed * 1e5;
	}

	void update(float delta_time) {
		sprite.move(velocity * delta_time);
		cout << velocity.y << " " << (velocity.x*delta_time) << '\n';
		velocity.y += 981.0f * delta_time*10;
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


struct player {
	Sprite sprite;
	float currentframe;
	float move_X, move_Y;
	FloatRect rect;
	bool onground;

	void sp(Texture& player_Texture) {

		sprite.setTexture(player_Texture);
		sprite.scale(1, 1);
		move_X = 0;
		move_Y = 0;
		currentframe = 0;
	}

	void update(float time, int row1, int row2) {
		rect.left += move_X * time;
		rect.top += move_Y * time;

		if (!onground) {
			move_Y = (0.5 * time);
		}
		onground = false;

		if (rect.top > ground) {
			rect.top = ground;
			move_Y = 0;
			onground = true;
		}


		currentframe += 20 * time;
		if (currentframe > 6) {
			currentframe -= 6;
		}
		//right
		if (move_X > 0) {
			sprite.setTextureRect(IntRect(row1, -22, 70, 100));

		}
		// left
		if (move_X < 0) {
			sprite.setTextureRect(IntRect(row2, 78, 70, 100));

		}
		sprite.setPosition(rect.left, rect.top);
		move_X = 0;
	}
};

struct Button {
	Sprite button;
	Texture buttonT;
	bool isOn = false;

	Button() {

	}

	Button(int X, int Y) {
		buttonT.loadFromFile(RESOURCES + "images/buttons_assets.png");
		button.setTexture(buttonT);
		button.setTextureRect(IntRect(518, 30, 77, 26));
		button.setScale(0.8, 0.8);
		button.setPosition(X, Y);
	}
};


struct Elevator {
	pair<int, int> init_pos, end_pos;
	Sprite elevator;
	Texture elevatorT;
	Button* control_buttons[5] = {};
	int num_buttons = 0; // number of controlling buttons
	

	Elevator(){
		elevatorT.loadFromFile(RESOURCES + "images/buttons_assets.png");
		elevator.setTexture(elevatorT);
		elevator.setTextureRect(IntRect(6, 7, 133, 16));
		elevator.setScale(1.07, 1.3);
		//for (int i = 0; i < 5; ++i) control_buttons[i] = nullptr;
	}

	void add_button(Button &button) {
		control_buttons[num_buttons] = &button;
		++num_buttons;
	}

	void set_pos(int initX, int initY, int endX, int endY) {
		elevator.setPosition(initX, initY);
		init_pos = { initX, initY };
		end_pos = { endX, endY };
	}

	void move_up() {
		elevator.move(0, 5);
	}
	
	void move_down() {
		elevator.move(0, -5);
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


