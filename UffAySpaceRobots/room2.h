#pragma once

#include "helper.h"
#include "colors.h"
#include "mensa.h"
#include "numPad2.h"
#include "things.h"
#include "flashback.h"
#include "esc.h"

#define COLOR_X 953
#define COLOR_Y 424
#define COLOR_WIDTH 540
#define COLOR_HEIGHT 53

#define MENSA_X 1175
#define MENSA_Y 742
#define MENSA_WIDTH 101
#define MENSA_HEIGHT 47

#define NUMPAD2_X 242
#define NUMPAD2_Y 242
#define NUMPAD2_WIDTH 54
#define NUMPAD2_HEIGHT 94

#define THING_X 804
#define THING_Y 662
#define THING_WIDTH 75
#define THING_HEIGHT 124

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

int room2(SDL_Window* mainWindow);