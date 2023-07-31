#include "enemy.hpp"

Enemy::Enemy(){
	plat_x = new float(-100), plat_y = new float(-100);
	x = -100, y = -100;
	spawned = false;
	texture_index = 0;
}

void Enemy::spawn(Platform* p){
	spawned = true;
	texture_index = rand() % 3;
	plat_x = &(p->x);
	plat_y = &(p->y);
	y = h;
	x = rand() % (p->w - w);
}

void Enemy::loadTexture(Sprite* enemy_textures[3]) {
	getScreenSize(screen_w, screen_h);
	w = screen_w / 9, h = screen_h / 16;

	for (int i = 0; i < 3; i++) {
		texture[i] = enemy_textures[i];
		setSpriteSize(texture[i], w, h);
	}
}

void Enemy::show() {
	drawSprite(texture[texture_index], x + *plat_x, *plat_y - y);
}

bool Enemy::outOfScreen(){
	return y > screen_h;
}
