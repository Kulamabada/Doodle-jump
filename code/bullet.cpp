#include "bullet.hpp"

Bullet::Bullet(){
	x = -100, y = -100; speed = 0, x_speed = 0, y_speed = 0;
}

void Bullet::show(){
	drawSprite(texture, (int)x, (int)y);
}

void Bullet::loadTexture(Sprite* bullet_texture) {
	texture = bullet_texture;
	getScreenSize(screen_w, screen_h);
	w = screen_w / 30, h = screen_h / 40;
	setSpriteSize(texture, w, h);
}

void Bullet::move() {
	x += x_speed, y += y_speed;
	if (x > screen_w - w / 3) x = w / 3 - w;
	else if (x + w < w / 3) x = screen_w - w / 3;
}

void Bullet::shoot(int start_x, int start_y, int mouse_x, int mouse_y) {
	if (mouse_y > screen_h / 4) mouse_y = screen_h / 4;

	x = start_x, y = start_y;
	speed = 4;

	x_speed = (float)(mouse_x - x);
	y_speed = (float)(mouse_y - y);
	float len = sqrt(pow(x_speed, 2) + pow(y_speed, 2));
	x_speed = (x_speed * speed)/len;
	y_speed = (y_speed * speed)/len;
}

bool Bullet::outOfScreen() {
	return y+h < 0 || x + w < 0 || x > screen_w;
}


AutoShooting::AutoShooting(){
	init();
}

void AutoShooting::init() {
	x = -100, y = -100, time = 20;
	active = false;
	spawned = false;
}

void AutoShooting::loadTexture(Sprite* scope_texture){
	texture = scope_texture;
	getScreenSize(screen_w, screen_h);
	w = screen_w / 15, h = screen_h / 20;
	setSpriteSize(texture, w, h);
}

void AutoShooting::show(){
	drawSprite(texture, x, y);
}

void AutoShooting::move(){
	y = *plat_y - h;
}

bool AutoShooting::outOfScreen(){
	return (y > screen_h);
}


void AutoShooting::spawn(Platform* p) {
	spawned = true;
	x = p->x + rand()%(p->w - w);
	y = p->y - h;
	plat_y = &(p->y);
	start = clock();
	start = clock();
}
