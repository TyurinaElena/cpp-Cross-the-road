#pragma once
#include <SDL.h>

class Car
{
private:
	double x;
	double y;
	short size;
	double speed;
	short direction;
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Renderer* renderer;

public:
	Car(int i, int j, short sz, short spd, short dir, SDL_Renderer* ren);
	int get_x();
	short get_direction();
	short get_speed();
	const SDL_Rect get_col_rect();
	void update();
	void render();
	
};

