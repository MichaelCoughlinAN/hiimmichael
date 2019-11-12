/*
 * Copyright (C) 2009 Josh A. Beam
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdio>
#include <cmath>
#include <SDL/SDL.h>
#include "Rasterizer.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

static bool g_Running = true;

static void
HandleKeyEvent(const SDL_Event &event)
{
	switch(event.key.keysym.sym) {
		default:
			break;
		case SDLK_ESCAPE:
			g_Running = false;
			break;
	}
}

static void
HandleEvent(const SDL_Event &event)
{
	switch(event.type) {
		default:
			break;
		case SDL_QUIT:
			g_Running = false;
			break;
		case SDL_KEYDOWN:
			HandleKeyEvent(event);
			break;
	}
}

int
main(int argc, char *argv[])
{
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init failed\n");
		return 1;
	}

	// create window for drawing
	SDL_Surface *screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE);
	if(!screen) {
		SDL_Quit();
		fprintf(stderr, "SDL_SetVideoMode failed\n");
		return 1;
	}

	SDL_WM_SetCaption("Triangle Rasterization Demo - http://www.3ddrome.com/", NULL);

	Rasterizer rast;
	rast.SetFrameBuffer((uint32_t *)screen->pixels, WINDOW_WIDTH, WINDOW_HEIGHT);

	float r = 0.0f;
	unsigned int lastTicks = SDL_GetTicks();

	// loop until we're done running the program
	while(g_Running) {
		// handle events
		SDL_Event event;
		while(SDL_PollEvent(&event))
			HandleEvent(event);

		// lock surface and clear framebuffer
		SDL_LockSurface(screen);
		rast.Clear();

		// calculate coordinates for triangle
		const float size = 110.0f;
		float x1 = (WINDOW_WIDTH / 2) + cosf(r - M_PI / 6.0) * size;
		float y1 = (WINDOW_HEIGHT / 2) + sinf(r - M_PI / 6.0) * size;
		float x2 = (WINDOW_WIDTH / 2) + cosf(r + M_PI / 2.0) * size;
		float y2 = (WINDOW_HEIGHT / 2) + sinf(r + M_PI / 2.0) * size;
		float x3 = (WINDOW_WIDTH / 2) + cosf(r + M_PI + M_PI / 6.0) * size;
		float y3 = (WINDOW_HEIGHT / 2) + sinf(r + M_PI + M_PI / 6.0) * size;

		// colors for each point of the triangle
		Color color1(1.0f, 0.0f, 0.0f);
		Color color2(0.0f, 1.0f, 0.0f);
		Color color3(0.0f, 0.0f, 1.0f);

		// render triangle
		rast.DrawTriangle(color1, x1, y1, color2, x2, y2, color3, x3, y3);

		// unlock and update surface
		SDL_UnlockSurface(screen);
		SDL_UpdateRect(screen, 0, 0, 0, 0);

		// calculate the number of seconds that
		// have passed since the last update
		unsigned int ticks = SDL_GetTicks();
		unsigned int ticksDiff = ticks - lastTicks;
		if(ticksDiff == 0)
			continue;
		float time = ticksDiff / 1000.0f;
		lastTicks = ticks;

		// update rotation
		r += M_PI / 2.0f * time;

		// display frames per second
		unsigned int fps = 1000 / ticksDiff;
		printf("Frames per second: %u    \r", fps);
	}

	SDL_Quit();
	return 0;
}
