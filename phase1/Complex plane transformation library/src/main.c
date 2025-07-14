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

void draw_filled_quad(SDL_Renderer *renderer, SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4) {
    // On remplit le quadrilatère en traçant des lignes horizontales entre les bords
    SDL_Point quad[4] = {p1, p2, p3, p4};

    // Trouver les limites du quadrilatère
    int minY = fmin(fmin(p1.y, p2.y), fmin(p3.y, p4.y));
    int maxY = fmax(fmax(p1.y, p2.y), fmax(p3.y, p4.y));

    for (int y = minY; y <= maxY; ++y) {
        // Chercher les intersections avec les 4 segments
        int count = 0;
        int xs[4];

        for (int i = 0; i < 4; ++i) {
            SDL_Point a = quad[i];
            SDL_Point b = quad[(i + 1) % 4];

            if ((a.y <= y && b.y > y) || (b.y <= y && a.y > y)) {
                float t = (float)(y - a.y) / (float)(b.y - a.y);
                xs[count++] = a.x + t * (b.x - a.x);
            }
        }

        if (count == 2) {
            if (xs[0] > xs[1]) {
                int tmp = xs[0];
                xs[0] = xs[1];
                xs[1] = tmp;
            }
            SDL_RenderDrawLine(renderer, xs[0], y, xs[1], y);
        }
    }
}

void draw_loupe(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // --- Verre de la loupe (translucide) ---
    SDL_SetRenderDrawColor(renderer, 150, 150, 255, 50);
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }

    // --- Bord épais ---
    SDL_SetRenderDrawColor(renderer, 135, 53, 0, 255);
    int border = 6;
    for (int r = radius - border; r <= radius; ++r) {
        double prevX = centerX + r * cos(0);
        double prevY = centerY + r * sin(0);
        for (double angle = 0.5; angle <= 360; angle += 0.5) {
            double rad = angle * M_PI / 180;
            double x = centerX + r * cos(rad);
            double y = centerY + r * sin(rad);
            SDL_RenderDrawLine(renderer, (int)prevX, (int)prevY, (int)x, (int)y);
            prevX = x;
            prevY = y;
        }
    }

    // --- Manche en rectangle incliné ---
    int handleLength = radius * 1.5;
    int handleWidth = radius / 3;

    double angle = M_PI / 4; // 45°
    double dx = cos(angle);
    double dy = sin(angle);

    double x0 = centerX + radius * dx;
    double y0 = centerY + radius * dy;

    double perpX = -dy;
    double perpY = dx;

    SDL_Point p1 = {(int)(x0 + perpX * handleWidth / 2), (int)(y0 + perpY * handleWidth / 2)};
    SDL_Point p2 = {(int)(x0 - perpX * handleWidth / 2), (int)(y0 - perpY * handleWidth / 2)};
    SDL_Point p3 = {(int)(x0 - perpX * handleWidth / 2 + dx * handleLength),
                    (int)(y0 - perpY * handleWidth / 2 + dy * handleLength)};
    SDL_Point p4 = {(int)(x0 + perpX * handleWidth / 2 + dx * handleLength),
                    (int)(y0 + perpY * handleWidth / 2 + dy * handleLength)};

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // gris foncé
    draw_filled_quad(renderer, p1, p2, p3, p4);
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

    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

    SDL_Surface *surf_originale = load_image_surface("textures/decor_A.png");
    SDL_Surface *surf_modif;

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    
    SDL_Window *window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, surf_originale->w, surf_originale->h, SDL_WINDOW_SHOWN);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer, NULL);

    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer, NULL);

    transformation * t = init_t();
    SDL_Texture * texture;
    t->theta_max = M_PI/8;
    t->d0 = 0;
    t->d1 = 100;
    t->dmax = 50;
    t->alpha = 4;
    t->transx = 0;
    t->transy = 100;

    int it = 0;
    int direction = 1;

    SDL_Event event;
    int quit = 0;
    int x_mouse = 0; 
    int y_mouse = 0;
    float it_zoom = 1;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 0;
                    break;

                case SDL_MOUSEMOTION: {
                    x_mouse = event.motion.x;
                    y_mouse = w_y - event.motion.y;
                    break;
                }

                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
        it++;
        //t.theta_max = it*M_PI/8;
        //texture = image_to_texture("textures/couleurs.jpg", renderer, t, &rotation_transformation_inverse_rond);
        //texture = image_to_texture("textures/grenouille.png", renderer, t, &rotation_rect_transformation_inverse);
        //texture = image_to_texture("textures/grenouille.png", renderer, t, &zoom_transformation_inverse);
        //texture = image_to_texture("textures/grenouille.png", renderer, t, &zoom_surx_transformation_inverse);
        //texture = image_to_texture("textures/grenouille.png", renderer, t, &zoom_sury_transformation_inverse);
        //texture = image_to_texture("textures/couleurs.jpg", renderer, t, &zoom_transformation_inverse_rond);
        //texture = image_to_texture("textures/couleurs.jpg", renderer, t, &translation_transformation_inverse_x);

        it++;
        
        // t->z_0.re = x_mouse; 
        // t->z_0.im = y_mouse; 
        t->z_0.re = w_x/2;
        t->z_0.im = w_y/2;
        //printf("z0 : %f %f\n", t.z_0.re, t.z_0.im);
        //printf("alpha : %f, theta: %f, rota_it: %d, sensi: %d\n", t.alpha, t.theta_max, rota_it, sensi);
        surf_modif = surface_to_surface(surf_originale, t, &zoom_transformation_inverse_carre);
        texture = SDL_CreateTextureFromSurface(renderer, surf_modif);
        //printf("z0 : %f %f\n", t.z_0.re, t.z_0.im);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        //draw_loupe(renderer, x_mouse, w_y - y_mouse, t->d1 - t->d0);

        SDL_RenderPresent(renderer);
        SDL_Delay(7000);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;


}