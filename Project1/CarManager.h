#pragma once
#include <array>
#include <list>
#include "Car.h"
#include "globals.h"
#include "Player.h"
class CarManager
{
private:
	std::array<std::list<Car>, MAP_SIZE - 1> Cars; // хранение экземпл€ров Car
	SDL_Renderer* renderer;
public:
	CarManager(SDL_Renderer* renderer); // конструктор
	void create_level(); //генераци€ положени€ машин в начале игры
	void add_cars(int i, short speed, short direction); // добавление новой машины в р€д
	void update(Player& i_player); //обновление машин, распознавание коллизий
	void render(); // визуализаци€
};

