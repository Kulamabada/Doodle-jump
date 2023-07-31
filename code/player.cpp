#include "player.hpp"


using namespace std;

Player::Player() {
	moveLeft = false, moveRight = false, alive = true;
	texture_index = 0, texture_jump = 0, texture_shoot = 5, shoot_time = 0, lifes = 5;
}

void Player::init() {
	lifes = 5;
	acceleration = float(screen_h / 70.0);
	max_speed = acceleration;
	x = screen_w / 2 - screen_w / 12, y = screen_h - screen_h / 4;
	
	alive = true;
}

void Player::loadTextures(Sprite* player_textures[7], Sprite* number_textures[7], Sprite* heart_texture) {
	getScreenSize(screen_w, screen_h);
	w = screen_w / 6, h = screen_h / 8;

	for (int i = 0; i < 7; i++) {
		texture[i] = player_textures[i];
		setSpriteSize(texture[i], w, h);
	}

	for (int i = 0; i < 10; i++) {
		numbers[i] = number_textures[i];
		setSpriteSize(numbers[i], screen_w/40, screen_h/40);
	}

	heart = heart_texture;
	setSpriteSize(heart, screen_w / 30, screen_h / 40);
}

void Player::show() {
	if(getTickCount() - shoot_time > 500)
		drawSprite(texture[texture_index + texture_jump], (int)x, (int)y);
	else
		drawSprite(texture[texture_shoot], (int)x, (int)y);
}
	
void Player::jump(vector <Platform*> pv, vector <Enemy*> ev, int &score_dist, int &score_plat){
	static int jump_flag = 0;
	if (getTickCount() - jump_flag < 10) return;
	jump_flag = getTickCount();

	texture_jump = (int)(acceleration >= max_speed/4);

	EnemyIntersectionCheck(ev);
	if (!alive){
		y -= acceleration;
		acceleration -= 0.3;
		return;
	}

	if (y <= screen_h/2 && acceleration > 0) {
		for (auto i = pv.begin(); i != pv.end(); i++) {
			(*i)->y += acceleration + (screen_h/2 - y);
			if (y + h <= (*i)->y && (*i)->isJumpedOver == false)
				(*i)->isJumpedOver = true, score_plat++;
		}
		score_dist += acceleration;
		y = screen_h / 2;
	}
	else y -= acceleration;

	acceleration -= 0.3;

	if (acceleration < 0) {
		for (auto i = ev.begin(); i != ev.end(); i++) {
			int enemy_x = (*i)->x + *(*i)->plat_x, enemy_y = *(*i)->plat_y - (*i)->y;
			if (x + w / 3 <= enemy_x + (*i)->w && x + w - w / 3 >= enemy_x && y + h < enemy_y && y + h - acceleration > enemy_y) {
				(*i)->spawned = false;
				(*i)->x = -1000;
				(*i)->y = -1000;
			}
		}
		for (auto i = pv.begin(); i != pv.end(); i++)
			if (x + w / 3 <= (*i)->x + (*i)->w &&
				x + w - w / 3 >= (*i)->x &&
				y + h <= (*i)->y &&
				y + h - acceleration >= (*i)->y &&
				(*i)->y <= screen_h) {
					if ((*i)->platfromTypeCheck() == "standard") {
						acceleration = max_speed;
						y = (*i)->y - h;
					}
					else
						(*i)->is_destroyed = true;
			}
	}
}

void Player::EnemyIntersectionCheck(vector<Enemy*> ev) {
	for (auto e = ev.begin(); e != ev.end(); e++) {
		if ((*e)->spawned == false) continue;
		int enemy_x = (*e)->x + (int)(*(*e)->plat_x), enemy_y = (int)(*(*e)->plat_y) - (*e)->y;

		if (getTickCount() - shoot_time <= 500 && 
			(enemy_x <= (int)x + w - w / 3 &&
			enemy_x + (*e)->w >= (int)x + w / 3 &&
			enemy_y <= (int)y + h &&
			enemy_y + (*e)->h >= (int)y)){
				alive = false;
				break;
			}
		else if (texture_index == 0 &&
				(enemy_x <= (int)x + w - w / 3 &&
				enemy_x + (*e)->w >= (int)x &&
				enemy_y <= (int)y + h &&
				enemy_y + (*e)->h >= (int)y)){
					alive = false;
					break;
			}
		else if (enemy_x <= (int)x + w &&
				enemy_x + (*e)->w >= (int)x + w / 3 &&
				enemy_y <= (int)y + h &&
				enemy_y + (*e)->h >= (int)y) {
					alive = false;
					break;
				}
	}
}

void Player::move() {
	if (!alive) return;
	float speed = 0.7;
	if (moveLeft) x -= speed;
	if (moveRight) x += speed;

	if (x > screen_w - w/3) x = w/3 - w;
	else if (x + w < w/3) x = screen_w - w/3;
}

void Player::showLifes(){
	drawSprite(heart,0,screen_h - screen_h / 40);
	drawSprite(numbers[lifes], screen_h / 30, screen_h - screen_h / 30);
}

bool Player::outOfScreen(){
	return y > screen_h;
}

void Player::shoot(int mouse_x, int mouse_y, vector <Bullet*> bullets) {
	Bullet* b = NULL;
	for (auto i = bullets.begin(); i != bullets.end(); i++)
		if ((*i)->speed == 0) {
			b = (*i);
			break;
		}
	texture_shoot = 4 + (int)(mouse_x > screen_w/3) + (int)(mouse_x > 2*screen_w/3);
	shoot_time = getTickCount();
	b->shoot(x+w/2, y + h/10, mouse_x, mouse_y);
}

void Player::showAbility(int t){
	string temp_t = to_string(t);
	for (int i = 0; i < temp_t.length(); i++)
		drawSprite(numbers[temp_t[i] - '0'], x +(i+1)* screen_h / 30, y - screen_h / 30);
}

void Player::autoShooting(vector <Bullet*> bullets, vector <Enemy*> enemies) {
	static int auto_shooting_flag = 0;
	if (getTickCount() - auto_shooting_flag < 175) return;
	auto_shooting_flag = getTickCount();

	for (auto i = enemies.begin(); i != enemies.end(); i++)
		if (*((*i)->plat_y) - (*i)->y > 0 && *((*i)->plat_y) - (*i)->y + (*i)->h < screen_h / 3) {
			Bullet* b = NULL;
			for (auto j = bullets.begin(); j != bullets.end(); j++)
				if ((*j)->speed == 0) {
					b = (*j);
					break;
				}
			int enemy_x = (*i)->x + *((*i)->plat_x) + (*i)->w/2;
			int enemy_y = *((*i)->plat_y) - (*i)->y + (*i)->h;
			texture_shoot = 4 + (int)(enemy_x > screen_w / 3) + (int)(enemy_x > 2 * screen_w / 3);
			shoot_time = getTickCount();
			b->shoot(x + w / 2, y + h/10, enemy_x, enemy_y);
			break;
		}
}

bool Player::AbilityIntersectionCheck(AutoShooting* as) {
	return (x <= as->x + as->w && x + w >= as->x && y <= as->y + as->h && y + h >= as->y);
}