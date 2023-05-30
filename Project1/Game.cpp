#include "Game.h"
#include <iostream>
#include <fstream>
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
void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init()== 0) {
		
		window = SDL_CreateWindow("Cross the Road", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			(MAP_SIZE+1) * CELL_SIZE, (MAP_SIZE+2) * CELL_SIZE, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0); 
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		font = TTF_OpenFont("assets/BarcadeBrawlRegular.ttf", 14);
		if (!font) {
			std::cout << "couldn't find font." << std::endl;
		}
		SDL_Surface* img = SDL_LoadBMP("assets/heart.bmp");
		SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0, 0, 255));
		live_texture = SDL_CreateTextureFromSurface(renderer, img);
		SDL_FreeSurface(img);
		is_running = true;
		status = 0;
	}
	else {
		std::cout << "couldn't initialize SDL." << std::endl;
		is_running = false;
	}

	player = new Player(renderer);
	car_manager = new CarManager(renderer);
}
void Game::render_text(const char* text, SDL_Rect rect)
{
	SDL_Surface* surf_text = TTF_RenderUTF8_Solid(font, text, { 255,255,255 });
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
	render_text("очки:", { CELL_SIZE * 3, CELL_SIZE * 5, CELL_SIZE, CELL_SIZE / 4 });
	render_text(num_to_str(player->get_score()).c_str(), {CELL_SIZE * 3, CELL_SIZE * 11/2, CELL_SIZE*2, CELL_SIZE*2 / 3});
	render_text("рекорд:", { CELL_SIZE * 11/2, CELL_SIZE * 5, CELL_SIZE, CELL_SIZE / 4 });
	render_text(num_to_str(best_res).c_str(), { CELL_SIZE * 11/2, CELL_SIZE * 11 / 2, CELL_SIZE * 2, CELL_SIZE * 2 / 3 });
	render_text("нажмите space чтобы продолжить", { CELL_SIZE * 5/2, CELL_SIZE * 7, CELL_SIZE * 6, CELL_SIZE/4 });
	render_text("нажмите e чтобы открыть рекорды", { CELL_SIZE * 5 / 2, CELL_SIZE * 15/2, CELL_SIZE * 6, CELL_SIZE / 4 });
	SDL_RenderPresent(renderer);
}

void Game::render_record_table()
{
	int th = 5;
	SDL_Rect rects[] = {
		{CELL_SIZE * 2, CELL_SIZE * 3, CELL_SIZE * 7, th},
		{CELL_SIZE * 2, CELL_SIZE * 8 - th, CELL_SIZE * 7, th},
		{CELL_SIZE * 2, CELL_SIZE * 3, th, CELL_SIZE * 5},
		{CELL_SIZE * 9 - th, CELL_SIZE * 3, th, CELL_SIZE * 5},
	};
	SDL_Rect rect = { CELL_SIZE * 2, CELL_SIZE * 3, CELL_SIZE * 7, CELL_SIZE * 5 };
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 50, 75, 255);
	SDL_RenderFillRects(renderer, rects, 4);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	std::ifstream file("records.txt");
	file.seekg(0);
	int n = 5;
	char line[6];
	std::string temp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			file.getline(line, 6);
			temp = line;
			render_text(num_to_str(stoi(temp)).c_str(), {CELL_SIZE * 3 + i*3*CELL_SIZE, 
				CELL_SIZE * 7/2+j*CELL_SIZE*4/5, CELL_SIZE * 2, CELL_SIZE / 3});
		}
	}
	file.close();
	render_text("нажмите space чтобы продолжить", { CELL_SIZE * 5 / 2, CELL_SIZE * 15 / 2, 
		CELL_SIZE * 6, CELL_SIZE / 4 });
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
			best_res = sort_file(player->get_score());
			render_endgame_box();
		}
	}
	else if (status == 1) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				status = 0;
				player->init();
				break;
			case SDLK_e:
				status = 1;
				render_record_table();
			default:
				break;
			}
		default:
			break;
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
	if (status == 0) {
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = { 0, 11 * CELL_SIZE, 11 * CELL_SIZE, 2 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 0, 10 * CELL_SIZE, 11 * CELL_SIZE, 2 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 0, CELL_SIZE, 11 * CELL_SIZE, 2 };
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		player->render();
		car_manager->render();
		render_text(num_to_str(player->get_score()).c_str(), {CELL_SIZE, CELL_SIZE*(MAP_SIZE + 1)+10, CELL_SIZE*3/2, CELL_SIZE*2/5});
		for (int i = 1; i <= player->get_lives(); i++) {
			rect = { 10*CELL_SIZE - i*CELL_SIZE*2/3, CELL_SIZE * (MAP_SIZE + 1)+10, CELL_SIZE/2, CELL_SIZE / 2 };
			SDL_RenderCopy(renderer, live_texture, NULL, &rect);
		}
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
