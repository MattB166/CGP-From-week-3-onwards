#include <iostream>
#include "SDL.h"

SDL_Window* g_sdlWindow;
SDL_Renderer* g_sdlRenderer;
const Uint8* keystate;

SDL_Texture* LoadTexture(const char* filename)
{
	//load door bmp as a surface
	SDL_Surface* image = SDL_LoadBMP(filename);
	if (image == nullptr)
	{
		std::cout << "Failed to load " << filename << ". SDL ERROR: " << SDL_GetError() << std::endl;
	}

	//convert surface of loaded bmp into a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_sdlRenderer, image);
	if (texture == nullptr)
	{
		std::cout << "Failed to create texture from surface" << std::endl;
	}

	//free surface
	SDL_FreeSurface(image);
	
	  
	return texture;
}








int main(int argc, char* argv[])
{
	
	//initialise all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL. SDL error: " << SDL_GetError() << std::endl; 
	}
	
	//create a window with specified name, anywhere on screen, 800x600 pixel size and no SDL_windowflags.	

	//flag testing 
	int iwindowflag = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN_DESKTOP;
	 g_sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, NULL);

	//error checking
	if (g_sdlWindow == nullptr)
	{
		std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
	}


	//Create a rendering context for our window. Enable Hardware acceleration with the SLD_RENDERER_ACCELERATED FLAG

	 g_sdlRenderer = SDL_CreateRenderer(g_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (g_sdlRenderer == nullptr)
	{
		std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl; 

    }

	//load door as a surface
	SDL_Surface* image = SDL_LoadBMP("assets/door.bmp");
	////error checking
	if (image == nullptr)
	{
		std::cout << "Failed to load image" << SDL_GetError();
	}

	SDL_Texture* doorTexture = LoadTexture("assets/door.bmp");

	SDL_Surface* image2 = SDL_LoadBMP("assets/dig10k_penguin.bmp");
	if (image2 == nullptr)
	{
		std::cout << "Failed to load image" << SDL_GetError();
	}
	
	SDL_Texture* penguinTexture = LoadTexture("assets/dig10k_penguin.bmp");
	
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_sdlRenderer, image);
	//error checking
	if (texture == nullptr)
	{
		std::cout << "Failed to create texture from surface. SDL ERROR: " << SDL_GetError() << std::endl;
	}

	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(g_sdlRenderer, image2);
	if (texture2 == nullptr)
	{
		std::cout << "Failed to create texture from surface. SDL ERROR: " << SDL_GetError() << std::endl;
	}

	
	SDL_Texture* MagicTexture = SDL_CreateTexture(g_sdlRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, 64, 64);

	SDL_SetRenderTarget(g_sdlRenderer, MagicTexture);

	SDL_SetRenderDrawColor(g_sdlRenderer, 0, 255, 0, 255);
	SDL_Rect BoxDST = { 16,16,32,32 };
	SDL_RenderFillRect(g_sdlRenderer, &BoxDST);
	
	SDL_SetRenderTarget(g_sdlRenderer, NULL);
	
	bool keepRunning = true;
	
	int MagicX = 80, MagicY = 80; 
	int MagicWidth, MagicHeight;
	
	//SDL_QueryTexture(MagicTexture, NULL, NULL, &MagicWidth, &MagicHeight);

	

	
	
	while(keepRunning)
	{
		SDL_Event sdlEvent;   //logs event queue  
		while (SDL_PollEvent(&sdlEvent))
		{
			/*keystate = SDL_GetKeyboardState(NULL);
			* if(keystate[SDL_SCANCODE_RIGHT])
			* ++MagicX 
			* 
			if(keystate)*///start of keystate function 
			
			
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				keepRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					keepRunning = false;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_a || sdlEvent.key.keysym.sym == SDLK_LEFT)
				{
					--MagicX;
					std::cout << " X value of magic texture is: " << MagicX << std::endl; 
				}
				else if (sdlEvent.key.keysym.sym == SDLK_d || sdlEvent.key.keysym.sym == SDLK_RIGHT)
				{
					++MagicX;
					std::cout << " X value of magic texture is: " << MagicX << std::endl;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_w || sdlEvent.key.keysym.sym == SDLK_UP)
				{
					--MagicY;
					std::cout << "Y Value of magic texture is: " << MagicY << std::endl; 
				}
				else if (sdlEvent.key.keysym.sym == SDLK_s || sdlEvent.key.keysym.sym == SDLK_DOWN)
				{
					++MagicY;
					std::cout << "Y Value of magic texture is: " << MagicY << std::endl;
				}

				break;
			case SDL_KEYUP:
				if (sdlEvent.key.keysym.sym == SDLK_w || sdlEvent.key.keysym.sym == SDLK_UP)
				{
					std::cout << "Up pressed" << std::endl; 
				}
				
				
				break;
			case SDL_MOUSEBUTTONUP:
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					std::cout << "Button Click" << std::endl; 
					int x;
					int y;
					SDL_GetMouseState(&x, &y); 
					std::cout << "X value is: " << x << "," << " Y Value is: " << y << std::endl;
				}
				break;
			case SDL_MOUSEMOTION:
				std::cout << "Current Mouse Position is: " << sdlEvent.motion.x << " , " << sdlEvent.motion.y << std::endl; 
				
				MagicX = sdlEvent.motion.x;
				MagicY = sdlEvent.motion.y; 
				break; 
				

			default:
				break;
			}
		}
		
		SDL_SetRenderDrawColor(g_sdlRenderer,19,47,209,255);
		SDL_RenderClear(g_sdlRenderer);
		
		//create destination for where the image will be copied{x,y,w,h}
		SDL_Rect destinationRect{ 25,25,16,16 };
		SDL_Rect destinationRect2{ 50,50,20,20 };
		SDL_Rect destinationRect3{ MagicX -10, MagicY -10,20,20 };
		
	
		//copy texture onto rendering target
		SDL_RenderCopy(g_sdlRenderer, doorTexture, NULL, &destinationRect);
		SDL_RenderCopy(g_sdlRenderer, penguinTexture, NULL, &destinationRect2);
		SDL_RenderCopy(g_sdlRenderer, MagicTexture, NULL, &destinationRect3);

		
		
		//update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);
		SDL_Delay(16);

	}
	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);



	//std::cout << "Hello World" << std::endl; 
	
	//getchar();

	//clean up
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(penguinTexture);
	SDL_DestroyRenderer(g_sdlRenderer);
	SDL_DestroyWindow(g_sdlWindow);
	SDL_Quit(); 

	return 0;
}