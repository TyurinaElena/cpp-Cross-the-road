#pragma once

#include <SDL.h>
//#include "Player.h"

class Game {
	
public:
	Game();
	~Game();
	void init();
	void handle_events();
	void update(char direction);
	void render();
	void clean();
	bool get_is_running();
private:
	bool is_running;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

/*SDL_Init(SDL_INIT_EVERYTHING);

SDL_Window* window = SDL_CreateWindow("Cross the Road", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	MAP_SIZE * CELL_SIZE, MAP_SIZE * CELL_SIZE, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
SDL_RenderClear(renderer);
SDL_RenderPresent(renderer);
SDL_Delay(3000);*/