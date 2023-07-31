#include "framework.hpp"

SDL_Renderer* renderer;
SDL_Window* window;

Sprite* createSprite(const char* path) {
    Sprite* sprite = new Sprite;
    sprite->texture = IMG_LoadTexture(renderer, path);
    int w = 0, h = 0;
    SDL_QueryTexture(sprite->texture, NULL, NULL, &w, &h);
    sprite->rect.w = w;
    sprite->rect.h = h;
    return sprite;
}

void drawSprite(Sprite* s, int x, int y){
    s->rect.x = x;
    s->rect.y = y;
    SDL_RenderCopy(renderer, s->texture, NULL, &(s->rect));
}

void getSpriteSize(Sprite* s, int& w, int& h){
    w = s->rect.w;
    h = s->rect.h;
}

void setSpriteSize(Sprite* s, int w, int h){
    s->rect.w = w;
    s->rect.h = h;
}

void destroySprite(Sprite* s){
    SDL_DestroyTexture(s->texture);
}

void getScreenSize(int& w, int& h){
    SDL_GetWindowSize(window, &w, &h);
}

unsigned int getTickCount(){
    return SDL_GetTicks();
}

int run(Framework* game) {
    int screen_width, screen_height;
    game->PreInit(screen_width, screen_height);
    window = SDL_CreateWindow(game->GetTitle(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        printf("Warning: Linear texture filtering not enabled!");


    if (window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if(game->Init() == false) return 0;

    SDL_Event e;
    int time_flag = 0;
    bool quit = false;
    while (!quit)
    {
        while ((getTickCount() - time_flag) < 1);
        time_flag = getTickCount();

        SDL_SetRenderDrawColor(renderer, 96, 178, 255, 255);
        SDL_RenderClear(renderer);

        quit = game->Tick();

        const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
        static bool up = false, down = false, right = false, left = false;

        if (keyboardstate[SDL_SCANCODE_UP] && !up) {
            game->onKeyPressed(FRKey::UP);
            up = true;
        }
        else if (!keyboardstate[SDL_SCANCODE_UP] && up) {
            game->onKeyReleased(FRKey::UP);
            up = false;
        }
        if (keyboardstate[SDL_SCANCODE_DOWN] && !down) {
            game->onKeyPressed(FRKey::DOWN);
            down = true;
        }
        else if (!keyboardstate[SDL_SCANCODE_DOWN] && down) {
            game->onKeyReleased(FRKey::DOWN);
            down = false;
        }
        if (keyboardstate[SDL_SCANCODE_RIGHT] && !right) {
            game->onKeyPressed(FRKey::RIGHT);
            right = true;
        }
        else if (!keyboardstate[SDL_SCANCODE_RIGHT] && right) {
            game->onKeyReleased(FRKey::RIGHT);
            right = false;
        }
        if (keyboardstate[SDL_SCANCODE_LEFT] && !left) {
            game->onKeyPressed(FRKey::LEFT);
            left = true;
        }
        else if (!keyboardstate[SDL_SCANCODE_LEFT] && left) {
            game->onKeyReleased(FRKey::LEFT);
            left = false;
        }

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button) {
                case SDL_BUTTON_LEFT:
                    game->onMouseButtonClick(FRMouseButton::LEFT, false);
                    break;
                case SDL_BUTTON_MIDDLE:
                    game->onMouseButtonClick(FRMouseButton::MIDDLE, false);
                    break;
                case SDL_BUTTON_RIGHT:
                    game->onMouseButtonClick(FRMouseButton::RIGHT, false);
                    break;
                default:
                    break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch (e.button.button) {
                case SDL_BUTTON_LEFT:
                    game->onMouseButtonClick(FRMouseButton::LEFT, true);
                    break;
                case SDL_BUTTON_MIDDLE:
                    game->onMouseButtonClick(FRMouseButton::MIDDLE, true);
                    break;
                case SDL_BUTTON_RIGHT:
                    game->onMouseButtonClick(FRMouseButton::RIGHT, true);
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        int x, y, xrel, yrel;
        SDL_GetMouseState(&x, &y);
        SDL_GetGlobalMouseState(&xrel, &yrel);
        game->onMouseMove(x, y, xrel, yrel);

        SDL_RenderPresent(renderer);
    }

    game->Close();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}