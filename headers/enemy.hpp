#include "bullet.hpp"


class Enemy :public SpriteObject {
	Sprite* texture[3];
	int texture_index;

public:
	bool spawned;
	float* plat_x, *plat_y;

	Enemy();

	void spawn(Platform* p);

	void loadTexture(Sprite* enemy_textures[3]);

	void show();

	bool outOfScreen();

	~Enemy() {};
};