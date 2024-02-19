#include <SDL2/SDL.h>
#include <cmath>

#include "Knot.h"
#include "Line.cpp"
#include "Time.h"
#include "KnotsArr.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 600

#define BLACK 0, 0, 0, 255
#define GREY  122, 122, 122, 255
#define PINK  122, 0, 122, 255
#define GREEN 46, 155, 46, 255
#define RED 227, 36, 43, 255

vec2f get_mouse_pos();
void compute_velocity(Knot *knot, knots_arr *arr);

int main(int argc, char **argv){
    if(SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Error: cannot initialize SDL");
        return 1;
    }
    
    SDL_Window *wind = SDL_CreateWindow("Rope Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if(wind == NULL){
        SDL_Log("Error: cannot initialize SDL_Window");
        return 1;
    }
    SDL_Renderer *rend = SDL_CreateRenderer(wind, 0, -1);
    if(rend == NULL){
        SDL_Log("Error: cannot initialize SDL_Renderer");
        return 1;
    }
    SDL_Event e;
	Time time = Time();
    
    
	knots_arr knots{.size=0};
    bool should_close=0, left_pressed=0;
    int drag_ind=-1;
    while(!should_close){
		time.update_time();

        while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT:should_close=1;break;

				case SDL_MOUSEBUTTONDOWN:

					if(e.button.button == SDL_BUTTON_LEFT) left_pressed=1;
					else if(e.button.button == SDL_BUTTON_RIGHT && e.button.clicks==1){ 
						auto [mx, my]=get_mouse_pos();

						if(knots.size==0)
							add_knot(&knots, Knot(mx, my, SDL_Color{GREEN}));
						else{
						int i;bool breaked=false;
							for(i=0; i<knots.size; i++){
								if(knots[i].is_inside_circle(mx, my)){
									breaked=true;
									break;
								}
							}

							if(breaked){
								if(knots[i].neigh_ind<NEIGH_CAP){
									add_knot(&knots, Knot(mx, my, SDL_Color{GREEN}));
									add_neighbour(&knots[i], knots.size-1);
									add_neighbour(&knots[knots.size-1], i);
								}
							}
						}

					}

				break;

				case SDL_MOUSEBUTTONUP:

					if(e.button.button == SDL_BUTTON_LEFT) left_pressed=0;

				break;

				case SDL_KEYDOWN:
				
					if(e.key.keysym.sym == SDLK_ESCAPE) should_close=1;

				break;
			}
        }

        if(left_pressed){
			auto [mx, my]=get_mouse_pos();
            for(int i=0; i<knots.size; i++){
                if(knots[i].is_inside_circle((float)mx, (float)my) && drag_ind==-1){
                    drag_ind=i;
                    break;
                }
            }
			knots[drag_ind].color=SDL_Color{RED};
        }else{
			knots[drag_ind].color=SDL_Color{GREEN};
            drag_ind=-1;
		}
        
        SDL_SetRenderDrawColor(rend, BLACK);
        SDL_RenderClear(rend);
        
        if(drag_ind>=0)
            knots[drag_ind].set_center_coords(get_mouse_pos(), WIDTH, HEIGHT);

		for(int i=0; i<knots.size; i++){
			compute_velocity(&knots[i], &knots);
			if(i!=drag_ind){
				knots[i].cx+=knots[i].vel_x*time.get_dt();
				knots[i].cy+=knots[i].vel_y*time.get_dt();
			}
		}
	
        for(int i=0; i<knots.size; i++){  //                         Connect the knots
			for(int n_ind=0; n_ind<knots.knots[i].neigh_ind; n_ind++){
				draw_thicc_line(rend, knots[i].cx, knots[i].cy, 
						        knots[knots[i].neighbours[n_ind]].cx, knots[knots[i].neighbours[n_ind]].cy, 
								15, SDL_Color{GREY});
			}
		}

        for(int i=0; i<knots.size; i++){  //                         Draw the knots
            knots.knots[i].render_knot(rend);
        }
        
        SDL_RenderPresent(rend);
   }
    
    SDL_DestroyWindow(wind);
    SDL_DestroyRenderer(rend);
    SDL_Quit();

    return 0;
}

void compute_velocity(Knot *knot, knots_arr *arr){
	const int TARGET_DIST=40;
	const int STIFFNESS=38;
	knot->vel_x=0, knot->vel_y=0;

	for(int i=0; i<knot->neigh_ind; i++){
		float nvx=knot->cx-(*arr)[knot->neighbours[i]].cx;
		float nvy=knot->cy-(*arr)[knot->neighbours[i]].cy;

		float len=sqrt(nvx*nvx + nvy*nvy);
		float dir_x=len>EPSILON ? (knot->cx-(*arr)[knot->neighbours[i]].cx)/len : 1;
		float dir_y=len>EPSILON ? (knot->cy-(*arr)[knot->neighbours[i]].cy)/len : 0;
		
		float tar_x=(*arr)[knot->neighbours[i]].cx+dir_x*TARGET_DIST;
		float tar_y=(*arr)[knot->neighbours[i]].cy+dir_y*TARGET_DIST;

		knot->vel_x += (tar_x-knot->cx)*STIFFNESS;
		knot->vel_y += (tar_y-knot->cy)*STIFFNESS;
	}


	const float REPULSION=1.5;

	for(int i=0; i<arr->size; i++){
		float nvx=knot->cx-(*arr)[i].cx;
		float nvy=knot->cy-(*arr)[i].cy;

		float len=sqrt(nvx*nvx + nvy*nvy);
		if((knot->cx!=(*arr)[i].cx && knot->cy!=(*arr)[i].cy) && (len<=RAD*2)){

			float dir_x=len>EPSILON ? (knot->cx-(*arr)[i].cx)/len : 1;
			float dir_y=len>EPSILON ? (knot->cy-(*arr)[i].cy)/len : 0;

			knot->vel_x += (knot->cx-(*arr)[i].cx)*REPULSION;
			knot->vel_y += (knot->cy-(*arr)[i].cy)*REPULSION;
		}
	}
}

vec2f get_mouse_pos(){
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    
    return {(float)mx, (float)my};
}
