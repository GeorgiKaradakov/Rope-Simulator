#pragma once
#include <SDL2/SDL.h>

#include "Knot.h"
using namespace std;

#define KNOTS_CNT 16

struct knots_arr{
	Knot knots[KNOTS_CNT];
	size_t size;

	knots_arr(){
		for(int i=0; i<KNOTS_CNT; i++){
			knots[i]=Knot();
		}
		size=0;
	}

	Knot& operator [](int idx) {
        return knots[idx];
    }
};

bool add_knot(knots_arr *knots, float _cx, float _cy, SDL_Color _color){
	if(knots->size==KNOTS_CNT)return false;

	knots->knots[knots->size].cx = _cx;
	knots->knots[knots->size].cy = _cy;
	knots->knots[knots->size++].color = _color;
	return true;
}

bool add_neighbour(Knot *knot, int ind){
	if(knot->neigh_ind==NEIGH_CAP)return false;

	knot->neighbours[knot->neigh_ind++]=ind;
	return true;
}
