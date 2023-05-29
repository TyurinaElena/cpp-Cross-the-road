//#include <SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include "support.h"
#include "Player.h"
#include "globals.h"


Player::Player(SDL_Renderer* ren) {
	renderer = ren;
	texture_u = load_texture("assets/frog.bmp", renderer, 255, 0, 0);
	texture_l = load_texture("assets/frog_l.bmp", renderer, 255, 0, 0);
	texture_r = load_texture("assets/frog_r.bmp", renderer, 255, 0, 0);
	texture_d = load_texture("assets/frog_d.bmp", renderer, 255, 0, 0);
	rect.h = CELL_SIZE;
	rect.w = CELL_SIZE;
	init();
}
//Player::~Player() {}

void Player::update(char direction) {
	//std::string direction
	if (alive) {
		if (direction == 'l') {
			if (x > 0) { x -= 1; }
			curr_dir = direction;
		}
		else if (direction == 'r') {
			if (x < MAP_SIZE) { x += 1; }
			curr_dir = direction;
		}
		else if (direction == 'd') {
			if (y < MAP_SIZE) { y += 1; }
			curr_dir = direction;
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
			curr_dir = direction;
		}
		if (y == 0) {
			reset_timer();
		}
		rect.x = x * CELL_SIZE;
		rect.y = y * CELL_SIZE;
	}
	else {
		reset_timer();
	}
}

void Player::render() {
	if (curr_dir == 'd') {
		SDL_RenderCopy(renderer, texture_d, NULL, &rect);
	}
	else if (curr_dir == 'l') {
		SDL_RenderCopy(renderer, texture_l, NULL, &rect);
	}
	else if (curr_dir == 'r') {
		SDL_RenderCopy(renderer, texture_r, NULL, &rect);
	}
	else {
		SDL_RenderCopy(renderer, texture_u, NULL, &rect);
	}
}

void Player::set_alive()
{
	alive = false;
	//std::cout << "you died" << std::endl;
}

bool Player::get_alive() {
	return alive;
}
int Player::get_score()
{
	return score;
}
int Player::get_lives()
{
	return lives;
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
		lives -= 1;
	}
}

void Player::set_reset_time()
{
	reset_time = SDL_GetTicks();
}

void Player::init()
{
	x = MAP_SIZE / 2;
	y = MAP_SIZE;
	alive = true;
	rect.x = 0;
	rect.y = 0;

	score = 0;
	path = 0;
	lives = 3;
	curr_dir = 'u';
}

void Player::reset_timer()
{
	Uint32 time = SDL_GetTicks();
	if (time - reset_time > RESET_DELAY) {
		reset();
	}
}
