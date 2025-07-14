#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "effects.h"

// Gere les animations des entitées
typedef struct animation_page{
    SDL_Texture * texture;      // sprite sheet
    SDL_Rect ** tab;            // tableau d'animation [numero anim][defilement anim]
    int * duree;                // nb de frame de chaque animation
    int nb_anim;                // nombre d'animations
}animation_page; 
 
// représente n'importe quelle entitée
typedef struct entity{
    int id;
    int direction;
    int x;
    int y;
    int x_draw;
    int y_draw;
    int gliding;
    float speed;
    animation_page * feuille_animation;
    animation_page * feuille_animation2;
    animation_page * feuille_animation3;
    animation_page * feuille_animation4;
    animation_page * feuille_animation5;
    animation_page * feuille_animation6;
}entity;

typedef struct maze{
    SDL_Texture * map;
    int dim_case;
    int longueur;
    int hauteur;
    int nb_noeud;
    int * construction;
    int * poids;
    int * button;
    SDL_Texture * button_texture;
    SDL_Rect dest;
}maze;

// Gestion textures
SDL_Rect *load_rectangle_from_sprite(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer, int dim[2], int * correspondance, int offset);
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );
void play_with_texture_2(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer, float zoom);
SDL_Rect ** load_rectangle_tab2D_from_sprite(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer, int dim[2], int * correspondance, int offset);
void render_focus_centered(SDL_Renderer* renderer, SDL_Texture* source_texture, SDL_Rect focus_rect, int window_width, int window_height);
void afficher_animation_page(animation_page **all_anim, int nb_anim);
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture ** tab_texture, animation_page ** all_anim, int nb_anim);
void init_sdl(SDL_Renderer ** renderer, SDL_Window ** window);
void free_maze(maze * m);
SDL_Surface* TextureToSurface(SDL_Renderer* renderer, SDL_Texture* texture);