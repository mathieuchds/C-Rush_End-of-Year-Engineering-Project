#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// Structure représentant une couleur RGBA
typedef struct couleur {
    int r;
    int g;
    int b;
    int a;
} couleur;

/**
 * Charge une image et la convertit au format SDL_PIXELFORMAT_RGBA8888.
 */
SDL_Surface* load_image_surface(const char *image_name) {
    SDL_Surface* loaded = IMG_Load(image_name);
    if (!loaded) {
        fprintf(stderr, "Erreur IMG_Load: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Surface* surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(loaded);
    if (!surface) {
        fprintf(stderr, "Erreur SDL_ConvertSurfaceFormat: %s\n", SDL_GetError());
    }

    return surface;
}

/**
 * Copie la couleur du pixel (i1, j1) de surf1 dans le pixel (i2, j2) de surf2.
 */
void transform_p2_into_p1(SDL_Surface *surf1, int i1, int j1, SDL_Surface *surf2, int i2, int j2) {
    Uint32 *pixels1 = (Uint32 *)surf1->pixels;
    Uint32 *pixels2 = (Uint32 *)surf2->pixels;

    int w1 = surf1->w;
    int w2 = surf2->w;

    Uint32 pixel = pixels1[i1 * w1 + j1];

    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel, surf1->format, &r, &g, &b, &a);

    pixels2[i2 * w2 + j2] = SDL_MapRGBA(surf2->format, r, g, b, a);
}


/**
 * Retourne la couleur RGBA du pixel (i, j) d'une surface.
 */
couleur couleur_from_pixel(SDL_Surface *surf, int i, int j) {
    Uint32 *pixels = (Uint32*)surf->pixels;
    Uint32 pixel = pixels[i * surf->w + j];

    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel, surf->format, &r, &g, &b, &a);

    couleur c = { r, g, b, a };
    return c;
}

/**
 * Affecte la couleur c au pixel (i, j) de la surface.
 */
void color_pixel(couleur c, SDL_Surface *surf, int i, int j) {
    Uint32 *pixels = (Uint32*)surf->pixels;
    pixels[i * surf->w + j] = SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a);
}
