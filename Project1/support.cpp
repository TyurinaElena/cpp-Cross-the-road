#include <fstream>
#include <iostream>
#include "support.h"

int count_digit(int number) {
	int count = 0;
	while (number != 0) {
		number = number / 10;
		count++;
	}
	return count > 0 ? count : 1;
}
std::string num_to_str(int num)
{
	int count = count_digit(num);
	std::string str = std::string(5 - count, '0');
	str += std::to_string(num);
	return str;
}

SDL_Texture* load_texture(const char* filename, SDL_Renderer* ren, int r, int g, int b) {
	SDL_Texture* texture;
	SDL_Surface* img = SDL_LoadBMP(filename);
	SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, r, g, b));
	texture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	return texture;
}

int sort_file(int score) {
	std::fstream file;
	file.open("records.txt", std::fstream::in | std::fstream::out);
	if (file.is_open()) {
		std::cout << "file is opened" << std::endl;
	}
	
	int n = 11;
	std::string lines[11];
	char line[6];
	std::string temp;
	for (int i = 0; i < n; i++) {
		if (i == n-1) {
			lines[i] = std::to_string(score);
		}
		else {
			file.getline(line, 6);
			lines[i] = line;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (std::stoi(lines[j]) < std::stoi(lines[j + 1]))
			{
				temp = lines[j];
				lines[j] = lines[j + 1];
				lines[j + 1] = temp;
			}
		}
	}
	file.seekg(0);
	file.write("", 0);
	for (int i = 0; i < n-1; i++) {
		file << lines[i] << std::endl;
		std::cout << lines[i] << std::endl;
	}
	file.close();
	return stoi(lines[0]);
}