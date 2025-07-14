#include <SDL2/SDL.h>
#include "convert.h" 

typedef struct {
    int i;
    int j;
} coordonnee_image;

typedef struct {
    float re;
    float im;
} coordonnee_complexe;

typedef struct {
    float alpha;
    coordonnee_complexe z_0;
    couleur couleur_defaut;
    coordonnee_complexe z_prime;
    float theta_max;
    float d0;
    float d1;
    float dmax;
    int transx;
    int transy;
} transformation;

// Transformation de coordonnées
coordonnee_complexe coordonnee_image_vers_complexe(coordonnee_image im, int width, int height);
coordonnee_image coordonnee_complexe_vers_image(coordonnee_complexe c, int width, int height);

// Fonctions utiles
coordonnee_complexe rotation(coordonnee_complexe z, coordonnee_complexe z0, float theta);

// Liste de nos transformations inverses
coordonnee_complexe zoom_transformation_inverse(transformation *t, int dim_surface[2]);
coordonnee_complexe rotation_transformation_inverse_rond(transformation *t, int dim_surface[2]);
coordonnee_complexe rotation_transformation_inverse_carre(transformation *t, int dim_surface[2]);
coordonnee_complexe rotation_simple_transformation(transformation *t, int dim_surface[2]);
coordonnee_complexe zoom_transformation_inverse_rond(transformation * t, int dim_surface[2]);
coordonnee_complexe zoom_transformation_inverse_carre(transformation * t, int dim_surface[2]);
coordonnee_complexe translation_transformation_inverse_rond(transformation *t, int dim_surface[2]);
coordonnee_complexe translation_transformation_inverse_x(transformation *t, int dim_surface[2]);
coordonnee_complexe translation_transformation_inverse_y(transformation *t, int dim_surface[2]);

// Application d'une transformation sur une image
void applique_transformation(SDL_Surface *originale, SDL_Surface *destination,
                              transformation * t,
                              coordonnee_complexe (*transformation_inverse)(transformation*, int *), int dim_surface[2]);

// Conversion image + transformation vers texture
SDL_Texture * image_to_texture(char *image_name, SDL_Renderer *renderer,
                               transformation * t,
                               coordonnee_complexe (*transformation_inverse)(transformation*, int*));

// Initialisation d'une transformation
transformation * init_t();
SDL_Surface * surface_to_surface(SDL_Surface * surf_originale, transformation * t, coordonnee_complexe (*transformation_inverse)(transformation*, int*));

