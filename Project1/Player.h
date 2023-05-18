#pragma once
#include <SDL.h>
//#include <SDL_image.h>
#include "Game.h"

class Player {
public:
	Player(const char* filename, SDL_Renderer* ren);
	~Player();
	void update(char direction);
	void render();
private:
	int x;
	int y;
	SDL_Texture* texture;
	SDL_Rect src_rect, dst_rect;
	SDL_Renderer* renderer;

};

