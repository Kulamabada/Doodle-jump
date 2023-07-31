#include "sprites.hpp"

using namespace std;

void SpriteObject::show() {
	drawSprite(texture, (int)x, (int)y);
}


bool Platform::outOfScreen() {
	return y > screen_h + screen_h/16;
}

void Platform::setPosition() {
	static float* y_prev = new float(screen_h);

	x = rand() % (screen_w - w);
	y = *y_prev - 2 * h - rand() % 2 * h;
	if (*y_prev >= screen_h) x = rand() % w + screen_w / 2 - w / 2;
	y_prev = &y;
}


StandardPlatform::StandardPlatform() {
	x = -100;
	y = -100;
	isJumpedOver = false;
}

void StandardPlatform::loadTexture(Sprite* fake_platform_textures[4], Sprite* standard_platform_texture) {
	texture = standard_platform_texture;
	getScreenSize(screen_w, screen_h);

	w = screen_w / 6, h = screen_h / 40;
	setSpriteSize(texture, w, h);

	setPosition();	
}

string StandardPlatform::platfromTypeCheck(){
	return "standard";
}

void StandardPlatform::show(){
	drawSprite(texture, (int)x, (int)y);
}


FakePlatform::FakePlatform() {
	x = -100; y = -100, time = 0;
	isJumpedOver = false, is_destroyed = false;
}

void FakePlatform::loadTexture(Sprite* fake_platform_textures[4], Sprite* standard_platform_texture) {
	getScreenSize(screen_w, screen_h);
	w = screen_w / 6, h = screen_h / 40;

	for (int i = 0; i < 4; i++) {
		texture[i] = fake_platform_textures[i];
		setSpriteSize(texture[i], w, h);
	}
	setPosition();

}

void FakePlatform::show(){
	if (!is_destroyed)
		drawSprite(texture[0], x, y);
	else {
		if(!time) time = getTickCount();
		int texture_index = 0;
		int animation_time = 150;
		for (size_t i = 1; i < 4; i++)
			texture_index += (int)(getTickCount() - time > i * animation_time);
		drawSprite(texture[texture_index], x, y++);
	}
}

string FakePlatform::platfromTypeCheck(){
	return "fake";
}
