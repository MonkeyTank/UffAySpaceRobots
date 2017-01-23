#include "flashback.h"

void flashback(char* path) {

	//////////////////////////////////////initialize music, video and text/////////////////////////////////////

	SDL_Surface *screen; 
	SDL_Window *window;
	SDL_Surface *text;
	SDL_Rect paper = { 560, 140, 800, 800 };

	char *fullString = ReadFile(path);
	char *string; 
	int cnt = 0;
	int quit = 1;

	Mix_Music *typing = NULL;

	//init sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { 
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());  
	}

	//load music
	typing = Mix_LoadMUS("sounds/typing.mp3");
	if (NULL == typing) {
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_PlayMusic(typing, -1);

	// init video
	SDL_Init(SDL_INIT_VIDEO); 

	// create the window
	
	window = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_BORDERLESS);

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

	//////////////////////////////////////render Text on Screen/////////////////////////////////////
	while (1) {
		
		while(SDL_PollEvent(&end));

		string = addToString(cnt, fullString);
		cnt++;

		//write text to surface
		SDL_Color text_color = { 255, 255, 255 };
		text = TTF_RenderText_Blended_Wrapped(font,
			string,
			text_color,
			1000);


		SDL_FillRect(screen, NULL, 0x000000); 		//overwrite screen in black
		SDL_BlitSurface(text, NULL, screen, &paper);	// blit it to the screen
		

		SDL_UpdateWindowSurface(window);

		// show image for 60 ms
		SDL_Delay(60);


		//////////////////////////////////////Skip text on tap any key//////////////////////////////////
		
		if (SDL_KEYDOWN == end.type || '\0' == fullString[cnt]) {

			Mix_HaltMusic();
			end.type = 0;
			SDL_FillRect(screen, NULL, 0x000000);

			text = TTF_RenderText_Blended_Wrapped(font,
				fullString,
				text_color,
				1000);
			SDL_BlitSurface(text, NULL, screen, &paper); 
			SDL_UpdateWindowSurface(window);
			Mix_HaltMusic();

 			while (1) {
				while(SDL_PollEvent(&end));
 				if (SDL_KEYDOWN == end.type) {
					quit = 0;
					break;
				}
			}
			break;	
		}
	}

	Mix_HaltMusic();
	Mix_FreeMusic(typing);
	typing = NULL;
	SDL_FreeSurface(text);
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
}