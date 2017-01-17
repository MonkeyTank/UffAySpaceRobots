#include "flashback.h"

void flashback() {

	SDL_Surface *screen; // even with SDL2, we can still bring ancient code back
	SDL_Window *window;
	SDL_Surface *text;

	char* fullString = ReadFile("text/flashback.txt");
	char* string; 
	int cnt = 0;

	SDL_Init(SDL_INIT_VIDEO); // init video

							  // create the window like normal
	window = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_BORDERLESS);

	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		fprintf(stderr, "Init TTF failed! SDL_Error: %s", SDL_GetError());
	}

	// Load a font
	TTF_Font *font;
	font = TTF_OpenFont("FreeMonoBold.ttf", 24);
	if (font == NULL)
	{
		fprintf(stderr, "loading font failed! SDL_Error: %s", SDL_GetError());
	}

	// draw directly to the screen
	screen = SDL_GetWindowSurface(window);

	SDL_Event end;

	while (1) {

		string = addToString(cnt, fullString);
		cnt++;

		//write text to surface
		SDL_Color text_color = { 255, 255, 255 };
		text = TTF_RenderText_Blended_Wrapped(font,
			string,
			text_color,
			800);

		// let's just show some classic code for reference

		SDL_BlitSurface(text, NULL, screen, NULL); // blit it to the screen
		

		// this works just like SDL_Flip() in SDL 1.2
		SDL_UpdateWindowSurface(window);

		// show image for 80 ms
		SDL_Delay(80);

		SDL_PollEvent(&end);
		if (SDL_KEYDOWN == end.type) {
			break;
		}
		
	}
	SDL_FreeSurface(text);
	SDL_DestroyWindow(window);
}