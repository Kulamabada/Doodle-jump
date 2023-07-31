#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include "player.hpp"

class Game : public Framework {
	Sprite* number_textures[10];
	Sprite* player_textures[7];
	Sprite* fake_platform_textures[4];
	Sprite* enemy_textures[3];
	Sprite* bullet_texture;
	Sprite* background_texture;
	Sprite* game_over_texture;
	Sprite* standard_platform_texture;
	Sprite* scope_texture;
	Sprite* distance_texture;
	Sprite* platforms_passed_texture;
	Sprite* heart_texture;
	Sprite* score_background_texture;

	int mouse_x, mouse_y;
	int spawning_enemy, spawning_ability;

	Player player;
	Score score;
	Background background;
	AutoShooting autos;
	Platform* p_enemy;
	Platform* p_ability;

	vector <Bullet*> bullets;
	vector <Platform*> platforms;
	vector <Enemy*> enemies;

	void loadAllTextures();

	void GameOver();

	void bulletIntersectionCheck(vector<Enemy*> ev, vector<Bullet*> bv);

public:
	int screen_w, screen_h;

	virtual void PreInit(int& width, int& height);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

	virtual const char* GetTitle() override;

	~Game();
};
