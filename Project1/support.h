#pragma once
# include <string>
#include <SDL.h>


int count_digit(int number);
std::string num_to_str(int num);

SDL_Texture* load_texture(const char* filename, SDL_Renderer* ren, int r, int g, int b);
int sort_file(int score);