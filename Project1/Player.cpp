//#include <SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "globals.h"

int count_digit(int number) {
	int count = 0;
	while (number != 0) {
		number = number / 10;
		count++;
	}
	return count > 0 ? count : 1;
}

Player::Player(const char* filename, SDL_Renderer* ren) {
	renderer = ren;
	x = MAP_SIZE/2;
	y = MAP_SIZE;
	alive = true;
	SDL_Surface* img = SDL_LoadBMP(filename);
	SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 0));
	texture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	rect.x = 0 ;
	rect.y = 0 ;
	rect.h = CELL_SIZE;
	rect.w = CELL_SIZE;
	score = 0;
	path = 0;

}
//Player::~Player() {}

void Player::update(char direction) {
	//std::string direction
	if (alive) {
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
			if (y + path <= MAP_SIZE) {
				score += 10;
				path += 1;
			}
			if (y > 0) {
				y -= 1;
				if (y == 0) { reset_time = SDL_GetTicks(); }
			}
		}
		if (y == 0) {
			reset_timer();
		}
		rect.x = x * CELL_SIZE;
		rect.y = y * CELL_SIZE;
	}
	else {
		reset();
	}
}

void Player::render() {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Player::set_alive()
{
	alive = false;
	//std::cout << "you died" << std::endl;
}

bool Player::get_alive() {
	return alive;
}
std::string Player::get_score()
{
	int count = count_digit(score);
	std::string str = std::string(5-count, '0');
	str += std::to_string(score);
	return str;
}
bool Player::is_colliding(Car& i_car)
{
	const SDL_Rect temp2 = i_car.get_col_rect();
	const SDL_Rect temp1 = get_rect();
	return SDL_HasIntersection(&temp1, &temp2);
}
const SDL_Rect Player::get_rect() {
	SDL_Rect col_rect;
	int d = 5;
	col_rect.x = rect.x + d;
	col_rect.y = rect.y + d;
	col_rect.h = rect.h- d*2;
	col_rect.w = rect.w - d * 2;
	return col_rect;
}

void Player::reset()
{
	x = MAP_SIZE / 2;
	y = MAP_SIZE;
	if (alive) {
		path = 0;
		score += 100;
	}
	else {
		alive = true;
	}
}

void Player::reset_timer()
{
	Uint32 time = SDL_GetTicks();
	if (time - reset_time > RESET_DELAY) {
		reset();
	}
}
