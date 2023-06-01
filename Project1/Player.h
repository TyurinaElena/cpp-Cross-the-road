#pragma once
#include <SDL.h>
#include <string>
#include "Car.h"

class Player {
public:
	Player(SDL_Renderer* ren); // конструктор
	void update(char direction); // перемещение в зависимости от direction
	void render(); // визуализация 
	void set_alive();
	bool get_alive();
	int get_score();
	int get_lives();
	bool is_colliding(Car& i_car); // коллизии
	const SDL_Rect get_rect(); // возвращает прямоугольник чуть меньше rect
	void reset(); // возвращение к исходному положению
	void set_reset_time(); 
	void init(); // сбрасывание значений до исходных при перезапуске игры

private:
	int x;
	int y;
	bool alive;
	int score;
	int path; // пройденный путь без учётаходов назад
	int lives;
	char curr_dir; // прошлое направление
	SDL_Texture* texture_u; // текстуры
	SDL_Texture* texture_r; // в зависимости
	SDL_Texture* texture_l; // от направления
	SDL_Texture* texture_d;
	SDL_Rect rect;
	SDL_Renderer* renderer;
	Uint32 reset_time;
	void reset_timer(); // запускает reset через некоторое время
};

