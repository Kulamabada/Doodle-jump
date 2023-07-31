#include "Doodle_jump.hpp"

void Game::GameOver() {
	bool clear_screen = true;

	background.gameOver();
	score.show();
	for (auto i = platforms.begin(); i != platforms.end(); i++)
		if ((*i)->outOfScreen() == false) {
			clear_screen = false;
			(*i)->show();
			(*i)->y += 1;
		}

	for (auto i = bullets.begin(); i != bullets.end(); i++)
		if ((*i)->speed != 0 && !(*i)->outOfScreen()) {
			(*i)->move();
			(*i)->show();
		}

	for (auto i = enemies.begin(); i != enemies.end(); i++)
		if ((*i)->spawned && !(*i)->outOfScreen())
			(*i)->show();

	if (clear_screen) {
		score.score_dist = 0;
		score.score_plat = 0;
		spawning_enemy = -1;
		spawning_ability = -1;
		player.init();
		autos.init();

		int j = 0;
		for (auto i = platforms.begin(); i != platforms.end(); i++, j++) {
			delete (*i);
			int choose_type = rand() % 5;
			if (j < 10) choose_type = 1;
			if (choose_type == 0 && (*(i - 1))->platfromTypeCheck() != "fake")
				(*i) = new FakePlatform;
			else
				(*i) = new StandardPlatform;
			(*i)->loadTexture(fake_platform_textures, standard_platform_texture);
		}

		for (auto i = bullets.begin(); i != bullets.end(); i++) {
			delete (*i);
			(*i) = new Bullet;
			(*i)->loadTexture(bullet_texture);
		}

		for (auto i = enemies.begin(); i != enemies.end(); i++) {
			delete (*i);
			(*i) = new Enemy;
			(*i)->loadTexture(enemy_textures);
		}
	}
}

void Game::bulletIntersectionCheck(vector<Enemy*> ev, vector<Bullet*> bv) {
	for (auto e = ev.begin(); e != ev.end(); e++) {
		if ((*e)->spawned == false) continue;
		for (auto b = bv.begin(); b != bv.end(); b++) {
			if ((*b)->speed == 0) continue;
			int enemy_x = (*e)->x + *(*e)->plat_x, enemy_y = *(*e)->plat_y - (*e)->y;
			if (enemy_x <= (*b)->x + (*b)->w &&
				enemy_x + (*e)->w >= (*b)->x &&
				enemy_y <= (*b)->y + (*b)->h &&
				enemy_y + (*e)->h >= (*b)->y) {
				(*e)->spawned = false;
				(*e)->x = 1000;
				(*e)->y = 1000;
				(*b)->x = -100;
				(*b)->y = -100;
			}
		}
	}
}

void Game::PreInit(int& width, int& height) {
	width = screen_w;
	height = screen_h;
}

void Game::loadAllTextures() {
	string loc, extension;
	player_textures[0] = createSprite("data/doodlestein-left@2x.png");
	player_textures[1] = createSprite("data/doodlestein-left-odskok@2x.png");
	player_textures[2] = createSprite("data/doodlestein-right@2x.png");
	player_textures[3] = createSprite("data/doodlestein-right-odskok@2x.png");
	player_textures[4] = createSprite("data/shoot1.png");
	player_textures[5] = createSprite("data/shoot2.png");
	player_textures[6] = createSprite("data/shoot3.png");

	loc = "data/", extension = ".png";
	for (int i = 0; i < 10; i++) {
		string path = loc + to_string(i) + extension;
		number_textures[i] = createSprite(path.c_str());
	}

	heart_texture = createSprite("data/heart.png");

	standard_platform_texture = createSprite("data/platform.png");

	loc = "data/fake_platform";
	for (int i = 0; i < 4; i++) {
		string path = loc + to_string(i + 1) + extension;
		fake_platform_textures[i] = createSprite(path.c_str());
	}

	loc = "data/enemy";
	for (int i = 0; i < 3; i++) {
		string path = loc + to_string(i + 1) + extension;
		enemy_textures[i] = createSprite(path.c_str());
	}

	background_texture = createSprite("data/bck.png");
	score_background_texture = createSprite("data/bck.png");
	game_over_texture = createSprite("data/game_over.png");
	scope_texture = createSprite("data/scope.png");
	distance_texture = createSprite("data/distance.png");
	platforms_passed_texture = createSprite("data/platforms_passed.png");
	bullet_texture = createSprite("data/bullet.png");
}

bool Game::Init() {
	loadAllTextures();

	spawning_enemy = -1;
	spawning_ability = -1;
	background.loadTexture(background_texture, game_over_texture);
	player.loadTextures(player_textures, number_textures, heart_texture);
	player.init();
	score.loadTexture(number_textures, distance_texture, platforms_passed_texture, score_background_texture);

	autos.loadTexture(scope_texture);

	bool prev = false;
	for (int i = 0; i < 20; i++) {
		int choose_type = rand() % 5;
		if (i >= 10 && choose_type == 0 && !prev) {
			platforms.push_back(new FakePlatform);
			prev = true;
		}
		else {
			platforms.push_back(new StandardPlatform);
			prev = false;
		}
	}

	for (int i = 0; i < 20; i++)
		bullets.push_back(new Bullet);

	for (int i = 0; i < 10; i++)
		enemies.push_back(new Enemy);

	for (auto i = platforms.begin(); i != platforms.end(); i++)
		(*i)->loadTexture(fake_platform_textures, standard_platform_texture);

	for (auto i = bullets.begin(); i != bullets.end(); i++)
		(*i)->loadTexture(bullet_texture);

	for (auto i = enemies.begin(); i != enemies.end(); i++)
		(*i)->loadTexture(enemy_textures);

	return true;
}

