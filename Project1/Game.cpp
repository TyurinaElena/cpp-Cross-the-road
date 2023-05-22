#include "Game.h"
#include <iostream>
#include <list>
#include <array>
#include "globals.h"
#include "Player.h" 
#include "CarManager.h"

Player* player;
CarManager* car_manager;

Game::Game() {
	init();
}
//Game::~Game() {}
void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init-ed!!!!" << std::endl;
		
		window = SDL_CreateWindow("Cross the Road", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			(MAP_SIZE+1) * CELL_SIZE, (MAP_SIZE+1) * CELL_SIZE, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		is_running = true;
	}
	else {
		is_running = false;
	}

	player = new Player("assets/frog.bmp", renderer);
	car_manager = new CarManager(renderer);
}
void Game::handle_events() {
	char direction = 'n';
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w:
					direction = 'u';
					break;
				case SDLK_DOWN:
				case SDLK_s:
					direction = 'd';
					break;
				case SDLK_LEFT:
				case SDLK_a:
					direction = 'l';
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					direction = 'r';
					break;
				default:
					break;
			}
		default:
			break;
	}
	update(direction);
}
void Game::update(char direction) {
	player->update(direction);
	car_manager->update(*player);
}
void Game::render() {
	SDL_RenderClear(renderer);
	player->render();
	car_manager->render();
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	delete[] player;
	delete[] car_manager;
}
bool Game::get_is_running() {return is_running;}
