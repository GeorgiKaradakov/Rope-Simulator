#pragma once
#include <SDL2/SDL.h>

const int RAD=15;
const int NEIGH_CAP=4;

struct vec2f{
    float x, y;
};

class Knot{
public:
    float cx, cy;
    SDL_Color color;
    float vel_x, vel_y;
	int *neighbours;
	size_t neigh_ind;

public:
    Knot(float cx, float cy, SDL_Color color);
    Knot(){}
    void render_knot(SDL_Renderer *rend);
    bool is_inside_circle(float x, float y);
    bool set_center_coords(vec2f coords, int width, int height);

private:
    vec2f get_x_range();
    vec2f get_y_range();
};

Knot::Knot(float cx, float cy, SDL_Color color){
    this->cx=cx;
    this->cy=cy;
    this->color=color;
	this->neighbours=new int[NEIGH_CAP];
	this->neigh_ind=0;
}

bool Knot::is_inside_circle(float x, float y){
    auto rx=get_x_range(), ry=get_y_range();
    
    return (rx.x<=x && x<=rx.y) && (ry.x<=y && y<=ry.y);
}

bool Knot::set_center_coords(vec2f coords, int width, int height){
    if(0>coords.x || coords.x>=width || 0>coords.y || coords.y>=height)return false;
    this->cx=coords.x;
    this->cy=coords.y;
    
    return true;
}

vec2f Knot::get_x_range(){
    return {
        .x=cx-RAD,
        .y=cx+RAD
    };
}

vec2f Knot::get_y_range(){
    return {
        .x=cy-RAD,
        .y=cy+RAD
    };
}

void Knot::render_knot(SDL_Renderer *rend){
    for(float y=cy-RAD; y <= cy+RAD; y++){
        for(float x=cx-RAD; x <= cx+RAD; x++){
            float eq=(x-cx)*(x-cx)+(y-cy)*(y-cy);
            if(eq<=RAD*RAD){
                SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPointF(rend, x, y);
            }
        }
    }
}
