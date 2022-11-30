// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// SDLHelpers.h
// This is the header file that contains all the SDL helper functions.
// ============================================================================
#ifndef SDLHELPERS_H
#define SDLHELPERS_H


#include "SDL.h"
#include "SDL_ttf.h"
#include <memory.h>
#include <math.h>

// define the most used colors
extern SDL_Color WHITE;
extern SDL_Color BLACK;
extern SDL_Color RED;
extern SDL_Color BLUE;
extern SDL_Color GREEN;
extern SDL_Color YELLOW;
extern SDL_Color ORANGE;
extern SDL_Color CYAN;
extern SDL_Color DCYAN;
extern SDL_Color PINK;
extern SDL_Color GREY;
extern SDL_Color LTGREY;
extern SDL_Color DKBLUE;
extern SDL_Color DKRED;
extern SDL_Color DKGREEN;


// ----------------------------------------------------------------
//  Name:           SDLPoint
//  Description:    draws a point on a surface
//  Arguments:      p_surface: surface to draw on
//                  x, y: coordinates
//                  p_color: the color of the point
//  Return Value:   None
// ----------------------------------------------------------------
void SDLPoint( SDL_Surface* p_surface, int x, int y, SDL_Color p_color );


// ----------------------------------------------------------------
//  Name:           SDLLine
//  Description:    draws a line on a surface
//  Arguments:      p_surface: surface to draw on
//                  x1, y1: first point
//                  x2, y2: second point
//                  p_color: color of the line
//  Return Value:   None
// ----------------------------------------------------------------
void SDLLine( SDL_Surface* p_surface, int x1, int y1, 
              int x2, int y2, SDL_Color p_color );


// ----------------------------------------------------------------
//  Name:           SDLArrowLine
//  Description:    draws a line, with optional arrowheads
//  Arguments:      p_surface: surface to draw on
//                  x1, y1: first point
//                  x2, y2: second point
//                  r1, r2: the radius of the points (see Appendx
//                          C in the book)
//                  arrow1, arrow2: determines if an arrow is drawn
//                  p_color: color of the line
//  Return Value:   None
// ----------------------------------------------------------------
void SDLArrowLine( SDL_Surface* p_surface, int x1, int y1, int x2, int y2,
                   int r1, int r2, bool arrow1, bool arrow2, SDL_Color p_color );


// ----------------------------------------------------------------
//  Name:           SDLBlit
//  Description:    draws a surface on another surface
//  Arguments:      p_source: surface to draw from
//                  p_dest: surface to draw on
//                  x, y: coordinates
//  Return Value:   None
// ----------------------------------------------------------------
void SDLBlit( SDL_Surface* p_source, SDL_Surface* p_dest, int x, int y );


// ----------------------------------------------------------------
//  Name:           SDLBox
//  Description:    draws a solid box on a surface
//  Arguments:      p_surface: surface to draw on
//                  x, y: coordinates
//                  width, height: width and height of the box
//                  p_color: color of the box
//  Return Value:   None
// ----------------------------------------------------------------
void SDLBox( SDL_Surface* p_surface, int x, int y, int width, int height, SDL_Color p_color );



#endif