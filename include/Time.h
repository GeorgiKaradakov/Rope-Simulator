#pragma once
#include <SDL2/SDL.h>

using namespace std;

class Time{
private:
	uint32_t prev;
	float dt;

public:
	Time();
	void update_time();
	float get_dt();
};

Time::Time(){
	this->prev=SDL_GetTicks();
}

void Time::update_time(){
	uint32_t curr=SDL_GetTicks(); 
	this->dt=(curr-this->prev)/1000.f;
	this->prev=curr;
}

float Time::get_dt(){
	return this->dt;
}