void Game::Close() {
	for (int i = 0; i < 10; i++)
		destroySprite(number_textures[i]);

	for (int i = 0; i < 7; i++)
		destroySprite(player_textures[i]);

	destroySprite(bullet_texture);
	destroySprite(background_texture);
	destroySprite(game_over_texture);
	destroySprite(standard_platform_texture);
	destroySprite(scope_texture);
	destroySprite(distance_texture);
	destroySprite(platforms_passed_texture);
	destroySprite(heart_texture);
	destroySprite(score_background_texture);

	for (int i = 0; i < 3; i++)
		destroySprite(enemy_textures[i]);

	for (int i = 0; i < 4; i++)
		destroySprite(fake_platform_textures[i]);

	bullets.clear();
	platforms.clear();
	enemies.clear();
}

bool Game::Tick() {
	if (player.outOfScreen()) {
		if (player.alive && player.lifes-- > 1) {
			player.y = -100;
			for (auto i = platforms.begin(); i != platforms.end(); i++)
				if ((*i)->y < screen_h && player.y + player.h < (*i)->y && (*i)->platfromTypeCheck() == "standard") {
					player.y = (*i)->y - player.h;
					player.x = (*i)->x + (*i)->w / 2 - player.w / 2;
					player.acceleration = player.max_speed;
				}
		}
		else {
			GameOver();
			return false;
		}
	}

	background.show();
	player.showLifes();

	for (auto i = platforms.begin(); i != platforms.end(); i++) {
		(*i)->show();
		if ((*i)->outOfScreen()) {
			delete (*i);
			int choose_type = rand() % 5;
			if (choose_type == 0 && (i == platforms.begin() || (*(i - 1))->platfromTypeCheck() != "fake")) {
				(*i) = new FakePlatform;
				(*i)->loadTexture(fake_platform_textures, standard_platform_texture);
			}
			else {
				(*i) = new StandardPlatform;
				(*i)->loadTexture(fake_platform_textures, standard_platform_texture);
				if (spawning_enemy != 0 && score.score_plat > 30) spawning_enemy = rand() % 10;
				if (spawning_enemy == 0) p_enemy = (*i);
				else {
					if (spawning_ability != 0 && score.score_plat > 30 && !autos.active && !autos.spawned) spawning_ability = rand() % 40;
					if (spawning_ability == 0) p_ability = (*i);
				}
			}
		}
	}

	for (auto i = bullets.begin(); i != bullets.end(); i++)
		if ((*i)->speed != 0) {
			if ((*i)->outOfScreen()) {
				delete (*i);
				(*i) = new Bullet;
				(*i)->loadTexture(bullet_texture);
			}
			else {
				(*i)->move();
				(*i)->show();
			}
		}

	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		if ((*i)->spawned) {
			if ((*i)->outOfScreen()) {
				delete (*i);
				(*i) = new Enemy;
				(*i)->loadTexture(enemy_textures);
			}
			else (*i)->show();
		}
		else if (spawning_enemy == 0) {
			(*i)->spawn(p_enemy);
			spawning_enemy = -1;
		}
	}

	if (spawning_ability == 0) {
		autos.spawn(p_ability);
		spawning_ability = -1;
	}

	if (autos.spawned) {
		autos.show();
		autos.move();
	}

	if (autos.outOfScreen()) autos.init();

	if (player.AbilityIntersectionCheck(&autos)) {
		autos.init();
		autos.active = true;
	}

	if (autos.active && autos.time > 0) {
		player.showAbility(autos.time);
		autos.stop = clock();
		if ((double)(autos.stop - autos.start) / CLOCKS_PER_SEC >= 1) {
			autos.start = clock();
			autos.time--;
		}
		player.autoShooting(bullets, enemies);
	}
	else if (autos.time == 0) autos.active = false;

	bulletIntersectionCheck(enemies, bullets);

	player.show();
	player.jump(platforms, enemies, score.score_dist, score.score_plat);
	player.move();

	score.show();

	return false;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {
	mouse_x = x, mouse_y = y;
}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (button == FRMouseButton::LEFT && !isReleased && !player.outOfScreen() && player.alive)
		player.shoot(mouse_x, mouse_y, bullets);
}

void Game::onKeyPressed(FRKey k) {
	if (k == FRKey::RIGHT) {
		player.texture_index = 2;
		player.moveRight = true;
	}
	if (k == FRKey::LEFT) {
		player.texture_index = 0;
		player.moveLeft = true;
	}
}

void Game::onKeyReleased(FRKey k) {
	if (k == FRKey::RIGHT)
		player.moveRight = false;
	if (k == FRKey::LEFT)
		player.moveLeft = false;
}

const char* Game::GetTitle() {
	return "Doodle jump";
}

Game::~Game() {
	Close();
}


int main(int argc, char* argv[]) {

	srand(time(NULL));
	Game* game = new Game;
	if (argc > 1) {
		game->screen_w = atoi(argv[1]);
		game->screen_h = atoi(argv[2]);
	}
	else {
		game->screen_w = 600;
		game->screen_h = 800;
	}

	run(game);
	delete(game);
	return 0;
}
