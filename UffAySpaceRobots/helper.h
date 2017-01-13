#pragma once
#include "main.h"

SDL_Texture* loadImage(char* path, SDL_Renderer* renderer);
SDL_Texture* loadColorKeyImage(char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
void render(int x, int y, SDL_Texture* tex, SDL_Rect* clip, SDL_Renderer* renderer);