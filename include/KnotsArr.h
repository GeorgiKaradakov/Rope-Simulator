#pragma once
#include <SDL2/SDL.h>

#include "Knot.h"
using namespace std;

#define KNOTS_CNT 16

struct knots_arr{
	Knot knots[KNOTS_CNT];
	size_t size;

	 Knot& operator [](int idx) {
        return knots[idx];
    }
};

bool add_knot(knots_arr *knots, const Knot &knot){
	if(knots->size==KNOTS_CNT)return false;

	knots->knots[knots->size++]=knot;
	return true;
}

bool add_neighbour(Knot *knot, int ind){
	if(knot->neigh_ind==NEIGH_CAP)return false;

	knot->neighbours[knot->neigh_ind++]=ind;
	return true;
}
