#include "framework.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class SpriteObject {
public:
	int x, y, w, h, screen_w, screen_h;
	Sprite* texture;

	SpriteObject() {};

	void show();

	~SpriteObject() {};
};

class Platform:public SpriteObject {
protected:
	void setPosition();

public:
	float x, y;

	bool isJumpedOver, is_destroyed;

	virtual string platfromTypeCheck() = 0;

	virtual void loadTexture(Sprite* fake_platform_textures[4], Sprite* standard_platform_texture) = 0;

	bool outOfScreen();

	virtual void show() = 0;

	~Platform() {};
};

class StandardPlatform : public Platform {
	void loadTexture(Sprite* fake_platform_textures[4], Sprite* standard_platform_texture);

public:
	StandardPlatform();

	string platfromTypeCheck();

	void show();

	~StandardPlatform() {};
};

class FakePlatform : public Platform {
	int time;

	void loadTexture(Sprite* fake_platform_textures[4], Sprite* standard_platform_texture);

	Sprite* texture[4];

public:
	FakePlatform();

	void show();

	string platfromTypeCheck();

	~FakePlatform() {};
};
