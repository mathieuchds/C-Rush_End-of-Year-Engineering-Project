#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "effects.h"
#define N 50 //à défaut de ne pas avoir la structure pour le tableau de pixels

coordonnee_image coordonnee_complexe_vers_image (coordonnee_complexe z, int L, int C){
    coordonnee_image coord;
    coord.i=L-z.im;
    coord.j=z.re;
    return coord;
}

coordonnee_complexe coordonnee_image_vers_complexe(coordonnee_image im, int L, int C){
    coordonnee_complexe complexe;
    complexe.re=im.j+0.5;
    complexe.im=L-im.i;
    return complexe;
}

void applique_transformation(tabPixel * originale, tabPixel * destination, transformation t, coordonnee_complexe (*transformation_inverse)(transformation)) {
    int L= originale->h;
    int C= originale ->w;
    coordonnee_image im;
    for (im.i=0; im.i<L; im.i++) {
        for (im.j=0; im.j<C; im.j++) {
            coordonnee_complexe z_p = coordonnee_image_vers_complexe(im, L, C);
            coordonnee_complexe z= transformation_inverse(t);
            coordonnee_image im_fin=coordonnee_complexe_vers_image(z, L, C);
            if (0<=im_fin.i && im_fin.i<L && 0<=im_fin.j && im_fin.j<C){
                transform_p2_into_p1(originale, im.i, im.j, destination, im_fin.i, im_fin.j);
            }
            else {
                color_pixel(t.couleur_defaut, destination, im_fin.i, im_fin.j);
            }
        }
    }
}


//Rotation Partielle de centre z0
coordonnee_complexe rotation ( coordonnee_complexe z, coordonnee_complexe z0, float theta){
    coordonnee_complexe compl;
    float x = z.re;
    float y = z.im;
    float x0 = z0.re;
    float y0 = z0.im;
    compl.re=cos(theta)*(x-x0)-sin(theta)*(y-y0)+x0;
    compl.im= sin(theta)*(x-x0)+cos(theta)*(y-y0) +y0;
    return  compl;
}

coordonnee_complexe rotation_transformation_inverse(transformation t) {
    float x = t.z_prime.re;
    float y=t.z_prime.im;
    float x0=t.z_0.re;
    float y0=t.z_0.im;
    float mod_z = pow((pow((x-x0),2) + pow((y-y0),2)),0.5);
    if (mod_z<=t.d0){
        return t.z_prime;
    }
    else if (mod_z<=t.dmax) {
        float angle = -t.theta_max/((t.dmax-t.d0)*(mod_z-t.d0));
        return rotation(t.z_prime,t.z_0, angle);
    }
    else if (mod_z<=t.d1) {
        float angle = -(t.theta_max/((t.dmax-t.d0)*(mod_z-t.d0))+t.theta_max);
        return rotation(t.z_prime,t.z_0, angle);
    }
    else {
        return t.z_prime;
    }
}



//Zoom
coordonnee_complexe zoom_transformation_inverse(transformation t){
    coordonnee_complexe compl;
    compl.re=(t.z_prime.re-t.z_0.re)/t.alpha+t.z_0.re;
    compl.im=(t.z_prime.im-t.z_0.im)/t.alpha+t.z_0.im;
    return compl;
}

//Translation
coordonnee_complexe translation_H_transformation_inverse(transformation t, int transx, int transy) {
    coordonnee_complexe compl;
    compl.re =(t.z_prime.re-t.z_0.re)+transx;
    compl.im =(t.z_prime.im-t.z_0.im)+transy;
    return compl;
}

//Rotation sur une partie d'une zone
//Zoom sur une partie d'une zone

