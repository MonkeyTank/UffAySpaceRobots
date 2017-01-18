#include "helper.h"
//////////////////////////////////////helper function to create untouched texture from image/////////////////////////////////////
SDL_Texture* loadImage(char* path, SDL_Renderer* renderer) {

	SDL_Surface* imagetmp;
	imagetmp = SDL_LoadBMP(path);
	if (imagetmp == NULL)
		{
			fprintf(stderr,
				"Unable to load image %s! SDL Error: %s\n",
				path,
				SDL_GetError());
		}

	//Create texture from surface pixels
	SDL_Texture* newTexture;
	newTexture = SDL_CreateTextureFromSurface(renderer, imagetmp);
	if (newTexture == NULL)
	{
		fprintf(stderr,
			"Unable to create texture from %s! SDL Error: %s\n",
			path,
			SDL_GetError());
	}

	//Für jedes Bild wird Speicher allokiert der wieder frei
	// gegeben werden muss. Dies tut SDL_FreeSurface!!!!!
	SDL_FreeSurface(imagetmp);
	return newTexture;
}

//helper function to create texture with color keying from image
SDL_Texture* loadColorKeyImage(char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {

	SDL_Surface* imagetmp;
	imagetmp = SDL_LoadBMP(path);
	if (imagetmp == NULL)
	{
		fprintf(stderr,
			"Unable to load image %s! SDL Error: %s\n",
			path,
			SDL_GetError());
	}

	//Color Keying

	if (0 != SDL_SetColorKey(imagetmp, SDL_TRUE, SDL_MapRGB(imagetmp->format, r, g, b)))
	{
		fprintf(stderr,
			"Unable to use color keying %s! SDL Error: %s\n",
			path,
			SDL_GetError());
	}
	//Create texture from surface pixels
	SDL_Texture* newTexture;
	newTexture = SDL_CreateTextureFromSurface(renderer, imagetmp);
	if (newTexture == NULL)
	{
		fprintf(stderr,
			"Unable to create texture from %s! SDL Error: %s\n",
			path,
			SDL_GetError());
	}

	//Für jedes Bild wird Speicher allokiert der wieder frei
	// gegeben werden muss. Dies tut SDL_FreeSurface!!!!!
	SDL_FreeSurface(imagetmp);
	return newTexture;
}

void render(int x, int y, SDL_Texture* tex, SDL_Rect* clip, SDL_Renderer* renderer){

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, 0, 0 };
	
	//Set rendering dimensions to clip dimensions
	if (clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	else abort();;

	//Render to screen       /--------/ /TargetAreaOnScreen/
	SDL_RenderCopy(renderer, tex, NULL, &renderQuad);
}

//test if click is on button or not
//x & y are position markers of mouse pointer
int XYInRect(const SDL_Rect rect, int x, int y) {

	if (x > rect.x && x < (rect.x + rect.w)
		&& y > rect.y && y < (rect.y + rect.h)) {
		return 1;
	}
	else {
		return 0;
	}

}

//set values for rect
void setRect(SDL_Rect rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

//add one char to string each time the function is called
char* addToString(int counter, char* fullString) {

	int newline = strlen(fullString) % 55;
	int k = 0;

	char* string = (char*)malloc((counter + newline + 1) * sizeof(char));

	for (int i = 0; i < counter; i++) {

		if (!(k % 55)) {
			string[k] = '\n';
			k++;
		}
		string[k] = fullString[i];
		k++;
	}

	string[counter] = '\0';

	return string;
}

char* ReadFile(char *filename)
{
	char *buffer = NULL;
	int string_size, read_size;
	FILE *handler;
	errno_t err;
	err = fopen_s(&handler, filename, "r");

	if (handler)
	{
		// Seek the last byte of the file
		fseek(handler, 0, SEEK_END);

		// Offset from the first to the last byte, or in other words, filesize
		string_size = ftell(handler);

		// go back to the start of the file
		rewind(handler);

		// Allocate a string that can hold it all
		buffer = (char*)malloc(sizeof(char) * (string_size + 1));

		// Read it all in one operation
		read_size = fread(buffer, sizeof(char), string_size, handler);

		// fread doesn't set it so put a \0 in the last position
		// and buffer is now officially a string
		buffer[string_size] = '\0';

		if (string_size != read_size)
		{
			// Something went wrong, throw away the memory and set
			// the buffer to NULL
			free(buffer);
			buffer = NULL;
		}

		// Always remember to close the file.
		fclose(handler);
	}

	return buffer;
}

SDL_Event getClick(SDL_Event mouse) {

	while (SDL_MOUSEBUTTONDOWN != mouse.type) {
		SDL_PollEvent(&mouse);
	}
	return mouse;
}