#pragma once
#include <SDL.h>
//#include <SDL_image.h>
//#include "Game.h"
#include "Car.h"

class Player {
public:
	Player(const char* filename, SDL_Renderer* ren);
	//~Player();
	void update(char direction);
	void render();
	void set_alive();
	bool get_alive();
	bool is_colliding(Car& i_car);
	const SDL_Rect get_rect();

private:
	int x;
	int y;
	bool alive;
	SDL_Texture* texture;
	SDL_Rect src_rect, dst_rect;
	SDL_Renderer* renderer;
	

};

