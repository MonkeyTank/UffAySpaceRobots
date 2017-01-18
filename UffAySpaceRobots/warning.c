#include "warning.h"

int warning(int num) {

	//create window
	SDL_Window *window;
	window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 900, SDL_WINDOW_BORDERLESS);

	//set window focus
	if (0 != SDL_SetWindowInputFocus(window)) {
		fprintf(stderr, "Window Focus could not be changend! SDL_Error: %s", SDL_GetError());
	}

	SDL_Surface *screen;
	SDL_Surface *text;

	char* warning1 = ReadFile("text/warning1.txt");
	char* warning2 = ReadFile("text/warning2.txt");

	SDL_Color text_color = { 255, 255, 255 };

	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		fprintf(stderr, "Init TTF failed! SDL_Error: %s", SDL_GetError());
	}

	// Load a font
	TTF_Font *font;
	font = TTF_OpenFont("FreeMonoBold.ttf", 50);
	if (font == NULL)
	{
		fprintf(stderr, "loading font failed! SDL_Error: %s", SDL_GetError());
	}

	// draw directly to the screen
	screen = SDL_GetWindowSurface(window);

	SDL_FillRect(screen, NULL, 0x000000);

	if (0 == num) {
		text = TTF_RenderText_Blended_Wrapped(font,
			warning1,
			text_color,
			700);
		SDL_BlitSurface(text, NULL, screen, NULL); 
		SDL_UpdateWindowSurface(window);

		SDL_Delay(2000);
	} 
	else if (1 == num) {
		text = TTF_RenderText_Blended_Wrapped(font,
			warning2,
			text_color,
			700);
		SDL_BlitSurface(text, NULL, screen, NULL); 
		SDL_UpdateWindowSurface(window);

		SDL_Delay(2000);
	}
	else {
		SDL_DestroyWindow(window);
		return 0;
	}

	SDL_DestroyWindow(window);
	return 1;
}