#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

class Sprite {
public:
	SDL_Rect rect;
	SDL_Texture* texture;
};

Sprite* createSprite(const char* path);
void drawSprite(Sprite* s, int x, int y);

void getSpriteSize(Sprite* s, int& w, int& h);
void setSpriteSize(Sprite* s, int w, int h);
void destroySprite(Sprite* s);


void getScreenSize(int& w, int& h);

unsigned int getTickCount();

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class Framework {
public:

	// no function calls are available here, this function should only return width and height values
	virtual void PreInit(int& width, int& height) = 0;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick() = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

	virtual const char* GetTitle() = 0;

	virtual ~Framework() {};
};


int run(Framework* game);
