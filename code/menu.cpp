#include "menu.hpp"


using namespace std;

Score::Score() {
	score_dist = 0, score_plat = 0;
}

void Score::show() {
	drawSprite(bck, 0, 0);
	drawSprite(dist, 0, 0);

	string temp_score = to_string(score_dist);
	for (int i = 0; i < temp_score.length(); i++){
		drawSprite(texture[temp_score[i] - '0'], (i + 9) * w, 3*h/4);
	}	

	drawSprite(plat, screen_w/2 - w, 0);

	temp_score = to_string(score_plat);
	for (int i = 0; i < temp_score.length(); i++) {
		drawSprite(texture[temp_score[i] - '0'], screen_w/2 + (i + 14) * w, 3*h/4);
	}
	
}

void Score::loadTexture(Sprite* number_textures[10], Sprite* distance_texture, Sprite* platforms_passed_texture, Sprite* background_texture) {
	getScreenSize(screen_w, screen_h);
	w = screen_w / 40, h = screen_h / 40;

	for (int i = 0; i < 10; i++) {
		texture[i] = number_textures[i];
		setSpriteSize(texture[i], w, h);
	}

	dist = distance_texture;
	setSpriteSize(dist, 9 * w, 3*h);
	plat = platforms_passed_texture;
	setSpriteSize(plat, 15 * w, 3*h);
	bck = background_texture;
	setSpriteSize(bck, screen_w, 3*h);
}


Background::Background() {
	x = 0, y = 0;
}

void Background::loadTexture(Sprite* background_texture, Sprite* game_over_texture) {
	int w, h;
	getScreenSize(w, h);

	texture = background_texture;
	game_over = game_over_texture;
	setSpriteSize(texture, w, h);
	setSpriteSize(game_over, w, h);
}

void Background::gameOver(){
	drawSprite(game_over, x, y);
}
