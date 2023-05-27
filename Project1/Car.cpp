#include <iostream>
#include "Car.h"
#include "globals.h"

Car::Car( int j, int i, short sz, short spd, short dir, SDL_Renderer* ren) {
	renderer = ren;
	x =  double(j) * CELL_SIZE;
	y = double(i) * CELL_SIZE;
	size = sz;
	speed = spd;
	direction = dir;
	SDL_Surface* img;
	if (size == 1) {
		img = SDL_LoadBMP("assets/small_car.bmp");
		SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 255));
	}
	else if (size == 2) {
		img = SDL_LoadBMP("assets/car.bmp");
		SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 0));
	}
	else {
		img = SDL_LoadBMP("assets/large_car.bmp");
		SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 255));
	}
	texture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	rect.x = x;
	rect.y = y;
	rect.h = CELL_SIZE;
	rect.w = CELL_SIZE * size;
}

int Car::get_x() {
	return x;
}

short Car::get_direction() {
	return direction;
}

short Car::get_speed() {
	return speed;
}
const SDL_Rect Car::get_col_rect() {
	SDL_Rect col_rect;
	int d = 5;
	col_rect.x = x + d;
	col_rect.y = y + d;
	col_rect.h = rect.h-d*2;
	col_rect.w = rect.w - d*2;
	return col_rect;
}
void Car::update() {
	x += speed*direction/3;
	rect.x = x;
}

void Car::render() {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
