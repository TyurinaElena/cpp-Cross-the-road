//#include <SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "globals.h"

Player::Player(const char* filename, SDL_Renderer* ren) {
	renderer = ren;
	x = MAP_SIZE/2;
	y = MAP_SIZE;
	alive = true;
	SDL_Surface* img = SDL_LoadBMP(filename);
	SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 0));
	texture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	src_rect.h = CELL_SIZE;
	src_rect.w = CELL_SIZE;
	src_rect.x = 0;
	src_rect.y = 0;
	dst_rect.x = 0 ;
	dst_rect.y = 0 ;
	dst_rect.h = src_rect.h;
	dst_rect.w = src_rect.w;

}
//Player::~Player() {}

void Player::update(char direction) {
	//std::string direction
	if (direction == 'l') { 
		if (x > 0) { x -= 1; }
	}
	else if (direction == 'r') {
		if (x < MAP_SIZE) { x += 1; }
	}
	else if (direction == 'd') {
		if (y < MAP_SIZE) { y += 1; }
	}
	else if (direction == 'u') {
		if (y > 0) { y -= 1; }
	}
	dst_rect.x = x * CELL_SIZE;
	dst_rect.y = y * CELL_SIZE;
	
}

void Player::render() {
	SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}

void Player::set_alive()
{
	alive = false;
	//std::cout << "you died" << std::endl;
}

bool Player::get_alive() {
	return alive;
}
bool Player::is_colliding(Car& i_car)
{
	const SDL_Rect temp2 = i_car.get_col_rect();
	const SDL_Rect temp1 = get_rect();
	return SDL_HasIntersection(&temp1, &temp2);
}
const SDL_Rect Player::get_rect() {
	SDL_Rect rect;
	int d = 5;
	rect.x = dst_rect.x + d;
	rect.y = dst_rect.y + d;
	rect.h = dst_rect.h- d*2;
	rect.w = dst_rect.w - d * 2;
	//std::cout << dst_rect.y << " " << rect.y << std::endl;
	return rect;
}
