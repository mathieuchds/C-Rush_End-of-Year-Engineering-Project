#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <math.h>
#include "end.h"

// Victory ------------------------------------------------------------------------------------------------------------
void page_fin_basique(SDL_Window * window, SDL_Renderer* renderer,SDL_Rect window_dimensions, SDL_Texture ** text, int victory, coord c_button, coord police_play){
    SDL_Rect rect1, rect2;
    SDL_SetRenderDrawColor(renderer, 0,0,0,120);
    rect1.x=0;
    rect1.y=0;
    rect1.w=window_dimensions.w;
    rect1.h=window_dimensions.h; 
    SDL_RenderFillRect(renderer, &rect1); 

    SDL_SetRenderDrawColor(renderer, 132,189,194,255);
    rect2.x=125;
    rect2.y=125;
    rect2.w=window_dimensions.w-250;
    rect2.h=window_dimensions.h-250; 
    SDL_RenderFillRect(renderer, &rect2); 

    coord rect;
    rect.x=75;
    rect.y=75;
    rect.w=window_dimensions.w-125;
    rect.h=window_dimensions.h-125; 


    coord texte;
    texte.w=window_dimensions.w/2;
    texte.h=window_dimensions.h/7;
    texte.x= (window_dimensions.w-texte.w)/2;
    texte.y=window_dimensions.h/3;

    char * play = "A G A I N !";
    SDL_Texture * t_play= chargement_police(window, renderer, play);

    if (victory==1) {
        char * vic= "V I C T O R Y !";
        SDL_Texture * t_victory= chargement_police(window, renderer, vic);
        afficher_text(renderer, t_victory, texte, 1);
    }
    else {
        char * def= "D E F E A T  : ( ";
        SDL_Texture * t_defeat= chargement_police(window, renderer, def);
        afficher_text(renderer, t_defeat, texte, 1);
    }
    fond_fixe_xy(text[19], window, renderer, rect);
    bool b_button=pos_cursor(c_button);
    hover_bouton(window, renderer, text[8],text[9], b_button, c_button);
    afficher_text(renderer, t_play, police_play, 1);
}


