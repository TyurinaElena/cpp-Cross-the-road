#pragma once

#include <SDL.h>
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
private:
	void init();
	bool is_running;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
