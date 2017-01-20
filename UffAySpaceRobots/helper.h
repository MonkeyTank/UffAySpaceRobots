#pragma once
#include "main.h"

SDL_Texture* loadImage(char* path, SDL_Renderer* renderer);
SDL_Texture* loadColorKeyImage(char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
void render(int x, int y, SDL_Texture* tex, SDL_Rect* clip, SDL_Renderer* renderer);
int XYInRect(const SDL_Rect rect, int x, int y);
char* addToString(int counter, char* fullString);
char* ReadFile(char *filename);
SDL_Event getClick(SDL_Event mouse);
SDL_Event getKey(SDL_Event key);