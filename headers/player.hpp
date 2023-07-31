#include "enemy.hpp"

class Player:public SpriteObject {
	int texture_jump, shoot_time, texture_shoot;
	Sprite* texture[7];
	Sprite* heart;
	Sprite* numbers[10];

	void EnemyIntersectionCheck(vector<Enemy*> ev);

public:
	bool moveRight, moveLeft, alive;

	int texture_index, lifes;
	float x, y, acceleration, max_speed;

	Player();

	void loadTextures(Sprite* player_textures[7], Sprite* number_textures[7], Sprite* heart_texture);

	void show();
	
	void jump(vector <Platform*> pv, vector <Enemy*> ev, int & score_dist, int &score_plat);

	void move();

	void showLifes();

	void showAbility(int t);

	void init();

	bool outOfScreen();

	bool AbilityIntersectionCheck(AutoShooting* as);

	void shoot(int mouse_x, int mouse_y, vector <Bullet*> bullets);

	void autoShooting(vector <Bullet*> bullets, vector <Enemy*> enemies);

	~Player() {};
};
