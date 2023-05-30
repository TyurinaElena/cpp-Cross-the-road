#include <stdlib.h>
#include <time.h>
#include "CarManager.h"
#include <SDL.h>

CarManager::CarManager(SDL_Renderer* ren) {
	renderer = ren;
	create_level();
}
void CarManager::create_level() {
	short direction, speed, size;
	short cells_to_skip = 0;
	bool condition;
	srand(time(NULL));
	for (int i = 1; i < MAP_SIZE; i++) {
		speed = SPEED_MIN + rand() % (SPEED_MAX - SPEED_MIN + 1);
		if (i > 1) {
			while (!Cars[i-2].empty() && speed == Cars[i - 2].front().get_speed()) {
				speed = SPEED_MIN + rand() % (SPEED_MAX - SPEED_MIN + 1);
			}
		}
		direction = rand() % 2;
		if (direction == 0) { direction = -1; }
		for (int j = 0; j <= MAP_SIZE; j++) {
			if (cells_to_skip>0) {
				cells_to_skip--;
				continue;
			}
			j == 0 ? condition = 1 : condition = rand() % 2;
			if (condition) {
				size = 1 + rand() % (3);
				if (direction == 1) {
					Cars[i - 1].push_front(Car(j, i, size, speed, direction, renderer));
				}
				else {Cars[i - 1].push_back(Car(j, i, size, speed, direction, renderer));}
				cells_to_skip = size + 4;
			}
		}
	}
}
void CarManager::add_cars(int i, short speed, short direction) {
	bool condition;
	short size;
	condition = rand() % 2;
	if (condition) {
		size = 1 + rand() % (3);
		if (direction == 1) {
			Cars[i - 1].push_back(Car(START_POINT_R, i, size, speed, direction, renderer));
		}
		else {
			Cars[i - 1].push_back(Car(START_POINT_L, i, size, speed, direction, renderer));
		}
	}
}
void CarManager::update(Player& i_player) {
	for (int i = 0; i < MAP_SIZE-1; i++) {
		if (!Cars[i].empty()) {
			for (Car& car : Cars[i]) {
				car.update();
				if (i_player.is_colliding(car)) {
					i_player.set_alive();
					i_player.set_reset_time();
				}
			}
			if (Cars[i].front().get_direction() == 1) {
				if (Cars[i].front().get_x() > (MAP_SIZE + 1) * CELL_SIZE) {
					Cars[i].pop_front();
				}
				if (Cars[i].back().get_x() > 4*CELL_SIZE) {
					add_cars(i+1, Cars[i].back().get_speed(), Cars[i].back().get_direction());
				}
			}
			else {
				if (Cars[i].front().get_x() < -4 * CELL_SIZE) {
					Cars[i].pop_front();
				}
				if (Cars[i].back().get_x() < (MAP_SIZE-4)*CELL_SIZE) {
					add_cars(i + 1, Cars[i].back().get_speed(), Cars[i].back().get_direction());
				}
			}
		}
	}
}
void CarManager::render() {
	for (int i = 0; i < MAP_SIZE - 1; i++) {
		if (!Cars[i].empty()) {
			for (Car& car : Cars[i]) { car.render(); }
		}
	}
}
