#pragma once
#include <array>
#include <list>
#include "Car.h"
#include "globals.h"
#include "Player.h"
class CarManager
{
private:
	std::array<std::list<Car>, MAP_SIZE - 1> Cars;
	SDL_Renderer* renderer;
public:
	CarManager(SDL_Renderer* renderer);
	void create_level();
	void add_cars(int i, short speed, short direction);
	void update();
	void render();
};

