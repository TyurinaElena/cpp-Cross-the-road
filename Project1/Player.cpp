//#include <SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "globals.h"

Player::Player(const char* filename, SDL_Renderer* ren) {
	renderer = ren;
	x = MAP_SIZE/2;
	y = MAP_SIZE;
	SDL_Surface* img = SDL_LoadBMP(filename);
	SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 0));
	texture = SDL_CreateTextureFromSurface(ren, img);
	if (texture) {
		std::cout << "the frog is here" << std::endl;
	}
	else {
		std::cout << "i don't know where's the frog, dude..." << std::endl;
	}
	SDL_FreeSurface(img);
	src_rect.h = CELL_SIZE;
	src_rect.w = CELL_SIZE;
	src_rect.x = 0;
	src_rect.y = 0;
	dst_rect.x = 0 ;
	dst_rect.y = 0 ;
	dst_rect.h = src_rect.h;
	dst_rect.w = src_rect.h;
}
Player::~Player() {}
//int Player::get_x() { return x; }
//int Player::get_y() { return y; }
void Player::update() {
	//x = 64;
	//y = 64;
	dst_rect.x = x*CELL_SIZE;
	dst_rect.y = y*CELL_SIZE;
	//std::string direction
	//if (direction == "left") { 
	//	if (x > 0) { x -= 1; }
	//}
	//else if (direction == "right") { 
	//	if (x < MAP_SIZE) { x += 1; }
	//}
	//else if (direction == "down") {
	//	if (y < MAP_SIZE) { y += 1; }
	//}
	//else {
	//	if (x < MAP_SIZE) { y -= 1; }
	//}
}

void Player::render() {
	SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}