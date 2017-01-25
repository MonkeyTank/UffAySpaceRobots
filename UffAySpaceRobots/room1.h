#pragma once

#include "anagram.h"
#include "numbers.h"
#include "numPad1.h"
#include "labyrinth.h"
#include "flashback.h"
#include "esc.h"
#include "help.h"
#include "captcha.h"

#define ANA_X 1124
#define ANA_Y 795
#define ANA_WIDTH 97
#define ANA_HEIGHT 111

#define NUMPAD1_X 206
#define NUMPAD1_Y 213
#define NUMPAD1_WIDTH 81
#define NUMPAD1_HEIGHT 120

#define NUM_X 1112
#define NUM_Y 177
#define NUM_WIDTH 169
#define NUM_HEIGHT 137

#define LAB_X 1655
#define LAB_Y 117
#define LAB_WIDTH 183
#define LAB_HEIGHT 258

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

int room1(SDL_Window* mainWindow);