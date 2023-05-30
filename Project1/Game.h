#pragma once

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "support.h"

class Game {
	
public:
	Game(); //конструктор
	void handle_events();  //обработка пользовательских событий
	void update(char direction); //обновление всех объектов игры
	void render(); //отрисовка
	void clean();  //очищение динамической пам€ти после закрыти€ окна
	bool get_is_running();
	short get_status();
private:
	int best_res; // рекорд дл€ вывода на экран в конце
	short status; //отвечает за состо€ние игры
	bool is_running;
	SDL_Texture* live_texture; // текстура "сердца"
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	void init(); // вызываетс€ при создании экземпл€ра
	void render_text(const char* text, SDL_Rect rect); 
	void render_endgame_box(); //визуализаци€ окна проигрыша
	void render_record_table(); //визуализаци€ таблицы рекордов
};
