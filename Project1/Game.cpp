#include "Game.h"
#include <iostream>
#include "globals.h"
#include "Player.h" 

Player* player;

Game::Game() {}
Game::~Game() {}
void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init-ed!!!!" << std::endl;
		
		window = SDL_CreateWindow("Cross the Road", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			(MAP_SIZE+1) * CELL_SIZE, (MAP_SIZE+1) * CELL_SIZE, SDL_WINDOW_SHOWN);
		if (window) {
			std::cout << "window created!!!!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created!!!!" << std::endl;
		}
		is_running = true;
	}
	else {
		is_running = false;
	}

	player = new Player("assets/frog.bmp", renderer);
}
void Game::handle_events() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;
	}
}
void Game::update() {
	player->update();
}
void Game::render() {
	SDL_RenderClear(renderer);
	player->render();
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "ge-mu o-ba da yo. kimi mo boku mo." << std::endl;

}
bool Game::get_is_running() {return is_running;}
