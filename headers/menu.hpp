#include "sprites.hpp"

class Score:public SpriteObject {
	Sprite* texture[10];
	Sprite* dist;
	Sprite* plat;
	Sprite* bck;
public:
	int score_dist, score_plat;

	Score();

	void loadTexture(Sprite* number_textures[10], Sprite* distance_texture, Sprite* platforms_passed_texture, Sprite* background_texture);

	void show();

	~Score() {};
};

class Background :public SpriteObject {
	Sprite* game_over;

public:

	Background();

	void gameOver();

	void loadTexture(Sprite* background_texture,Sprite* game_over_texture);

	~Background() {};
};

