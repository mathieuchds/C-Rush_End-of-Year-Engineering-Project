#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "effects.h"

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture ** tab_texture) {                           
    
    char msg_formated[255];                                            
    int l;                                                     
    printf("END \n");                        
    
    if (!ok) {                                      
        strncpy(msg_formated, msg, 250);                                         
        l = strlen(msg_formated);                                            
        strcpy(msg_formated + l, " : %s\n");                                              
        SDL_Log(msg_formated, SDL_GetError());                                   
    }                                                          
                                            
    if (renderer != NULL) {                                          
        SDL_DestroyRenderer(renderer);                              
        renderer = NULL;
    }
    if (window != NULL)   {                                         
        SDL_DestroyWindow(window);                                  
        window= NULL;
    }
    int i = 0;
    if(tab_texture != NULL){
        while(tab_texture[i] != NULL){
            SDL_DestroyTexture(tab_texture[i]);
            i++;
        }
    }
                                            
    SDL_Quit();                                                    
                                            
    if (!ok) {                                               
        exit(EXIT_FAILURE);                                                  
    }                                                          
}                    

int main(int argc, char** argv) {

    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Erreur IMG_Init: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    
    // Affichage test

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.h * 0.5, screen.h * 0.5, SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer, NULL);

    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer, NULL);

    transformation t = init_t();
    SDL_Texture * texture;
    t.theta_max = M_PI/16;
    t.d0 = 0;
    t.d1 = 64;
    t.dmax = 50;
    t.alpha = 1;
    t.transx = 100;
    t.transy = 100;

    int it = 0;
    int rota_it = 0;
    int direction = 1;
    int sensi_zoom = 20;
    int sensi_rota = 3;
    float it_zoom = 1;
    
    SDL_Surface *surf_originale = load_image_surface("textures/bee_a.png");
    t.z_0.re = surf_originale->w/2;
    t.z_0.im = surf_originale->h/2;
    t.z_prime.re = surf_originale->w/2;
    t.z_prime.im = surf_originale->h/2;

    SDL_Surface *surf_modif;

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }

        SDL_RenderClear(renderer);

        it++;
        rota_it += direction;    
        it_zoom += direction;

        if(it%120 == 0){
            direction *= -1;
            if(direction == -1){
                surf_originale = load_image_surface("textures/bee_a2.png");
            }else{
                surf_originale = load_image_surface("textures/bee_a.png");
            }
        }

        t.alpha = 1/(it_zoom/sensi_zoom);
        t.theta_max = (rota_it/sensi_rota)*M_PI/8;
        //printf("alpha : %f, theta: %f, rota_it: %d, sensi: %d\n", t.alpha, t.theta_max, rota_it, sensi);
        surf_modif = surface_to_surface(surf_originale, t, &rotation_transformation_inverse);
        surf_modif = surface_to_surface(surf_modif, t, &zoom_transformation_inverse);
        texture = SDL_CreateTextureFromSurface(renderer, surf_modif);

        //texture = image_to_texture("textures/grenouille.png", renderer, t, &zoom_transformation_inverse);
        //texture = image_to_texture("textures/grenouille.png", renderer, t, &translation_H_transformation_inverse);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        //SDL_Delay(20);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;


}