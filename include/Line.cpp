#pragma once
#include <SDL2/SDL.h>
#include <cmath>

#include "Knot.h"
using namespace std;

#define EPSILON 0.000001


void draw_thicc_line(SDL_Renderer *rend, float x1, float y1, float x2, float y2, float t, SDL_Color color){
	float dx=x2-x1, dy=y2-y1;
	float x3=-dy, y3=dx;

	float len=sqrt(x3*x3 + y3*y3);

	if(len > EPSILON){
		x3/=len, y3/=len;

		SDL_Vertex f_verts[3]={
			{SDL_FPoint{x1+x3*(t/2), y1+y3*(t/2)}, color, SDL_FPoint{0}},
			{SDL_FPoint{x1-x3*(t/2), y1-y3*(t/2)}, color, SDL_FPoint{0}},
			{SDL_FPoint{x2-x3*(t/2), y2-y3*(t/2)}, color, SDL_FPoint{0}},
		};

		SDL_Vertex s_verts[3]={
			{SDL_FPoint{x1+x3*(t/2), y1+y3*(t/2)}, color, SDL_FPoint{0}},
			{SDL_FPoint{x2-x3*(t/2), y2-y3*(t/2)}, color, SDL_FPoint{0}},
			{SDL_FPoint{x2+x3*(t/2), y2+y3*(t/2)}, color, SDL_FPoint{0}}
		};

		SDL_RenderGeometry(rend, nullptr, f_verts, 3, nullptr, 0);
		SDL_RenderGeometry(rend, nullptr, s_verts, 3, nullptr, 0);
	}
}
