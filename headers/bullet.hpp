#include "menu.hpp"
#include <cmath>

class Bullet:public SpriteObject {
	float x_speed, y_speed;
public:
	float x, y, speed;

	Bullet();

	void show();

	void loadTexture(Sprite* bullet_texture);

	void move();

	void shoot(int start_x, int start_y, int mouse_x, int mouse_y);

	bool outOfScreen();

	~Bullet() {};
};

class AutoShooting :public SpriteObject {
	float* plat_y;

public:
	bool active, spawned;
	int time;
	clock_t start, stop;

	AutoShooting();

	void init();

	void loadTexture(Sprite* scope_texture);

	void spawn(Platform* p);

	void show();

	void move();

	bool outOfScreen();

	~AutoShooting() {};
};
