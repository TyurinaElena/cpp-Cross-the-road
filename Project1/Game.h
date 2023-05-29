#pragma once

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "support.h"
//#include "Player.h"

class Game {
	
public:
	Game();
	//~Game();
	;
	void handle_events();
	void update(char direction);
	void render();
	void clean();
	bool get_is_running();
	short get_status();
private:
	int best_res;
	short status;
	bool is_running;
	SDL_Texture* live_texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	void init();
	void render_text(const char* text, SDL_Rect rect);
	void render_endgame_box();
};
