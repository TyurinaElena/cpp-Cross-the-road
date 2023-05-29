#pragma once
#include <SDL.h>
#include <string>
#include "Car.h"

class Player {
public:
	Player(SDL_Renderer* ren);
	//~Player();
	void update(char direction);
	void render();
	void set_alive();
	bool get_alive();
	int get_score();
	int get_lives();
	bool is_colliding(Car& i_car);
	const SDL_Rect get_rect();
	void reset();
	void set_reset_time();
	void init();

private:
	int x;
	int y;
	bool alive;
	int score;
	int path;
	int lives;
	char curr_dir;
	SDL_Texture* texture_u;
	SDL_Texture* texture_r;
	SDL_Texture* texture_l;
	SDL_Texture* texture_d;
	SDL_Rect rect;
	SDL_Renderer* renderer;
	Uint32 reset_time;
	void reset_timer();
	

};

