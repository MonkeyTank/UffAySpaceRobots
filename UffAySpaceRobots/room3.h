#pragma once

#include "helper.h"
#include "beer.h"
#include "crossword.h"
#include "numPad3.h"
#include "sudoku.h"
#include "flashback.h"
#include "esc.h"
#include "captcha.h"

#define CROSS_X 212
#define CROSS_Y 588
#define CROSS_WIDTH 142
#define CROSS_HEIGHT 148

#define NUMPAD3_X 1706
#define NUMPAD3_Y 533
#define NUMPAD3_WIDTH 106
#define NUMPAD3_HEIGHT 235

#define SUD_X 1473
#define SUD_Y 65
#define SUD_WIDTH 325
#define SUD_HEIGHT 192

#define BEER_X 1121
#define BEER_Y 42
#define BEER_WIDTH 162
#define BEER_HEIGHT 72

extern SDL_Rect ESC;
extern SDL_Rect ZERO;
extern SDL_Rect ENTER;

extern SDL_Rect ONE;
extern SDL_Rect TWO;
extern SDL_Rect THREE;

extern SDL_Rect FOUR;
extern SDL_Rect FIVE;
extern SDL_Rect SIX;

extern SDL_Rect SEVEN;
extern SDL_Rect EIGHT;
extern SDL_Rect NINE;

extern SDL_Rect A;
extern SDL_Rect B;
extern SDL_Rect C;

extern SDL_Rect D;
extern SDL_Rect E;
extern SDL_Rect F;

int room3(SDL_Window* mainWindow);