// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// SDLHelpers.cpp
// This is the source file that contains all the SDL helper functions.
// ============================================================================
#include "SDLHelpers.h"



// define the most used colors
SDL_Color WHITE = { 255, 255, 255, 0 };
SDL_Color BLACK = { 0, 0, 0, 0 };
SDL_Color RED   = { 255, 0, 0, 0 };
SDL_Color BLUE  = { 0, 0, 255, 0 };
SDL_Color GREEN = { 0, 255, 0, 0 };
SDL_Color YELLOW = { 255, 255, 0, 0 };
SDL_Color CYAN   = { 0, 255, 255, 0 };
SDL_Color PINK   = { 255, 0, 127, 0 };
SDL_Color ORANGE = { 255, 127, 0, 0 };
SDL_Color DCYAN  = { 0, 127, 127, 0 };
SDL_Color GREY   = { 63, 63, 63, 0 };
SDL_Color LTGREY = { 191, 191, 191, 0 };
SDL_Color DKBLUE = { 0, 0, 127, 0 };
SDL_Color DKRED  = { 127, 0, 0, 0 };
SDL_Color DKGREEN = { 0 ,127, 0, 0 };


// ----------------------------------------------------------------
//  Name:           SDLPoint
//  Description:    draws a point on a surface
//  Arguments:      p_surface: surface to draw on
//                  x, y: coordinates
//                  p_color: the color of the point
//  Return Value:   None
// ----------------------------------------------------------------
void SDLPoint( SDL_Surface* p_surface, int x, int y, SDL_Color p_color ) 
{
    Uint32 col = SDL_MapRGB( p_surface->format, p_color.r, p_color.g, p_color.b );
    static SDL_Rect rec;
    rec.w = 1;
    rec.h = 1;
    rec.x = x;
    rec.y = y;
    SDL_FillRect( p_surface, &rec, col );
}


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
           int x2, int y2, SDL_Color p_color ) 
{
    // lock the surface
    SDL_LockSurface( p_surface );

    // find distances of the line
    int x;
    float y;
    int dx = x2 - x1;
    int dy = y2 - y1;
    float m;

    // if the line is more wide than tall...
    if( abs(dx) > abs(dy) )
    {
        // check to see if dx is negative. If so, 
        // then swap the coordinates.
        if( dx < 0 )
        {
            dx = -dx;
            dy = -dy;
            x = x1;
            x1 = x2;
            x2 = x;
            x = y1;
            y1 = y2;
            y2 = x;
        }

        // find the slope and the beginning y coordinate
        m = (float)dy / (float)dx;
        y = (float)y1;

        // draw a point for each x
        for( x = x1; x <= x2; x++ )
        {
            SDLPoint( p_surface, x, (int)y, p_color );
            y += m;
        }
    }
    else
    {
        // check to see if dy is negative. If so, 
        // then swap the coordinates.
        if( dy < 0 )
        {
            dx = -dx;
            dy = -dy;
            x = x1;
            x1 = x2;
            x2 = x;
            x = y1;
            y1 = y2;
            y2 = x;
        }

        
        // find the slope and the beginning x coordinate
        m = (float)dx / (float)dy;
        y = (float)x1;


        // draw a point for each y
        for( x = y1; x <= y2; x++ )
        {
            SDLPoint( p_surface, (int)y, x, p_color );
            y += m;
        }
    }

    // unlock the surface
    SDL_UnlockSurface( p_surface );
}


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
                int r1, int r2, bool arrow1, bool arrow2, SDL_Color p_color )
{
    int tx1, ty1, tx2, ty2;

    // calculate distance from each point
    float dx = (float)(x2 - x1);
    float dy = (float)(y2 - y1);
    float d = (float)sqrt( dx * dx + dy * dy );

    // calculate the normal vector (dx, dy), and
    // the angle of that vector, a.
    float a;
    dx /= d;
    dy /= d;
    a = (float)acos( dx );

    // if dy is less than 0, then subtract the angle from 2PI
    if( dy < 0 )
        a = 6.2832f - a;

    // calculate new coordinates (tx1,ty1) and (tx2,ty2) that are
    // r1 and r2 units away from the original points, along the
    // same line.
    tx1 = x1 + (int)((float)cos(a) * (float)r1);
    ty1 = y1 + (int)((float)sin(a) * (float)r1);
    tx2 = x2 + (int)((float)cos(a+3.1416f) * (float)r2);
    ty2 = y2 + (int)((float)sin(a+3.1416f) * (float)r2);

    // draw the line with the new coordinates
    SDLLine( p_surface, tx1, ty1, tx2, ty2, p_color );

    if( arrow1 == true )
    {
        // calculate two lines that are 0.3 degrees away
        // from the real line, 15 pixels long, and draw them.
        // these two lines are the arrowhead.
        tx2 = tx1 + (int)((float)cos(a+0.3f) * 15.0f);
        ty2 = ty1 + (int)((float)sin(a+0.3f) * 15.0f);
        SDLLine( p_surface, tx1, ty1, tx2, ty2, p_color );
        tx2 = tx1 + (int)((float)cos(a-0.3f) * 15.0f);
        ty2 = ty1 + (int)((float)sin(a-0.3f) * 15.0f);
        SDLLine( p_surface, tx1, ty1, tx2, ty2, p_color );
    }
    if( arrow2 == true )
    {
        // calculate two lines that are 0.3 degrees away
        // from the real line, 15 pixels long, and draw them.
        // these two lines are the arrowhead.
        a += 3.1416f;
        tx1 = x2 + (int)((float)cos(a) * (float)r2);
        ty1 = y2 + (int)((float)sin(a) * (float)r2);
        tx2 = tx1 + (int)((float)cos(a+0.3f) * 15.0f);
        ty2 = ty1 + (int)((float)sin(a+0.3f) * 15.0f);
        SDLLine( p_surface, tx1, ty1, tx2, ty2, p_color );
        tx2 = tx1 + (int)((float)cos(a-0.3f) * 15.0f);
        ty2 = ty1 + (int)((float)sin(a-0.3f) * 15.0f);
        SDLLine( p_surface, tx1, ty1, tx2, ty2, p_color );
    }
}




// ----------------------------------------------------------------
//  Name:           SDLBlit
//  Description:    draws a surface on another surface
//  Arguments:      p_source: surface to draw from
//                  p_dest: surface to draw on
//                  x, y: coordinates
//  Return Value:   None
// ----------------------------------------------------------------
void SDLBlit( SDL_Surface* p_source, SDL_Surface* p_dest, int x, int y )
{
    // make the rects static for speed.
    static SDL_Rect sourcerect;
    static SDL_Rect destrect;

    sourcerect.w = p_source->w;
    sourcerect.h = p_source->h;
    sourcerect.x = 0;
    sourcerect.y = 0;
    destrect.w = p_source->w;
    destrect.h = p_source->h;
    destrect.x = x;
    destrect.y = y;
    SDL_BlitSurface( p_source, &sourcerect, p_dest, &destrect );
}



// ----------------------------------------------------------------
//  Name:           SDLBox
//  Description:    draws a solid box on a surface
//  Arguments:      p_surface: surface to draw on
//                  x, y: coordinates
//                  width, height: width and height of the box
//                  p_color: color of the box
//  Return Value:   None
// ----------------------------------------------------------------
void SDLBox( SDL_Surface* p_surface, int x, int y, int w, int h,
             SDL_Color p_color )
{
    static SDL_Rect rect;
    Uint32 col = SDL_MapRGB( p_surface->format, p_color.r, p_color.g, p_color.b );

    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
    SDL_FillRect( p_surface, &rect, col );
}