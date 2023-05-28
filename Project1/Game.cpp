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
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init()== 0) {
		std::cout << "SDL init-ed!!!! And ttf" << std::endl;
		
		window = SDL_CreateWindow("Cross the Road", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			(MAP_SIZE+1) * CELL_SIZE, (MAP_SIZE+2) * CELL_SIZE, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0); 
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		font = TTF_OpenFont("assets/BarcadeBrawlRegular.ttf", 14);
		if (font) {
			std::cout << "it worked!!" << std::endl;
		}
		is_running = true;
		status = 0;
	}
	else {
		is_running = false;
	}

	player = new Player("assets/frog.bmp", renderer);
	car_manager = new CarManager(renderer);
}
void Game::render_text(const char* text, SDL_Rect rect)
{
	SDL_Surface* surf_text = TTF_RenderText_Solid(font, text, { 255,255,255 });
	SDL_Texture* t_text = SDL_CreateTextureFromSurface(renderer, surf_text);
	SDL_FreeSurface(surf_text);
	SDL_RenderCopy(renderer, t_text, NULL, &rect);
}

void Game::render_endgame_box()
{
	int th = 5;
	SDL_Rect rects[] = {
		{CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*7, th},
		{CELL_SIZE * 2, CELL_SIZE * 8 - th, CELL_SIZE * 7, th},
		{CELL_SIZE * 2, CELL_SIZE * 3, th, CELL_SIZE * 5},
		{CELL_SIZE * 9-th, CELL_SIZE * 3, th, CELL_SIZE * 5},
	};
	SDL_Rect rect = { CELL_SIZE * 2, CELL_SIZE * 3, CELL_SIZE * 7, CELL_SIZE * 5 };
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 50, 75, 255);
	SDL_RenderFillRects(renderer, rects, 4);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	render_text("Game Over", { CELL_SIZE * 3, CELL_SIZE * 7/2, CELL_SIZE * 5, CELL_SIZE});
	render_text("last:", { CELL_SIZE * 3, CELL_SIZE * 5, CELL_SIZE, CELL_SIZE / 4 });
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	render_text(player->get_score().c_str(), {CELL_SIZE * 3, CELL_SIZE * 11/2, CELL_SIZE*2, CELL_SIZE*2 / 3});
	render_text("best:", { CELL_SIZE * 11/2, CELL_SIZE * 5, CELL_SIZE, CELL_SIZE / 4 });
	render_text("press space to continue", { CELL_SIZE * 5/2, CELL_SIZE * 7, CELL_SIZE * 6, CELL_SIZE/4 });
	render_text("press e to view records", { CELL_SIZE * 5 / 2, CELL_SIZE * 15/2, CELL_SIZE * 6, CELL_SIZE / 4 });
	SDL_RenderPresent(renderer);
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
	
	if (status == 0) {
		char direction = 'n';
		switch (event.type) {
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
		if (!player->get_alive() && (player->get_lives() == 0)) {
			status = 1;
			render_endgame_box();
		}
	}
	else {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				status = 0;
				player->init();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}
void Game::update(char direction) {
	player->update(direction);
	car_manager->update(*player);
}
void Game::render() {
	SDL_Rect text_rect;
	if (status == 0) {
		SDL_RenderClear(renderer);
		player->render();
		car_manager->render();
		text_rect.x = CELL_SIZE;
		text_rect.y = CELL_SIZE * (MAP_SIZE + 1);
		text_rect.w = CELL_SIZE;
		text_rect.h = CELL_SIZE / 3;
		render_text(player->get_score().c_str(), text_rect);
		SDL_RenderPresent(renderer);
	}
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	delete[] player;
	delete[] car_manager;
}
bool Game::get_is_running() {return is_running;}

short Game::get_status()
{
	return status;
}
