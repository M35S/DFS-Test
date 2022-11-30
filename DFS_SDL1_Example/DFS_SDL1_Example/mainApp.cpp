// ============================================================================
// Direction-Table Graph Demo
// ============================================================================
// C++ libs
#include <iostream>
#include <memory>

// SDL libs
#include "SDL.h"
#include "SDLHelpers.h"

// Custom libs
#include "Array2D.h"
#include "Bitvector.h"

// C lib
#include <stdlib.h>

// ============================================================================
//  Global Constants
// ============================================================================
const char PROGRAM_NAME[] = "Game Demo Test:  Direction Table Graph Demo";
const int WIDTH = 800;
const int HEIGHT = 600;
const int ROOMS = 16;
const int DIRECTIONS = 4;


// ============================================================================
//  Global Variables
// ============================================================================

// pixel offsets of each direction as tile = 64px. 
int directionarray[4][2] = { { 0, -64 }, // Up
{ 64, 0 }, // Right
{ 0, 64 }, // Down
{ -64, 0 } }; // Left


// ============================================================================
//  Functions
// ============================================================================

// -------------- Override "new" operator ---------------- //

void* operator new[](size_t size) // ** This is selected
{
	std::cout << "Allocating " << size << " bytes\n";

	return malloc(size);
}

// ------------------- Override "delete" operator ----------------- //

void operator delete[](void* memory) // ** This is selected
{
	std::cout << "Freed.\n ";

	free(memory);
}

// ------------------- Game Functions -------------------- //
void DrawMap(SDL_Surface* g_window, SDL_Surface* g_tile, Bitvector &g_marked,
int p_room, int p_x, int p_y, Array2D<int> &g_map)
{
	// draw and mark the tile.
	SDLBlit(g_tile, g_window, p_x, p_y); // Draw single tile
	g_marked.Set(p_room, true); // Mark room's bit value
	int room;

	// loop through each direction
	int direction;
	for (direction = 0; direction < DIRECTIONS; direction++)
	{
		room = g_map.Get(p_room, direction);
		if (room != -1)
		{
			if (g_marked[room] == false)
			{
				DrawMap(g_window, g_tile, g_marked, room,
					p_x + directionarray[direction][0],
					p_y + directionarray[direction][1],
					g_map);
			}
		}
	}
}


void InitialiseMap(Array2D<int> &g_map)
{
	int room, direction;

	// first clear all the rooms.
	for (room = 0; room < ROOMS; room++)
	{
		for (direction = 0; direction < DIRECTIONS; direction++)
		{
			g_map.Get(room, direction) = -1;
		}
	}

	// Assign Room exits
	g_map.Get(0, 0) = 1; // Room 0

	g_map.Get(1, 0) = 3; // Room 1
	g_map.Get(1, 1) = 2;
	g_map.Get(1, 2) = 0;

	g_map.Get(2, 3) = 1; // Room 2

	g_map.Get(3, 0) = 4; // Room 3
	g_map.Get(3, 2) = 1;

	g_map.Get(4, 1) = 5; // Room 4
	g_map.Get(4, 2) = 3;
	g_map.Get(4, 3) = 7;

	g_map.Get(5, 1) = 6; // Room 5
	g_map.Get(5, 3) = 4;

	g_map.Get(6, 3) = 5; // Room 6

	g_map.Get(7, 1) = 4; // Room 7
	g_map.Get(7, 3) = 8;

	g_map.Get(8, 1) = 7; // Room 8
	g_map.Get(8, 3) = 9;

	g_map.Get(9, 1) = 8; // Room 9
	g_map.Get(9, 2) = 10;
	g_map.Get(9, 3) = 14;

	g_map.Get(10, 0) = 9; // Room 10
	g_map.Get(10, 2) = 11;

	g_map.Get(11, 0) = 10; // Room 11
	g_map.Get(11, 1) = 12;
	g_map.Get(11, 2) = 13;
	g_map.Get(11, 3) = 15;

	g_map.Get(12, 3) = 11; // Room 12

	g_map.Get(13, 0) = 11; // Room 13

	g_map.Get(14, 1) = 9; // Room 14

	g_map.Get(15, 1) = 11; // Room 15


}

int main(int argc, char* argv[])
{
	// this is the main window for the framework
	SDL_Surface* g_window = 0;

	// the tile and player graphics
	SDL_Surface* g_tile;
	SDL_Surface* g_player;

	// the current room of the player.
	int g_room = 0;

	// the map
	Array2D<int> g_map(ROOMS, DIRECTIONS);

	// the bitvector which determines which rooms are marked
	Bitvector g_marked(ROOMS);

	// declare coordinates.
	int x, y;

	// declare event holder
	SDL_Event event;

	// initialise the map
	InitialiseMap(g_map);

	// initialize the video system.
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_WM_SetCaption(PROGRAM_NAME, 0);

	// set our at exit function
	atexit(SDL_Quit);

	// set the video mode.
	g_window = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_ANYFORMAT);

	// Load bmp's and set the colour key
	g_tile = SDL_LoadBMP("floorTile.bmp");
	SDL_SetColorKey(g_tile, SDL_SRCCOLORKEY,
		SDL_MapRGB(g_tile->format, 0, 0, 0));
	g_player = SDL_LoadBMP("bat.bmp");
	SDL_SetColorKey(g_player, SDL_SRCCOLORKEY,
		SDL_MapRGB(g_player->format, 255, 0, 255));

	while (1)
	{
		//look for an event
		if (SDL_PollEvent(&event))
		{
			//an event was found
			if (event.type == SDL_QUIT)
				break;
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				// get the mouse state.
				SDL_GetMouseState(&x, &y);

			}
			if (event.type == SDL_KEYDOWN)
			{
				// a key was pressed.
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					// if ESC was pressed, quit the program.
					SDL_Event quit;
					quit.type = SDL_QUIT;
					SDL_PushEvent(&quit);
				}

				x = -1;

				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					x = 0;
					break;
				case SDLK_RIGHT:
					x = 1;
					break;
				case SDLK_DOWN:
					x = 2;
					break;
				case SDLK_LEFT:
					x = 3;
					break;
				}

				// move if requested.
				if (x != -1)
				{
					if (g_map.Get(g_room, x) != -1)
						g_room = g_map.Get(g_room, x);
				}
			}

		}   // end event loop.


		// clear the screen to black.
		SDL_FillRect(g_window, NULL, SDL_MapRGB(g_window->format, 0, 0, 0));

		// clear bit vector
		g_marked.ClearAll();

		// draw the tiles using DFS
		DrawMap(g_window, g_tile, g_marked, g_room, WIDTH / 2 - 32, HEIGHT / 2 - 32, g_map);

		// draw the window and the player on top of the tiles  
		SDLBlit(g_player, g_window, WIDTH / 2 - 28, HEIGHT / 2 - 32);

		// update the entire window.
		SDL_UpdateRect(g_window, 0, 0, 0, 0);
	}

	// done
	return 0;
}