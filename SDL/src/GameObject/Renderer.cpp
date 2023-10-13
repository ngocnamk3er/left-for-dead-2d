#include"Renderer.h"
#include "Define.h"
Renderer::Renderer()
{
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;
}
	
Renderer::~Renderer()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
}
bool Renderer::Init()
{
	//Initialization flag
	bool success = true;
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
	//Create window
	gWindow = SDL_CreateWindow("Left 4 dead 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIDHT, SDL_WINDOW_SHOWN);
	// set icon
	SDL_Surface* icon = IMG_Load("Data/Textures/GUI/icon_game.png");
	if (icon == NULL)
	{
		printf("Could not load icon image: %s\n", SDL_GetError());
		//return;
	}
	// Set the icon for the window.
	SDL_SetWindowIcon(gWindow, icon);
	SDL_FreeSurface(icon);

	//set icon for mouse
	//SDL_Surface* cursorIcon = IMG_Load("Data/Textures/circular-target.png");
	//SDL_Cursor* customCursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	//if (customCursor == NULL)
	//{
	//	printf("Could not create custom cursor: %s\n", SDL_GetError());
	//}
	//SDL_SetCursor(customCursor);

	//// Free the icon image.
	//SDL_FreeSurface(cursorIcon);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create renderer for window ( tao doi tuong renderer de co the render on window)
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	return success;
}
SDL_Window* Renderer::GetWindow()
{
	return gWindow;
}
SDL_Renderer* Renderer::GetRenderer()
{
	return gRenderer;
}
void Renderer::SetWindow(SDL_Window* mWindow)
{
	gWindow = mWindow;
}

void Renderer::SetRenderer(SDL_Renderer* mRenderer)
{
	gRenderer = mRenderer;
}
