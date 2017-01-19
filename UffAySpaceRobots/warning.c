#include "warning.h"

int warning(int num) {

	//create window
	SDL_Window *window;
	window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 900, SDL_WINDOW_BORDERLESS);

	////set window focus
	//if (0 != SDL_SetWindowInputFocus(window)) {
	//	fprintf(stderr, "Window Focus could not be changend! SDL_Error: %s", SDL_GetError());
	//}

	//create renderer
	SDL_Renderer* rendererPopup;
	rendererPopup = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererPopup) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}
	SDL_Texture* warning = NULL;

	///////////////////////////////////////////////MUSIC//////////////////////////////////////////////////
	Mix_Chunk *alarm = NULL;
	Mix_Chunk *warn = NULL;

	//init sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//load music
	alarm = Mix_LoadWAV("sounds/alarm.wav");

	if (NULL == alarm) {
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	warn = Mix_LoadWAV("sounds/warning.wav");

	if (NULL == alarm) {
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}


	if (0 == num) {

		warning = loadImage("images/numpad/robotSkullWarning.bmp", rendererPopup);
		SDL_RenderClear(rendererPopup);
		SDL_RenderCopy(rendererPopup, warning, NULL, NULL);
		SDL_RenderPresent(rendererPopup);
		Mix_PlayChannel(-1, warn, 0);

		SDL_Delay(3000);
	} 
	else if (1 == num) {
		warning = loadImage("images/numpad/robotSkullWarning2.bmp", rendererPopup);
		SDL_RenderClear(rendererPopup);
		SDL_RenderCopy(rendererPopup, warning, NULL, NULL);
		SDL_RenderPresent(rendererPopup);
		Mix_PlayChannel(-1, warn, 0);

		SDL_Delay(3000);
	}
	else {
		warning = loadImage("images/numpad/robotSkullAlarm.bmp", rendererPopup);
		SDL_RenderClear(rendererPopup);
		SDL_RenderCopy(rendererPopup, warning, NULL, NULL);
		SDL_RenderPresent(rendererPopup);
		Mix_PlayChannel(-1, alarm, 0);

		SDL_Delay(3000);
		
		Mix_FreeChunk(alarm);
		Mix_FreeChunk(warn);
		alarm = NULL;
		warn = NULL;
		SDL_DestroyTexture(warning);
		SDL_DestroyRenderer(rendererPopup);
		SDL_DestroyWindow(window);

		return 0;
	}
	Mix_FreeChunk(alarm);
	Mix_FreeChunk(warn);
	alarm = NULL;
	warn = NULL;
	SDL_DestroyTexture(warning);
	SDL_DestroyRenderer(rendererPopup);
	SDL_DestroyWindow(window);
	return 1;
}