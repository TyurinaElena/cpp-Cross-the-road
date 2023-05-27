#pragma once
#include <SDL.h>
#include <string>
#include "Car.h"

class Player {
public:
	Player(const char* filename, SDL_Renderer* ren);
	//~Player();
	void update(char direction);
	void render();
	void set_alive();
	bool get_alive();
	std::string get_score();
	bool is_colliding(Car& i_car);
	const SDL_Rect get_rect();
	void reset();

private:
	int x;
	int y;
	bool alive;
	int score;
	int path;
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Renderer* renderer;
	Uint32 reset_time;
	void reset_timer();
	

};

