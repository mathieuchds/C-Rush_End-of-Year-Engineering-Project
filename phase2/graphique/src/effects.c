#include "effects.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// max a et bs
float max_complexe(coordonnee_complexe z) {
    float abs_re = fabs(z.re);
    float abs_im = fabs(z.im);
    float max_val;

    if (abs_im > abs_re){
        max_val = abs_im;
    }else{
        max_val = abs_re;
    }

    return max_val;
}

// Conversion complexe -> image
coordonnee_image coordonnee_complexe_vers_image(coordonnee_complexe z, int L, int C) {
    coordonnee_image coord;
    coord.i = L - z.im;
    coord.j = z.re;
    return coord;
}

// Conversion image -> complexe
coordonnee_complexe coordonnee_image_vers_complexe(coordonnee_image im, int L, int C) {
    coordonnee_complexe complexe;
    complexe.re = im.j + 0.5;
    complexe.im = L - im.i - 0.5;
    return complexe;
}

// Texture créée à partir d'une image + une transformation
SDL_Texture * image_to_texture(char * image_name, SDL_Renderer * renderer, transformation *t,
                            coordonnee_complexe (*transformation_inverse)(transformation *, int *)) {

    SDL_Surface *surf_originale = load_image_surface(image_name);

    // Créer une surface vide de mêmes dimensions et même format
    SDL_Surface *surf_destination = SDL_CreateRGBSurfaceWithFormat(
        0,
        surf_originale->w,
        surf_originale->h,
        32,
        surf_originale->format->format
    );

    if (!surf_destination) {
        fprintf(stderr, "Erreur de création surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surf_originale);
        return NULL;
    }

    // Met tous les pixels de la surface destination à zéro (transparent noir)
    SDL_LockSurface(surf_destination);
    memset(surf_destination->pixels, 0, surf_destination->h * surf_destination->pitch);
    SDL_UnlockSurface(surf_destination);

    if (!surf_originale || !surf_destination) {
        SDL_FreeSurface(surf_originale);
        SDL_FreeSurface(surf_destination);
        return NULL;
    }
    t->z_0.re = surf_originale->w/2;
    t->z_0.im = surf_originale->h/2;
    t->z_prime.re = surf_originale->w/2;
    t->z_prime.im = surf_originale->h/2;

    int dim_surface[2];
    dim_surface[0] = surf_originale->w;
    dim_surface[1] = surf_originale->h;

    applique_transformation(surf_originale, surf_destination, t, transformation_inverse, dim_surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf_destination);

    SDL_FreeSurface(surf_originale);
    SDL_FreeSurface(surf_destination);

    return texture;
}

// Permet d'enchainer plusieurs transformations
SDL_Surface * surface_to_surface(SDL_Surface * surf_originale, transformation *t, coordonnee_complexe (*transformation_inverse)(transformation *, int *)) {
    if (!surf_originale) {
    fprintf(stderr, "surface originale NULL\n");
    return NULL;
    }
    SDL_Surface *surf32 = SDL_ConvertSurfaceFormat(surf_originale, SDL_PIXELFORMAT_RGBA8888, 0);
    if (!surf32) {
        fprintf(stderr, "Erreur de conversion 32 bits : %s\n", SDL_GetError());
        SDL_FreeSurface(surf_originale);
        return NULL;
    }

    SDL_FreeSurface(surf_originale); // libère l'ancienne surface si ce n'est plus utile
    surf_originale = surf32;

    SDL_Surface *surf_destination = SDL_CreateRGBSurfaceWithFormat(
        0,
        surf_originale->w,
        surf_originale->h,
        32,
        surf_originale->format->format
    );
    //printf("1\n");
    int dim_surface[2];
    dim_surface[0] = surf_originale->w;
    dim_surface[1] = surf_originale->h;

    if (!surf_destination) {
        fprintf(stderr, "Erreur de création surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surf_originale);
        return NULL;
    }
    //printf("2\n");
    // Met tous les pixels de la surface destination à zéro (transparent noir)
    SDL_LockSurface(surf_destination);
    memset(surf_destination->pixels, 0, surf_destination->h * surf_destination->pitch);
    SDL_UnlockSurface(surf_destination);
    //printf("3\n");
    if (!surf_originale || !surf_destination) {
        SDL_FreeSurface(surf_originale);
        SDL_FreeSurface(surf_destination);
        return NULL;
    }

    applique_transformation(surf_originale, surf_destination, t, transformation_inverse,dim_surface);

    return surf_destination;
}

// Initialisation transformation
transformation * init_t() {
    transformation * t;
    t = malloc(sizeof(transformation));
    t->alpha = 0;
    couleur c = {0, 0, 0, 255};
    t->couleur_defaut = c;
    t->d0 = 0;
    t->d1 = 0;
    t->dmax = 0;
    t->theta_max = 0;
    coordonnee_complexe z0 = {0, 0};
    t->z_0 = z0;
    t->z_prime = z0;
    t->transy = 0;
    t->transx = 0;
    return t;
}

// Appliquer transformation
void applique_transformation(SDL_Surface *originale, SDL_Surface *destination, transformation *t,
                              coordonnee_complexe (*transformation_inverse)(transformation *, int *), int dim_surface[2]) {
    int L = destination->h;
    int C = destination->w;

    coordonnee_image im;

    for (im.i = 0; im.i < L; im.i++) {
        for (im.j = 0; im.j < C; im.j++) {

            // 1. Met à jour z' (coordonnée du pixel de destination)
            t->z_prime = coordonnee_image_vers_complexe(im, L, C);

            // 2. Calcule l'antécédent dans l'image source
            coordonnee_complexe z = transformation_inverse(t, dim_surface);

            // 3. Convertit en coordonnées entières dans l'image source
            coordonnee_image im_source = coordonnee_complexe_vers_image(z, originale->h, originale->w);

            // 4. Vérifie que les coordonnées sont valides
            if (im_source.i >= 0 && im_source.i < originale->h &&
                im_source.j >= 0 && im_source.j < originale->w &&
                im.i >= 0 && im.i < destination->h &&
                im.j >= 0 && im.j < destination->w) {

                transform_p2_into_p1(originale, im_source.i, im_source.j, destination, im.i, im.j);

            } else {
                // Pixel en dehors de l'image source → on met la couleur par défaut
                color_pixel(t->couleur_defaut, destination, im.i, im.j);
            }
        }
    }
}


// Alpha continu
float alpha_rond(float mod_z){
    float alpha =5*exp(-mod_z*mod_z/1500)+1;
    if (alpha<1) {
        return 1;
    }
    else {
        return alpha;
    }
}

// Rotation autour d’un centre z0
coordonnee_complexe rotation(coordonnee_complexe z, coordonnee_complexe z0, float theta) {
    coordonnee_complexe compl;
    float x = z.re;
    float y = z.im;
    float x0 = z0.re;
    float y0 = z0.im;
    compl.re = cos(theta) * (x - x0) - sin(theta) * (y - y0) + x0;
    compl.im = sin(theta) * (x - x0) + cos(theta) * (y - y0) + y0;
    return compl;
}

// Transformation inverse d'une rotation partielle continue
coordonnee_complexe rotation_transformation_inverse_rond(transformation *t, int dim_surface[2]) {

    if(t == NULL){
        t = init_t();
        t->theta_max = M_PI/8;
        t->z_0.re = dim_surface[0]/2;
        t->z_0.im = dim_surface[1]/2;
    }

    float x = t->z_prime.re;
    float y = t->z_prime.im;
    float x0 = t->z_0.re;
    float y0 = t->z_0.im;

    float dx = x - x0;
    float dy = y - y0;
    float mod_z = sqrt(dx * dx + dy * dy);

    coordonnee_complexe tmp;

    if (mod_z <= t->d0) {
        tmp = t->z_prime;
    } else if (mod_z <= t->dmax) {
        float angle = -t->theta_max * (mod_z - t->d0) / (t->dmax - t->d0);
        tmp = rotation(t->z_prime, t->z_0, angle);
    } else if (mod_z <= t->d1) {
        float angle = -(t->theta_max * (mod_z - t->dmax)/ (t->dmax - t->d1) + t->theta_max);
        tmp = rotation(t->z_prime, t->z_0, angle);
    } else {
        tmp = t->z_prime;
    }
    return tmp;
}

// Transformation inverse d'une rotation partielle continue
coordonnee_complexe rotation_transformation_inverse_carre(transformation *t, int dim_surface[2]) {

    if(t == NULL){
        t = init_t();
        t->theta_max = M_PI/8;
        t->z_0.re = dim_surface[0]/2;
        t->z_0.im = dim_surface[1]/2;
    }

    float x = t->z_prime.re;
    float y = t->z_prime.im;
    float x0 = t->z_0.re;
    float y0 = t->z_0.im;

    float dx = x - x0;
    float dy = y - y0;
    coordonnee_complexe ztmp; ztmp.re = dx; ztmp.im = dy;
    float mod_z = max_complexe(ztmp);

    coordonnee_complexe tmp;

    if (mod_z <= t->d0) {
        tmp = t->z_prime;
    } else if (mod_z <= t->dmax) {
        float angle = -t->theta_max * (mod_z - t->d0) / (t->dmax - t->d0);
        tmp = rotation(t->z_prime, t->z_0, angle);
    } else if (mod_z <= t->d1) {
        float angle = -(t->theta_max * (mod_z - t->dmax)/ (t->dmax - t->d1) + t->theta_max);
        tmp = rotation(t->z_prime, t->z_0, angle);
    } else {
        tmp = t->z_prime;
    }
    return tmp;
}

// Zoom inverse non continu
coordonnee_complexe zoom_transformation_inverse(transformation *t, int dim_surface[2]) {
    if(t == NULL){
        t = init_t();
        t->alpha = 3;
        t->z_0.re = dim_surface[0]/2;
        t->z_0.im = dim_surface[1]/2;
    }
    coordonnee_complexe compl;
    compl.re = (t->z_prime.re - t->z_0.re) / t->alpha + t->z_0.re;
    compl.im = (t->z_prime.im - t->z_0.im) / t->alpha + t->z_0.im;
    return compl;
}

// Zoom en forme de rond avec continuité
coordonnee_complexe zoom_transformation_inverse_rond(transformation *t, int dim_surface[2]) {

    if(t == NULL){
        t = init_t();
        t->alpha = 3;
        t->z_0.re = dim_surface[0]/2;
        t->z_0.im = dim_surface[1]/2;
    }

    coordonnee_complexe compl;
    float x = t->z_prime.re;
    float y = t->z_prime.im;
    float x0 = t->z_0.re;
    float y0 = t->z_0.im;

    float dx = x - x0;
    float dy = y - y0;
    float mod_z = sqrt(dx * dx + dy * dy);
    float alpha_continu = alpha_rond(mod_z);

    if (mod_z <= t->d0) {
        return t->z_prime;
    } else if (mod_z <= t->d1) {
        compl.re = (t->z_prime.re - t->z_0.re) / alpha_continu + t->z_0.re;
        compl.im = (t->z_prime.im - t->z_0.im) / alpha_continu + t->z_0.im;
        return compl;
    } else {
        return t->z_prime;
    }
}

// Zoom en forme de carre avec continuité
coordonnee_complexe zoom_transformation_inverse_carre(transformation *t, int dim_surface[2]) {

    if(t == NULL){
        t = init_t();
        t->alpha = 3;
        t->z_0.re = dim_surface[0]/2;
        t->z_0.im = dim_surface[1]/2;
    }

    coordonnee_complexe compl;
    float x = t->z_prime.re;
    float y = t->z_prime.im;
    float x0 = t->z_0.re;
    float y0 = t->z_0.im;

    float dx = x - x0;
    float dy = y - y0;
    coordonnee_complexe ztmp; ztmp.re = dx; ztmp.im = dy;
    float mod_z = max_complexe(ztmp);
    float alpha_continu = alpha_rond(mod_z);

    if (mod_z <= t->d0) {
        return t->z_prime;
    } else if (mod_z <= t->d1) {
        compl.re = (t->z_prime.re - t->z_0.re) / alpha_continu + t->z_0.re;
        compl.im = (t->z_prime.im - t->z_0.im) / alpha_continu + t->z_0.im;
        return compl;
    } else {
        return t->z_prime;
    }
}

float smooth_ratio(float x) {
    return 0.5f - 0.5f * cosf(M_PI * x);
}

coordonnee_complexe translation_transformation_inverse_rond(transformation *t, int dim_surface[2]) {
    
    if (t == NULL) {
        t = init_t();
        t->transx = 20; 
        t->transy = 0;  
        t->z_0.re = dim_surface[0] / 2.0f;
        t->z_0.im = dim_surface[1] / 2.0f;
    }

    float x = t->z_prime.re;
    float y = t->z_prime.im;
    float x0 = t->z_0.re;
    float y0 = t->z_0.im;

    float dx = x - x0;
    float dy = y - y0;
    float mod_z = sqrtf(dx * dx + dy * dy);

    coordonnee_complexe tmp;
    coordonnee_complexe v = { t->transx, t->transy };
    float ratio = 0.0f;

    if (mod_z <= t->d0 || mod_z >= t->d1) {
        // Aucun effet aux extrémités
        ratio = 0.0f;
    } else if (mod_z <= t->dmax) {
        // Croissance progressive entre d0 et dmax
        float lin = (mod_z - t->d0) / (t->dmax - t->d0);
        ratio = smooth_ratio(lin);
    } else {
        // Décroissance progressive entre dmax et d1
        float lin = (mod_z - t->dmax) / (t->d1 - t->dmax);
        ratio = smooth_ratio(1.0f - lin);  // décroissance lisse
    }

    // Appliquer la translation inverse, pondérée
    tmp.re = t->z_prime.re - ratio * v.re;
    tmp.im = t->z_prime.im - ratio * v.im;

    return tmp;
}

float smooth_cos_ratio(float dx, float d1) {
    float x = dx / d1; // normalise le ratio
    if (fabsf(x) >= 1.0f) return 0.0f;
    float angle = x * (M_PI / 2.0f); // les f cest pour pas que ça retourne de double
    return cosf(angle) * cosf(angle);  // = cos2(pi/2 * x)
}

coordonnee_complexe translation_transformation_inverse_x(transformation *t, int dim_surface[2]) {
    
    if (t == NULL) {
        t = init_t();
        t->transx = 100;
        t->transy = 0;
        t->z_0.re = dim_surface[0] / 2.0f;
        t->z_0.im = dim_surface[1] / 2.0f;
        t->d1 = 100; // zone floue sur x
    }

    float x = t->z_prime.re;
    float x0 = t->z_0.re;
    float dx = x - x0;

    float ratio = smooth_cos_ratio(dx, t->d1);

    coordonnee_complexe v = { t->transx, t->transy };
    coordonnee_complexe tmp;

    tmp.re = t->z_prime.re - ratio * v.re;
    tmp.im = t->z_prime.im - ratio * v.im;

    return tmp;
}

float smooth_cos_ratio_y(float dy, float d1) {
    float y = dy / d1;
    if (fabsf(y) >= 1.0f) return 0.0f;
    float angle = y * (M_PI / 2.0f);
    return cosf(angle) * cosf(angle);  
}

coordonnee_complexe translation_transformation_inverse_y(transformation *t, int dim_surface[2]) {
    if (t == NULL) {
        t = init_t();
        t->transx = 0;     
        t->transy = 100;    
        t->z_0.re = dim_surface[0] / 2.0f;
        t->z_0.im = dim_surface[1] / 2.0f;
        t->d1 = 100; 
    }

    float y = t->z_prime.im;
    float y0 = t->z_0.im;
    float dy = y - y0;

    float ratio = smooth_cos_ratio_y(dy, t->d1);

    coordonnee_complexe v = { t->transx, t->transy };
    coordonnee_complexe tmp;

    tmp.re = t->z_prime.re - ratio * v.re;
    tmp.im = t->z_prime.im - ratio * v.im;

    return tmp;
}



// Rotation complète
coordonnee_complexe rotation_simple_transformation(transformation *t, int dim_surface[2]){
    if(t == NULL){
        t = init_t();
        t->theta_max = M_PI/8;
        t->z_0.re = dim_surface[0]/2;
        t->z_0.im = dim_surface[1]/2;
    }
    coordonnee_complexe tmp = rotation(t->z_prime, t->z_0, t->theta_max);
    return tmp;
}