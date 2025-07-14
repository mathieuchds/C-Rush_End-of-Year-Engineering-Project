#include "player_movement_graphic.h"
#include <SDL2/SDL_mixer.h>

// Charge toutes les animations d'entitées nécessaires dans le niveau
animation_page ** load_entity_animation(entity_name * tab, int taille, SDL_Window * window, SDL_Renderer * renderer){
    animation_page ** a = malloc(taille*sizeof(animation_page*));
    for(int k=0; k<taille;k++){
        a[k] = malloc(sizeof(animation_page));
    }

    for(int i=0; i<taille; i++){
        switch (tab[i]){
            case SLIME1:
                a[i]->nb_anim = 4; 
                int tableau1[] = {8, 8, 8, 8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau1[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime1_Walk_full.png", window, renderer);
                int dim1[2] = {4, 8};
                int correspondance1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime1_Walk_full.png", window, renderer, dim1, correspondance1, 10);
                break;
            case SLIME2:
                a[i]->nb_anim = 4;

                int tableau2[] = {8, 8, 8, 8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau2[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime2_Walk_full.png", window, renderer);
                int dim2[2] = {4, 8};
                int correspondance2[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime2_Walk_full.png", window, renderer, dim2, correspondance2, 10);
                break;
            case SLIME3:
                a[i]->nb_anim = 4;

                int tableau3[] = {8, 8, 8, 8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau3[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime3_Walk_full.png", window, renderer);
                int dim3[3] = {4, 8};
                int correspondance3[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime3_Walk_full.png", window, renderer, dim3, correspondance3, 10);
                break;
            case SLIME1CHILL: 
                a[i]->nb_anim = 4; 
                int tableau4[] = {6, 6, 6, 6}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau4[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime1_Idle_full.png", window, renderer);
                int dim4[2] = {4, 6};
                int correspondance4[6] = {0, 1, 2, 3, 4, 5};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime1_Idle_full.png", window, renderer, dim4, correspondance4, 10);
                break;
            case SLIME2CHILL:
                a[i]->nb_anim = 4;

                int tableau5[] = {6, 6, 6, 6}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau5[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime2_Idle_full.png", window, renderer);
                int dim5[2] = {4, 6};
                int correspondance5[8] = {0, 1, 2, 3, 4, 5};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime2_Idle_full.png", window, renderer, dim5, correspondance5, 10);
                break;
            case SLIME3CHILL:
                a[i]->nb_anim = 4;

                int tableau6[] = {6, 6, 6, 6}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau6[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime3_Idle_full.png", window, renderer);
                int dim6[3] = {4, 6};
                int correspondance6[8] = {0, 1, 2, 3, 4, 5};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime3_Idle_full.png", window, renderer, dim6, correspondance6, 10);
                break;
            case SLIME1RUN:
                a[i]->nb_anim = 4;

                int tableau7[] = {8, 8, 8, 8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau7[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime1_Run_full.png", window, renderer);
                int dim7[3] = {4, 8};
                int correspondance7[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime1_Run_full.png", window, renderer, dim7, correspondance7, 10);
                break;
            case SLIME2RUN:
                a[i]->nb_anim = 4;

                int tableau8[] = {8, 8, 8, 8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau8[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime2_Run_full.png", window, renderer);
                int dim8[3] = {4, 8};
                int correspondance8[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime2_Run_full.png", window, renderer, dim8, correspondance8, 10);
                break;
            case SLIME3RUN:
                a[i]->nb_anim = 4;

                int tableau9[] = {8, 8, 8, 8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau9[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime3_Run_full.png", window, renderer);
                int dim9[3] = {4, 8};
                int correspondance9[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime3_Run_full.png", window, renderer, dim9, correspondance9, 10);
                break;
            case SLIME1LIGHT:
                a[i]->nb_anim = 4;

                int tableau10[] = {9, 9, 9, 9}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau10[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime1_t.png", window, renderer);
                int dim10[3] = {4, 9};
                int correspondance10[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime1_t.png", window, renderer, dim10, correspondance10, 10);
                break;
            case SLIME2LIGHT:
                a[i]->nb_anim = 4;

                int tableau11[] = {9,9,9,9}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau11[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime2_light.png", window, renderer);
                int dim11[3] = {4, 9};
                int correspondance11[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime2_light.png", window, renderer, dim11, correspondance11, 10);
                break;
            case SLIME3LIGHT: 
                a[i]->nb_anim = 4;

                int tableau12[] = {9, 9, 9, 9}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau12[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime3_light.png", window, renderer);
                int dim12[3] = {4, 9};
                int correspondance12[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime3_light.png", window, renderer, dim12, correspondance12, 10);
                break;
            case MONSTER_ICON1: 
                a[i]->nb_anim = 1;

                int tableau13[] = {8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau13[k];
                }

                a[i]->texture = load_texture_from_image("textures/monster_icon_chill.png", window, renderer);
                int dim13[3] = {1, 8};
                int correspondance13[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/monster_icon_chill.png", window, renderer, dim13, correspondance13, 0);
                break;
            case MONSTER_ICON2: 
                a[i]->nb_anim = 1;

                int tableau14[] = {8}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau14[k];
                }

                a[i]->texture = load_texture_from_image("textures/monster_icon_hunt.png", window, renderer);
                int dim14[3] = {1, 8};
                int correspondance14[8] = {0, 1, 2, 3, 4, 5, 6, 7};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/monster_icon_hunt.png", window, renderer, dim14, correspondance14, 0);
                break;
            case MONSTER_WALK: 
                a[i]->nb_anim = 4;

                int tableau15[] = {4, 4, 4, 4}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau15[k];
                }

                a[i]->texture = load_texture_from_image("textures/monster_walk.png", window, renderer);
                int dim15[3] = {4, 4};
                int correspondance15[8] = {0, 1, 2, 3};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/monster_walk.png", window, renderer, dim15, correspondance15, 0);
                break;
            case SLIME1ATTACK: 
                a[i]->nb_anim = 4;

                int tableau16[] = {10, 10, 10, 10}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau16[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime1_Attack_full.png", window, renderer);
                int dim16[3] = {4, 10};
                int correspondance16[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime1_Attack_full.png", window, renderer, dim16, correspondance16, 10);
                break;
            case SLIME2ATTACK: 
                a[i]->nb_anim = 4;

                int tableau17[] = {10, 10, 10, 10}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau17[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime2_Attack_full.png", window, renderer);
                int dim17[3] = {4, 10};
                int correspondance17[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime2_Attack_full.png", window, renderer, dim17, correspondance17, 10);
                break;
            case SLIME3ATTACK: 
                a[i]->nb_anim = 4;

                int tableau18[] = {10, 10, 10, 10}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau18[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime3_Attack_full.png", window, renderer);
                int dim18[3] = {4, 10};
                int correspondance18[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime3_Attack_full.png", window, renderer, dim18, correspondance18, 10);
                break;
            case SLIME1DEATH: 
                a[i]->nb_anim = 4;

                int tableau19[] = {10, 10, 10, 10}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau19[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime1_Death_full.png", window, renderer);
                int dim19[3] = {4, 10};
                int correspondance19[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime1_Death_full.png", window, renderer, dim19, correspondance19, 10);
                break;
            case SLIME2DEATH: 
                a[i]->nb_anim = 4;

                int tableau20[] = {10, 10, 10, 10}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau20[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime2_Death_full.png", window, renderer);
                int dim20[3] = {4, 10};
                int correspondance20[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime2_Death_full.png", window, renderer, dim20, correspondance20, 10);
                break;
            case SLIME3DEATH: 
                a[i]->nb_anim = 4;

                int tableau21[] = {10, 10, 10, 10}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau21[k];
                }

                a[i]->texture = load_texture_from_image("textures/Slime3_Death_full.png", window, renderer);
                int dim21[3] = {4, 10};
                int correspondance21[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/Slime3_Death_full.png", window, renderer, dim21, correspondance21, 10);
                break;
            case MONSTER_ATTACK: 
                a[i]->nb_anim = 4;

                int tableau22[] = {7, 7, 7, 7}; // nb de frame de chaque anim
                a[i]->duree = malloc(a[i]->nb_anim * sizeof(int));
                for (int k = 0; k < a[i]->nb_anim; k++) {
                    a[i]->duree[k] = tableau22[k];
                    //printf("anim dureeeeeeeeeeeee %d\n", a[i]->duree[k]);
                }

                a[i]->texture = load_texture_from_image("textures/monster_attack.png", window, renderer);
                int dim22[3] = {4, 7};
                int correspondance22[7] = {0, 1, 2, 3, 4, 5, 6}; 
                a[i]->tab = load_rectangle_tab2D_from_sprite("textures/monster_attack.png", window, renderer, dim22, correspondance22, 0);
                break;
        default:
            break;
        }
    }
    return a;
}

// Récup la bonne texture dans une animation_page et la met dans le renderer
void get_texture_entity(animation_page * a, int num_anim, int num_frame, SDL_Rect dest, SDL_Renderer * renderer){
    SDL_RenderCopy(renderer, a->texture, &a->tab[num_anim][num_frame], &dest);
}

// Détecte un appuie sur une touche
int is_direction_key_pressed() {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    return keystates[SDL_SCANCODE_UP] ||
           keystates[SDL_SCANCODE_DOWN] ||
           keystates[SDL_SCANCODE_LEFT] ||
           keystates[SDL_SCANCODE_RIGHT];
}

// mouvement unique réel dans une direction si possible
void movement(entity *e, maze *m) {

    switch (e->direction) {
        case 0: e->x--; break; // gauche
        case 1: e->x++; break; // droite
        case 2: e->y--; break; // haut
        case 3: e->y++; break; // bas
    }
}

// vérifie si on peut se déplacer dans cette direction
int verif_direction(entity * player, maze *m, int sensibilite) {
    int x = player->x;
    int y = player->y;
    int dim = m->dim_case;
    int marge_x = 6;
    int marge_y = 6;
    int epaisseur_mur_fin = dim/16;
    int epaisseur_gros_mur = 0;
    int marge_slide = dim/3;
    int marge_slide_gros_murs = dim/3;

    int bord_gauche = player->x_draw + marge_x;
    int bord_droit  = player->x_draw + dim-marge_x;
    int bord_haut   = player->y_draw + marge_y;
    int bord_bas    = player->y_draw + dim-marge_y;
    int index;

    //printf("verif direction: bb: %d bh: %d  et y: %d x: %d dim :%d\n", bord_bas, bord_haut,(player->y*dim), player->x*dim, dim);

    switch (player->direction) {
        case 0: // case de gauche = 0 1 2 3 8 9 10 11
            if (x == 0) return 0;
            index = (x - 1) + y * m->longueur;
            if((m->construction[index] == 0)||(m->construction[index] == 1)){
                return 1;
            }else if((m->construction[index] == 2)||(m->construction[index] == 3)){ // si ya un mur en haut sur la gauche
                if(bord_haut > (player->y)*dim + epaisseur_gros_mur){ // le bord haut doit etre en dessous du mur haut gauche
                    return 1;
                }else if(bord_haut > (player->y)*dim - marge_slide_gros_murs){ // decalage vers le bas
                    //printf("slide vers le bas\n");
                    player->y_draw += sensibilite;
                }
            }else if((m->construction[index] == 8) || (m->construction[index] == 9)){ // si ya un mur en bas à gauche
                if((bord_bas < (player->y+1)*dim - epaisseur_mur_fin)){ // si on se prend pas le mur bas gauche
                    return 1;
                }else if(bord_bas < (player->y+1)*dim + marge_slide){ // decalage vers la haut
                    //printf("slide vers le haut\n");
                    player->y_draw -= sensibilite;
                }
            }else if((m->construction[index] == 10) || (m->construction[index] == 11)){ // si ya un mur en haut et en bas
                if((bord_haut > (player->y)*dim + epaisseur_gros_mur)&&((bord_bas < (player->y+1)*dim - epaisseur_mur_fin))){ // si on passe entre les deux
                    return 1;
                }else if(bord_haut > (player->y)*dim + epaisseur_gros_mur){ // si ya un pb avec le mur du bas (pas de pb avec le haut)
                    if(bord_bas < (player->y+1)*dim + marge_slide){ // decalage vers la haut
                        //printf("slide vers le haut\n");
                        if(bord_haut - sensibilite > (player->y)*dim + epaisseur_gros_mur){
                            player->y_draw -= sensibilite;
                        }else{
                            player->y_draw -= sensibilite - (bord_haut-(player->y)*dim + epaisseur_gros_mur);
                        }
                    }
                }else if(bord_bas < (player->y+1)*dim - epaisseur_mur_fin){ // si ya un pb avec le mur du haut
                    if(bord_haut > (player->y)*dim - marge_slide_gros_murs){ // decalage vers le bas
                        //printf("slide vers le bas\n");
                        if(bord_bas - sensibilite > (player->y+1)*dim - epaisseur_mur_fin){
                            player->y_draw += sensibilite;
                        }else{
                            player->y_draw += sensibilite - (bord_haut-(player->y)*dim + epaisseur_gros_mur);
                        }
                    }
                }else{ // si ya un pb avec le mur du haut
                    if(bord_haut > (player->y)*dim - marge_slide_gros_murs){ // decalage vers le bas
                        //printf("slide vers le bas\n");
                        if(bord_bas - sensibilite > (player->y+1)*dim - epaisseur_mur_fin){
                            player->y_draw += sensibilite;
                        }else{
                            player->y_draw += sensibilite - (bord_haut-(player->y)*dim + epaisseur_gros_mur);
                        }
                    }
                }
            }
            break;

        case 1: // case de droite = 0 2 4 8 6 10 12 14
            if (x == m->longueur-1) return 0;
            index = (x + 1) + y * m->longueur;
            if((m->construction[index] == 0)||(m->construction[index] == 4)){
                return 1;
            }else if((m->construction[index] == 2)||(m->construction[index] == 6)){ // si ya un mur en haut sur la droite
                if(bord_haut > (player->y)*dim + epaisseur_gros_mur){ // le bord haut doit etre en dessous du mur haut droite
                    return 1;
                }else if(bord_haut > (player->y)*dim - marge_slide_gros_murs){ // decalage vers le bas
                    //printf("slide vers le bas\n");
                    player->y_draw += sensibilite;
                }
            }else if((m->construction[index] == 8) || (m->construction[index] == 12)){ // si ya un mur en bas
                if((bord_bas < (player->y+1)*dim - epaisseur_mur_fin)){ // si on se prend pas le mur bas droite
                    if((index-m->longueur < m->longueur)&&((m->construction[index-m->longueur] == 8) || (m->construction[index-m->longueur] == 12))){ // si la case de droite au dessus a un mur bas et pas de mur gauche
                        if(bord_haut > (player->y)*dim){ // le bord haut du perso doit etre en dessous 
                            return 1;
                        }else if(bord_bas < (player->y+1)*dim + marge_slide_gros_murs){ // decalage vers le bas
                            //printf("slide vers le bas\n");
                            player->y_draw += sensibilite;
                        }
                    }else{
                        return 1;
                    }
                }else if(bord_bas < (player->y+1)*dim + marge_slide){ // decalage vers la haut
                    //printf("slide vers le haut\n");
                    player->y_draw -= sensibilite;
                }
            }else if((m->construction[index] == 10) || (m->construction[index] == 14)){ // si ya un mur en haut et en bas
                if((bord_haut > (player->y)*dim + epaisseur_gros_mur)&&((bord_bas < (player->y+1)*dim - epaisseur_mur_fin))){ // si on passe entre les deux
                    return 1;
                }else if(bord_haut > (player->y)*dim + epaisseur_gros_mur){ // si ya un pb avec le mur du bas
                    if(bord_bas < (player->y+1)*dim + marge_slide){ // decalage vers la haut
                        //printf("slide vers le haut\n");
                        if(bord_haut - sensibilite > (player->y)*dim + epaisseur_gros_mur){
                            player->y_draw -= sensibilite;
                        }else{
                            player->y_draw -= sensibilite - (bord_haut-(player->y)*dim + epaisseur_gros_mur);
                        }
                    }
                }else{ // si ya un pb avec le mur du haut
                    if(bord_haut > (player->y)*dim - marge_slide_gros_murs){ // decalage vers le bas
                        //printf("slide vers le bas\n");
                        if(bord_bas - sensibilite > (player->y+1)*dim - epaisseur_mur_fin){
                            player->y_draw += sensibilite;
                        }else{
                            player->y_draw += sensibilite - (bord_haut-(player->y)*dim + epaisseur_gros_mur);
                        }
                    }
                }
            }
            break;

        case 2: // haut 0 1 2 3 4 5 6 7
            if (y == 0) return 0;
            index = x + (y-1) * m->longueur;
            if((m->construction[index] == 0)||(m->construction[index] == 2)){
                return 1;
            }else if((m->construction[index] == 1)||(m->construction[index] == 3)){ // si ya un mur à gauche au dessus
                if(bord_gauche > (player->x)*dim + epaisseur_mur_fin){ // le bord gauche doit etre à droite du mur gauche haut
                    return 1;
                }else if(bord_gauche > (player->x)*dim - marge_slide){
                    //printf("slide vers la droite\n");
                    player->x_draw += sensibilite;
                }
            }else if((m->construction[index] == 4) || (m->construction[index] == 6)){ // si ya un mur à droite au dessus
                if((bord_droit < (player->x+1)*dim - epaisseur_mur_fin)){ // si on se prend pas le mur à droite au dessus
                        return 1;
                }else if(bord_droit < (player->x+1)*dim + marge_slide){ // decalage vers la gauche
                    //printf("slide vers la gauche\n");
                    player->x_draw -= sensibilite;
                }
            }else if((m->construction[index] == 5) || (m->construction[index] == 7)){ // si ya un mur à gauche et à droite au dessus
                if((bord_droit < (player->x+1)*dim - epaisseur_mur_fin)&&(bord_gauche > (player->x)*dim + epaisseur_mur_fin)){ // si on passe entre les deux
                    return 1;
                }else if(bord_droit < (player->x+1)*dim - epaisseur_mur_fin){ // si ya un pb avec le mur gauche
                    //printf("pb mur gauche 5 ou 7 g\n");
                    if(bord_gauche > (player->x)*dim - marge_slide){ // decalage vers la droite
                        //printf("slide vers la droite\n");
                        if(player->x_draw + sensibilite < (player->x)*dim){
                            player->x_draw += sensibilite;
                        }else{
                            player->x_draw = (player->x)*dim; //+dim/2;
                        }
                        return 1;
                    }
                }else{ // si ya un pb avec le mur droite
                    //printf("pb mur droit 5 ou 7 d\n");
                    //printf("slide vers la gauche\n");
                        if(player->x_draw - sensibilite > (player->x)*dim){
                            player->x_draw -= sensibilite;
                        }else{
                            player->x_draw = (player->x)*dim; //+dim/2;
                        }
                        return 1;
                }
            }
            break;

        case 3: // bas 0 1 4 8 5 9 12 13
            if (y == m->hauteur -1) return 0;
            index = x + (y+1) * m->longueur;
            if((m->construction[index] == 0)||(m->construction[index] == 8)){
                return 1;
            }else if((m->construction[index] == 1)||(m->construction[index] == 9)){ // si ya un mur à gauche en dessous
                if(bord_gauche > (player->x)*dim + epaisseur_mur_fin){ // le bord gauche doit etre à droite du mur gauche bas
                    return 1;
                }else if(bord_gauche > (player->x)*dim - marge_slide){
                    //printf("slide vers la droite\n");
                    player->x_draw += sensibilite;
                }
            }else if((m->construction[index] == 4) || (m->construction[index] == 12)){ // si ya un mur à droite en dessous
                if((bord_droit < (player->x+1)*dim - epaisseur_mur_fin)){ // si on se prend pas le mur à droite en dessous
                        return 1;
                }else if(bord_droit < (player->x+1)*dim + marge_slide){ // decalage vers la gauche
                    //printf("slide vers la gauche\n");
                    player->x_draw -= sensibilite;
                }
            }else if((m->construction[index] == 5) || (m->construction[index] == 13)){ // si ya un mur à gauche et à droite en dessous
                if((bord_droit < (player->x+1)*dim - epaisseur_mur_fin)&&(bord_gauche > (player->x)*dim + epaisseur_mur_fin)){ // si on passe entre les deux
                    return 1;
                }else if(bord_droit < (player->x+1)*dim - epaisseur_mur_fin){ // si ya un pb avec le mur gauche
                    if(bord_gauche > (player->x)*dim - marge_slide){ // decalage vers la droite
                        //printf("slide vers la droite\n");
                        if(player->x_draw + sensibilite < (player->x)*dim){
                            player->x_draw += sensibilite;
                        }else{
                            player->x_draw = (player->x)*dim; //+dim/2;
                        }
                        return 1;
                    }
                }else{ // si ya un pb avec le mur droite
                    if(bord_droit < (player->x+1)*dim + marge_slide){ // decalage vers la gauche
                        //printf("slide vers la gauche\n");
                        if(player->x_draw - sensibilite > (player->x)*dim){
                            player->x_draw -= sensibilite;
                        }else{
                            player->x_draw = (player->x)*dim; //+dim/2;
                        }
                        return 1;
                    }
                }
            }
            break;

        default:
            return 0;
    }
    return 0;
}

// renvoi une direction en fonction de la fleche
int change_direction(){
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_UP]) {
        return 2;
    }
    if (keystates[SDL_SCANCODE_DOWN]) {
        return 3;
    }
    if (keystates[SDL_SCANCODE_LEFT]) {
        return 0;
    }
    if (keystates[SDL_SCANCODE_RIGHT]) {
        return 1;
    }
    return 0;
}

// fais un mouvement graphique
void micro_movement(int sensibilite, entity *  e){
    switch (e->direction){
    case 0:
        e->x_draw -= sensibilite;
        break;
    case 1:
        e->x_draw += sensibilite;
        break;
    case 2:
        e->y_draw -= sensibilite;
        break;
    case 3:
        e->y_draw += sensibilite;
        break;
    default:
        break;
    }
}

void micro_movement_inverse(int sensibilite, entity *  e){
    switch (e->direction){
    case 0:
        e->x_draw += sensibilite;
        break;
    case 1:
        e->x_draw -= sensibilite;
        break;
    case 2:
        e->y_draw += sensibilite;
        break;
    case 3:
        e->y_draw -= sensibilite;
        break;
    default:
        break;
    }
}

int changement_case(entity *player, maze *m) {
    int dim = m->dim_case;
    int marge_x = 6;
    int marge_y = 6;

    int bord_gauche = player->x_draw + marge_x;
    int bord_droit  = player->x_draw + dim - marge_x;
    int bord_haut   = player->y_draw + marge_y;
    int bord_bas    = player->y_draw + dim - marge_y;

    int centre_x = player->x_draw + dim/2;
    int centre_y = player->y_draw + dim/2;

    //printf("direction c_case : %d\n", player->direction);
    //printf("g: %d d :%d h:%d b:%d \n", bord_gauche, bord_droit, bord_haut, bord_bas);
    switch (player->direction) {
        case 0: // gauche
            if ((bord_droit < (player->x+1)*dim)&&(bord_gauche < player->x*dim)){ 
                //printf("values gauche:%d  %d\n", ((player->x+1)*dim), player->x*dim);
                if(centre_x < (player->x)*dim){
                   return 2; 
                }
                return 1;
            }
            break;
        case 1: // droite
            if ((bord_gauche > (player->x)*dim)&&(bord_droit > (player->x + 1)*dim)){ 
                //printf("values droite:%d  %d\n", ((player->x)*dim), (player->x+1)*dim);
                if(centre_x > (player->x+1)*dim){
                   return 2; 
                }
                return 1;
            }
            break;
        case 2: // haut
            if ((bord_bas < (player->y+1)*dim)&&(bord_haut < (player->y)*dim)){ 
                //printf("values haut: %d < %d  et %d < %d\n", bord_bas, ((player->y+1)*dim), bord_haut, player->y*dim);
                if(centre_y < (player->y)*dim){
                   return 2; 
                }
                return 1;
            }
            break;
        case 3: // bas
            if ((bord_haut > (player->y)*dim)&&(bord_bas > (player->y+1)*dim)){
                //printf("values bas:%d  %d\n", ((player->y)*dim), (player->y+1)*dim);
                if(centre_y > (player->y+1)*dim){
                   return 2; 
                }
                return 1;
            }
            break;
    }

    return 0;
}

int jump_over_wall(entity * player, maze * m, int x_old, int y_old){
    if((x_old != player->x)&&(y_old != player->y)){
        switch (player->direction){
            case 0:
                if((m->construction[player->x] == 4)||(m->construction[player->x] == 5)||(m->construction[player->x] == 6)||(m->construction[player->x] == 7)||(m->construction[player->x] == 12)||(m->construction[player->x] == 13)||(m->construction[player->x] == 14)||(m->construction[player->x] == 15)){
                    return 1;
                }
                break;
            case 1:
                if((m->construction[player->x] == 1)||(m->construction[player->x] == 3)||(m->construction[player->x] == 5)||(m->construction[player->x] == 7)||(m->construction[player->x] == 9)||(m->construction[player->x] == 13)||(m->construction[player->x] == 11)||(m->construction[player->x] == 15)){
                    return 1;
                }
                break;
            case 2:
                if(m->construction[player->y] >= 8){
                    return 1;
                }
                break;
            case 3:
                if((m->construction[player->y] == 2)||(m->construction[player->y] == 3)||(m->construction[player->y] == 6)||(m->construction[player->y] == 7)||(m->construction[player->y] == 10)||(m->construction[player->x] == 11)||(m->construction[player->x] == 14)||(m->construction[player->x] == 15)){
                    return 1;
                }
                break;
            default:
                break;
        }
    }
    //printf("non jump dir:%d\n", player->direction);
    return 0;
}

// gère les deplacements d'un joueur 
void smooth_player_movement(entity * player, maze * m, SDL_Renderer * renderer, SDL_Window * window,  int w_x, int w_y, int it, int animation_p_attack, int animation_m_attack){
    int correspondance[4] = {2,3,1,0};
    float SPEED_MIN = 0.08*m->dim_case;
    float SPEED_MAX = 0.27*m->dim_case;
    float ACCEL_INCREMENT = (SPEED_MAX-SPEED_MIN)/45;

    if(m->poids[player->x + player->y*m->longueur] == 1){
        SPEED_MIN = 0.15*m->dim_case;
        SPEED_MAX = 0.37*m->dim_case;
        ACCEL_INCREMENT = (SPEED_MAX-SPEED_MIN)/35;
    }else if(m->poids[player->x + player->y*m->longueur] == 2){
        SPEED_MIN = 0.11*m->dim_case;
        SPEED_MAX = 0.32*m->dim_case;
        ACCEL_INCREMENT = (SPEED_MAX-SPEED_MIN)/40;
    }else if(m->poids[player->x + player->y*m->longueur] == 6){
        SPEED_MIN = 0.06*m->dim_case;
        SPEED_MAX = 0.22*m->dim_case;
        ACCEL_INCREMENT = (SPEED_MAX-SPEED_MIN)/55;
    }else if(m->poids[player->x + player->y*m->longueur] == 8){
        SPEED_MIN = 0.04*m->dim_case;
        SPEED_MAX = 0.17*m->dim_case;
        ACCEL_INCREMENT = (SPEED_MAX-SPEED_MIN)/60;
    }
    //printf("min %f max %f acc %f\n", SPEED_MIN, SPEED_MAX, ACCEL_INCREMENT);

    if (is_direction_key_pressed()) {
        int new_dir = change_direction();
        if (new_dir != player->direction) {
            player->direction = new_dir;
        } else {
            if (player->speed < SPEED_MAX) {
                player->speed += ACCEL_INCREMENT;
                if (player->speed > SPEED_MAX) player->speed = SPEED_MAX;
            }
        }

        if(player->speed > SPEED_MAX){
            //printf("modif vitesse : %f %f\n", player->speed, SPEED_MAX);
            player->speed = (SPEED_MAX+SPEED_MIN)/2;
        }

        player->gliding = 0;
        int x_old = player->x; int y_old = player->y;
        micro_movement((int)player->speed, player);
        if(!jump_over_wall(player, m, x_old, y_old)){
            int c = changement_case(player, m);
            if (c != 0) {
                if (verif_direction(player, m, player->speed)) {
                    if (c == 2) {
                        movement(player, m); 
                    }
                } else {
                    micro_movement_inverse((int)player->speed, player);
                    player->speed = SPEED_MIN; 
                }
            }
        }else{
            micro_movement_inverse((int)player->speed, player);
            player->speed = SPEED_MIN; 
        }
        if((animation_p_attack == -1)&&(animation_m_attack == -1)){
            if(player->speed > 8){
                int taille_point = m->dim_case;
                SDL_Rect dest = {player->x_draw, player->y_draw, taille_point, taille_point};
                get_texture_entity(player->feuille_animation3, correspondance[player->direction], it % player->feuille_animation3->duree[correspondance[player->direction]], dest, renderer);
            }else{ 
                int taille_point = m->dim_case;
                SDL_Rect dest = {player->x_draw, player->y_draw, taille_point, taille_point};
                get_texture_entity(player->feuille_animation, correspondance[player->direction], it % player->feuille_animation->duree[correspondance[player->direction]], dest, renderer);
            }
        }
    } else {
        if (player->speed > 0.4f) {
            player->gliding = 1;
            int x_old = player->x; int y_old = player->y;
            micro_movement((int)player->speed, player);

            if (!verif_direction(player, m, player->speed)||jump_over_wall(player, m, x_old, y_old)) {
                micro_movement_inverse((int)player->speed, player);
            }

            switch (m->poids[player->x + player->y*m->longueur]){
                case 1:
                    player->speed *= 0.9f; 
                    break;
                case 2:
                    player->speed *= 0.8f; 
                    break;
                case 4:
                    player->speed *= 0.6f; 
                    break;
                case 6:
                    player->speed *= 0.4f; 
                    break;
                case 8:
                    player->speed *= 0.2f; 
                    break;
                default:
                    break;
            }
            if((animation_p_attack == -1)&&(animation_m_attack == -1)){
                int taille_point = m->dim_case;
                SDL_Rect dest = {player->x_draw, player->y_draw, taille_point, taille_point};
                get_texture_entity(player->feuille_animation, correspondance[player->direction], it % player->feuille_animation->duree[correspondance[player->direction]], dest, renderer);
            }
        } else {
            if((animation_p_attack == -1)&&(animation_m_attack == -1)){
                int taille_point = m->dim_case;
                SDL_Rect dest = {player->x_draw, player->y_draw, taille_point, taille_point};
                get_texture_entity(player->feuille_animation2, correspondance[player->direction], ((int)it / 4) % player->feuille_animation2->duree[correspondance[player->direction]], dest, renderer);
            }
        }

        //son de mouvement
        // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        //     printf("Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
        //     return 1;
        // }
        
        // Mix_Chunk * pas = Mix_LoadWAV("./son/pas.wav");
        // if (!pas) {
        //     printf("Erreur chargement pas : %s\n", Mix_GetError());
        // }
        // else {
        //     Mix_PlayChannel(0, pas,0);
        // }
    }
    //printf("min %f max %f acc %f speed %f\n", SPEED_MIN, SPEED_MAX, ACCEL_INCREMENT, player->speed);

}

void anim_switching_light(int switching_light, entity * player, SDL_Renderer * renderer, maze * m){
    int correspondance[4] = {2,3,1,0};
    int taille_point = m->dim_case;
    SDL_Rect dest = {player->x_draw, player->y_draw, taille_point, taille_point};

    /*if(switching_light < 50){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 4, dest, renderer);
    }else if(switching_light < 100){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 3, dest, renderer);
    }else if(switching_light < 150){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 2, dest, renderer);
    }else if(switching_light < 200){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 1, dest, renderer);
    }else{
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 0, dest, renderer);
    }*/
    if(switching_light < 25){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 7, dest, renderer);
    }else if(switching_light < 50){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 6, dest, renderer);
    }else if(switching_light < 75){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 5, dest, renderer);
    }else if(switching_light < 100){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 4, dest, renderer);
    }else if(switching_light < 125){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 3, dest, renderer);
    }else if(switching_light < 150){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 2, dest, renderer);
    }else if(switching_light < 175){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 1, dest, renderer);
    }else if(switching_light <= 200){
        get_texture_entity(player->feuille_animation4, correspondance[player->direction], 0, dest, renderer);
    }
}

// pour savoir où le joueur va
int calcul_direction(int pos_actuelle, int longueur, int destination){
    if(pos_actuelle + longueur == destination ){
        return 3; // bas
    }
    if(pos_actuelle - longueur == destination ){
        return 2; // haut
    }
    if(pos_actuelle + 1 == destination ){
        return 1; // droite
    }
    if(pos_actuelle - 1 == destination ){
        return 0; // gauche
    }
    return -1;
}

void monster_icon_movement(SDL_Renderer * renderer, entity * monster, int next_step, maze * m, int freq_anim, int mode_hunt, int light, int light_radius, entity * player, int exit_open){
    
    
    
    
    if(next_step != monster->x + monster->y*m->longueur){ // si ses coo reelles changent

        monster->direction = calcul_direction(monster->x + monster->y*m->longueur, m->longueur, next_step);
        monster->x = next_step%m->longueur;
        monster->y = next_step/m->longueur;
        /*monster->x_draw = monster->x * m->dim_case;
        monster->y_draw = monster->y * m->dim_case;*/

        if(mode_hunt == -1){
            monster->speed = (0.3*m->dim_case + 0.08*m->dim_case)/4;
            if(m->poids[monster->x + monster->y*m->longueur] == 1){
                monster->speed = (0.4*m->dim_case + 0.15*m->dim_case)/4;
            }else if(m->poids[monster->x + monster->y*m->longueur] == 2){
                monster->speed = (0.35*m->dim_case+0.11*m->dim_case)/4;
            }else if(m->poids[monster->x + monster->y*m->longueur] == 6){
                monster->speed = (0.25*m->dim_case + 0.06*m->dim_case)/4;
            }else if(m->poids[monster->x + monster->y*m->longueur] == 8){
                monster->speed = (0.2*m->dim_case + 0.04*m->dim_case)/4;
            }
        }else if(mode_hunt == 1){
            monster->speed = (0.3*m->dim_case + 0.08*m->dim_case)/2;
            if(m->poids[monster->x + monster->y*m->longueur] == 1){
                monster->speed = (0.4*m->dim_case + 0.15*m->dim_case)/2;
            }else if(m->poids[monster->x + monster->y*m->longueur] == 2){
                monster->speed = (0.35*m->dim_case+0.11*m->dim_case)/2;
            }else if(m->poids[monster->x + monster->y*m->longueur] == 6){
                monster->speed = (0.25*m->dim_case + 0.06*m->dim_case)/2;
            }else if(m->poids[monster->x + monster->y*m->longueur] == 8){
                monster->speed = (0.2*m->dim_case + 0.04*m->dim_case)/2;
            }
        }
    }

    switch (monster->direction){
        case 0:
            if(monster->x_draw > monster->x*m->dim_case){
                monster->x_draw -= monster->speed;
            }
            break;
        case 1:
            if(monster->x_draw < monster->x*m->dim_case){
                monster->x_draw += monster->speed;
            }
            break;
        case 2:
            if(monster->y_draw > monster->y*m->dim_case){
                monster->y_draw -= monster->speed;
            }
            break;
        case 3:
            if(monster->y_draw < monster->y*m->dim_case){
                monster->y_draw += monster->speed;
            }
            break;
        default:
            break;
    }

    
    SDL_Rect r = {monster->x_draw, monster->y_draw, m->dim_case, m->dim_case};
    int cor[4] = {2,1,3,0};
    // si le monstre est assez proche ou que la lumiere est allumé
    if((exit_open == 1)||(((light==1)&&(sqrt((monster->x_draw - player->x_draw)*(monster->x_draw - player->x_draw) + (monster->y_draw - player->y_draw)*(monster->y_draw  - player->y_draw)) < light_radius))||
        ((light==-1)&&(sqrt((monster->x_draw - player->x_draw)*(monster->x_draw  - player->x_draw) + (monster->y_draw  - player->y_draw)*(monster->y_draw  - player->y_draw)) < m->dim_case)))){
        get_texture_entity(monster->feuille_animation3, monster->direction[cor], freq_anim%4, r, renderer);
    }else{
        if(mode_hunt == 1){
            get_texture_entity(monster->feuille_animation2, 0, freq_anim%8, r, renderer);
        }else{
            get_texture_entity(monster->feuille_animation, 0, freq_anim%8, r, renderer);
        }
    }
}

 
void player_attack_monster(SDL_Renderer * renderer, entity * player, entity * monster, maze * m, int * animation_p_attack, point_interet * p, int freq_anim, int * is_monster_killed){
    //printf("%d\n", *animation_p_attack);
    if(*animation_p_attack == -1){ // si on est pas entrain d'attaquer
        if((player->x == monster->x)&&(player->y == monster->y)){
            *animation_p_attack = 9;
        }
    }else{
        int correspondance[4] = {2,3,1,0};
        SDL_Rect r = {player->x_draw, player->y_draw, m->dim_case, m->dim_case};
        get_texture_entity(player->feuille_animation5, correspondance[player->direction], 9-*animation_p_attack, r, renderer);
        if(freq_anim%2 == 0){
            *animation_p_attack -= 1;
        }

        if(*animation_p_attack == -1){
            monster->x = p->spawn_monster%m->longueur;
            monster->y = p->spawn_monster/m->longueur;
            monster->x_draw = monster->x*m->dim_case;
            monster->y_draw = monster->y*m->dim_case;
            *is_monster_killed = 1;;
        }
    }
}

void monster_attack_player(SDL_Renderer * renderer, entity * player, entity * monster, maze * m, point_interet * p, int freq_anim, int w_x, int w_y){

  

    SDL_Rect r = {w_x/4, w_y/3, w_x/4, w_y/4};
    SDL_Rect r2 = {w_x/2, w_y/2, w_x/4, w_y/4};
    SDL_SetRenderTarget(renderer, NULL);

    for(int i=0;i<10;i++){
        //printf("test 0 %d\n", monster->feuille_animation4==NULL);
        SDL_RenderClear(renderer);
        if(i<7){
            get_texture_entity(monster->feuille_animation4, 1, i, r, renderer);
        }else{
            get_texture_entity(monster->feuille_animation4, 1, 6, r, renderer);
        }
        get_texture_entity(player->feuille_animation6, 0, i, r2, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(350);
    }
    
}

void player_anime_fin(SDL_Renderer * renderer, entity * player, entity * monster, maze * m, point_interet * p, int freq_anim, int w_x, int w_y){

    

    SDL_Rect r = {w_x/3, w_y/3, w_x/3, w_y/3};
    SDL_SetRenderTarget(renderer, NULL);

    for(int i=0;i<10;i++){
        //printf("test 0 %d\n", monster->feuille_animation4==NULL);
        SDL_RenderClear(renderer);
        get_texture_entity(player->feuille_animation5, 0, i, r, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(350);
    }
    
}

