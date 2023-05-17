#include <SDL.h>
//#include <SDL2/SDL_image.h>
#include "Game.h"
#include "globals.h"

Game* game = nullptr;

int main(int argc, char ** argv) {

	Uint32 frame_start;
	int frame_time;

	game = new Game();
	game->init();
	while (game->get_is_running()) {

		frame_start = SDL_GetTicks();
		
		game->handle_events();
		game->update();
		game->render();

		frame_time = SDL_GetTicks() - frame_start;
		if (FRAME_DELAY > frame_time) {
			SDL_Delay(FRAME_DELAY - frame_time);
		}
	}
	game->clean();
	return 0;
}
