#include <SDL2/SDL.h>

typedef struct couleur {
    int r;
    int g;
    int b;
    int a;
} couleur;

SDL_Surface* load_image_surface(const char *image_name);
void transform_p2_into_p1(SDL_Surface *surf1, int i1, int j1, SDL_Surface *surf2, int i2, int j2);
couleur couleur_from_pixel(SDL_Surface *surf, int i, int j);
void color_pixel(couleur c, SDL_Surface *surf, int i, int j);


