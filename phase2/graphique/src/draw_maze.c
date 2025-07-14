#include "draw_maze.h"
#include <SDL2/SDL_mixer.h>

#define EPAISSEUR 3

void draw_mur_gauche(SDL_Renderer * renderer, int i, int j, int dim_case) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    for (int offset = 0; offset < EPAISSEUR; ++offset) {
        SDL_RenderDrawLine(renderer, i + offset, j, i + offset, j + dim_case);
    }
    //printf("mur gauche %d %d %d %d\n", i, j, i, j+dim_case);
}

void draw_mur_droite(SDL_Renderer * renderer, int i, int j, int dim_case) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    for (int offset = 0; offset < EPAISSEUR; ++offset) {
        SDL_RenderDrawLine(renderer, i + dim_case - offset, j, i + dim_case - offset, j + dim_case);
    }
}

void draw_mur_haut(SDL_Renderer * renderer, int i, int j, int dim_case) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    for (int offset = 0; offset < EPAISSEUR; ++offset) {
        SDL_RenderDrawLine(renderer, i, j + offset, i + dim_case, j + offset);
    }
}

void draw_mur_bas(SDL_Renderer * renderer, int i, int j, int dim_case) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    for (int offset = 0; offset < EPAISSEUR; ++offset) {
        SDL_RenderDrawLine(renderer, i, j + dim_case - offset, i + dim_case, j + dim_case - offset);
    }
}
 

int draw_maze(SDL_Renderer * renderer, int window_size_x,int window_size_y, int * construction_mur, int nb_noeud, int taille[2]){
    int dim_case;

    if(window_size_y / taille[0] > window_size_x / taille[1]){
        dim_case = window_size_x / taille[1];
    }else{
        dim_case = window_size_y / taille[0];
    }

    int i = 0;
    int j = -1;
    for(int k=0;k<nb_noeud;k++){
        if(k%taille[1]==0){
            j++;
            i = 0;
        }        
        //printf("taille case = %d, i %d, j %d, k %d\n", dim_case, i, j, k);
        switch (construction_mur[k]){
            case 1:
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 2:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 4:
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 8: 
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 3:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 5:
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 6:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 9:
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 12:
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 10:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 7:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 11:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 13:
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 14:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            case 15:
                draw_mur_haut(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_gauche(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_droite(renderer, i*dim_case, j*dim_case, dim_case);
                draw_mur_bas(renderer, i*dim_case, j*dim_case, dim_case);
                break;
            default:
                break;
        }
        i++;

    }

    return dim_case;
}

maze * get_labyrinthe_map_without_texture(SDL_Window * window, SDL_Renderer * renderer, labyrinthe * l){

    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);
    int taille_labyrinthe[2] = {l->nb_ligne, l->nb_colonne};
    int nb_noeud_maze = l->nb_colonne*l->nb_ligne;

   

    SDL_Texture *map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);
    SDL_SetRenderTarget(renderer, map); // dessine dans la map
    SDL_RenderClear(renderer); // efface l’ancien contenu
    int dim_case = draw_maze(renderer, w_x, w_y, l->construction, nb_noeud_maze, taille_labyrinthe);
    SDL_SetRenderTarget(renderer, NULL); // revient au rendu normal

    maze * m = malloc(sizeof(maze));
    m->map = map;
    m->dim_case = dim_case;
    m->longueur = taille_labyrinthe[1];
    m->hauteur = taille_labyrinthe[0];
    m->nb_noeud = nb_noeud_maze;
    m->construction = l->construction;
    
    return m;
}


int draw_maze_texture(SDL_Renderer *renderer, int window_size_x, int window_size_y, int *construction_mur, int nb_noeud, int taille[2], SDL_Texture **textures, SDL_Rect ** tab_rect, SDL_Texture ** cas_speciaux, int * biomes, SDL_Window * window) {    
    int dim_case; 

    SDL_Texture * texture_water_top[4];
    texture_water_top[0] = load_texture_from_image("textures/biomes/water_top_full.png", window, renderer);
    texture_water_top[1] = load_texture_from_image("textures/biomes/water_top_mid.png", window, renderer);
    texture_water_top[2] = load_texture_from_image("textures/biomes/water_top_left.png", window, renderer);
    texture_water_top[3] = load_texture_from_image("textures/biomes/water_top_right.png", window, renderer);

    SDL_Texture * texture_water_bot[4];
    texture_water_bot[0] = load_texture_from_image("textures/biomes/water_bot_full.png", window, renderer);
    texture_water_bot[1] = load_texture_from_image("textures/biomes/water_bot_mid.png", window, renderer);
    texture_water_bot[2] = load_texture_from_image("textures/biomes/water_bot_left.png", window, renderer);
    texture_water_bot[3] = load_texture_from_image("textures/biomes/water_bot_right.png", window, renderer);

    SDL_Texture * texture_water_left[4];
    texture_water_left[0] = load_texture_from_image("textures/biomes/water_right_full.png", window, renderer);
    texture_water_left[1] = load_texture_from_image("textures/biomes/water_right_mid.png", window, renderer);
    texture_water_left[2] = load_texture_from_image("textures/biomes/water_right_bot.png", window, renderer);
    texture_water_left[3] = load_texture_from_image("textures/biomes/water_right_top.png", window, renderer);

    SDL_Texture * texture_water_right[4];
    texture_water_right[0] = load_texture_from_image("textures/biomes/water_left_full.png", window, renderer);
    texture_water_right[1] = load_texture_from_image("textures/biomes/water_left_mid.png", window, renderer);
    texture_water_right[2] = load_texture_from_image("textures/biomes/water_left_bot.png", window, renderer);
    texture_water_right[3] = load_texture_from_image("textures/biomes/water_left_top.png", window, renderer);

    if(window_size_y / taille[0] > window_size_x / taille[1]){
        dim_case = window_size_x / taille[1];
    }else{
        dim_case = window_size_y / taille[0];
    }

    //printf("w : %d %d %d\n",window_size_x, window_size_y, construction_mur[0]);
    //printf("w : %d %d %d %d %d %d %d\n",window_size_x, window_size_y, construction_mur[0], nb_noeud, taille[0], taille[1]);

    int i = 0;
    int j = -1;
    SDL_Texture * pick_t;
    SDL_Rect * pick_rect;
    int preced = -1;
    int cas_spe = 0;
    int correspondance[9] = {0, 4, 5, 0, 0, 0, 6, 0, 7}; // corespondance poids/biome dans le tab pour cas classique
    int correspondance_spe[9] = {0, 10, 20, 0, 0, 0, 30, 0, 40}; // corespondance poids/biome dans le tab pour cas spe

    for (int k = 0; k < nb_noeud; k++) {
        if (k % taille[1] == 0) {
            j++;
            i = 0;
        }
        int val = construction_mur[k];
        SDL_Rect dest = { i * dim_case, j * dim_case, dim_case, dim_case };
        int p = rand()%100;
        cas_spe = 0;
        if(biomes[k] == 4){ // variation aleatoire de textures biome normal
            if(p<10){
                pick_t = textures[0];
                pick_rect = tab_rect[0];
                preced = -1;
            }else if(p<70){
                pick_t = textures[1];
                pick_rect = tab_rect[1];
                preced = -1;
            }else if((p<85)&&(preced != 1)){
                pick_t = textures[2];
                pick_rect = tab_rect[2];
                preced = 1;
            }else if((p<100)&&(preced != 1)){
                pick_t = textures[3];
                pick_rect = tab_rect[3];
                preced = 1;
            }else{
                pick_t = textures[1];
                pick_rect = tab_rect[1];
                preced = -1;
            }
        }else{
            pick_t = textures[correspondance[biomes[k]]]; // on recupe la bonne sprite sheet qui correspond au biome
            pick_rect = tab_rect[correspondance[biomes[k]]];
        }

        // Gère les cas spéciaux d'affichage
        if(val == 8){
            if((k-taille[1] >= 0)&&(construction_mur[k-taille[1]] < 8)){ // si au dessus ya pas de mur du bas
                if((k-1 >= 0)&&((construction_mur[k-1] == 2)|| (construction_mur[k-1] == 3)|| (construction_mur[k-1] == 10)|| (construction_mur[k-1] == 11))){ // si le bloc de gauche a un mur du haut mais pas de mur de droite
                    if((k+1 < nb_noeud)&&((construction_mur[k+1] == 2)|| (construction_mur[k+1] == 6)|| (construction_mur[k+1] == 10)|| (construction_mur[k+1] == 14))){ // si le bloc de droite a un mur du haut mais pas de mur de gauche   
                        if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7)){ // si le bloc haut a G et D
                            pick_t = cas_speciaux[5 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }else if((construction_mur[k-taille[1]] == 1) || (construction_mur[k-taille[1]] == 3)){ // si il a que G
                            pick_t = cas_speciaux[6 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }else if((construction_mur[k-taille[1]] == 4) || (construction_mur[k-taille[1]] == 6)){ // si il a que D 
                            pick_t = cas_speciaux[4 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }
                    }else{ // si ya que G qui nous interesse
                        if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 1) || (construction_mur[k-taille[1]] == 3)){ // si ya un mur G au dessus
                            pick_t = cas_speciaux[6 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }
                    }
                }else if((k+1 < nb_noeud)&&((construction_mur[k+1] == 2)|| (construction_mur[k+1] == 6)|| (construction_mur[k+1] == 10)|| (construction_mur[k+1] == 14))){ // si ya que D qui nous interesse
                    if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 4) || (construction_mur[k-taille[1]] == 6)){ // si ya un mur en haut à D
                        pick_t = cas_speciaux[4 + correspondance_spe[biomes[k]]];
                        cas_spe = 1;
                    }
                }
            }
        }else if(val == 1){
            if((k-taille[1] >= 0)&&(construction_mur[k-taille[1]] < 8)){ // si au dessus ya pas de mur du bas
                if((k+1 < nb_noeud)&&((construction_mur[k+1] == 2)|| (construction_mur[k+1] == 6)|| (construction_mur[k+1] == 10)|| (construction_mur[k+1] == 14))){ // si le bloc de droite a un mur du haut mais pas de mur de gauche   
                    if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 4) || (construction_mur[k-taille[1]] == 6)){ // si ya un mur en haut à D
                        pick_t = cas_speciaux[0 + correspondance_spe[biomes[k]]];
                        cas_spe = 1;
                    }
                }
            }
        }else if(val == 4){
            if((k-taille[1] >= 0)&&(construction_mur[k-taille[1]] < 8)){ // si au dessus ya pas de mur du bas
                if((k-1 >= 0)&&((construction_mur[k-1] == 2)|| (construction_mur[k-1] == 3)|| (construction_mur[k-1] == 10)|| (construction_mur[k-1] == 11))){ // si le bloc de gauche a un mur du haut mais pas de mur de droite
                    if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 1) || (construction_mur[k-taille[1]] == 3)){ // si ya un mur G au dessus
                        pick_t = cas_speciaux[1 + correspondance_spe[biomes[k]]];
                        cas_spe = 1;
                    }
                }
            }
        }else if(val == 12){
            if((k-taille[1] >= 0)&&(construction_mur[k-taille[1]] < 8)){ // si au dessus ya pas de mur du bas
                if((k-1 >= 0)&&((construction_mur[k-1] == 2)|| (construction_mur[k-1] == 3)|| (construction_mur[k-1] == 10)|| (construction_mur[k-1] == 11))){ // si le bloc de gauche a un mur du haut mais pas de mur de droite
                    if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 1) || (construction_mur[k-taille[1]] == 3)){ // si ya un mur G au dessus
                        pick_t = cas_speciaux[3 + correspondance_spe[biomes[k]]];
                        cas_spe = 1;
                    }
                }
            }
        }else if(val == 9){
            if((k-taille[1] >= 0)&&(construction_mur[k-taille[1]] < 8)){ // si au dessus ya pas de mur du bas
                if((k+1 < nb_noeud)&&((construction_mur[k+1] == 2)|| (construction_mur[k+1] == 6)|| (construction_mur[k+1] == 10)|| (construction_mur[k+1] == 14))){ // si le bloc de droite a un mur du haut mais pas de mur de gauche   
                    if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 4) || (construction_mur[k-taille[1]] == 6)){ // si ya un mur en haut à D
                        pick_t = cas_speciaux[2 + correspondance_spe[biomes[k]]];
                        cas_spe = 1;
                    }
                }
            }
        }else if(val == 0){
            if((k-taille[1] >= 0)&&(construction_mur[k-taille[1]] < 8)){ // si au dessus ya pas de mur du bas
                if((k-1 >= 0)&&((construction_mur[k-1] == 2)|| (construction_mur[k-1] == 3)|| (construction_mur[k-1] == 10)|| (construction_mur[k-1] == 11))){ // si le bloc de gauche a un mur du haut mais pas de mur de droite
                    if((k+1 < nb_noeud)&&((construction_mur[k+1] == 2)|| (construction_mur[k+1] == 6)|| (construction_mur[k+1] == 10)|| (construction_mur[k+1] == 14))){ // si le bloc de droite a un mur du haut mais pas de mur de gauche   
                        if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7)){ // si le bloc haut a G et D
                            pick_t = cas_speciaux[8 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }else if((construction_mur[k-taille[1]] == 1) || (construction_mur[k-taille[1]] == 3)){ // si il a que G
                            pick_t = cas_speciaux[7 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }else if((construction_mur[k-taille[1]] == 4) || (construction_mur[k-taille[1]] == 6)){ // si il a que D 
                            pick_t = cas_speciaux[9 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }
                    }else{ // si ya que G qui nous interesse
                        if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 1) || (construction_mur[k-taille[1]] == 3)){ // si ya un mur G au dessus
                            pick_t = cas_speciaux[7 + correspondance_spe[biomes[k]]];
                            cas_spe = 1;
                        }
                    }
                }else if((k+1 < nb_noeud)&&((construction_mur[k+1] == 2)|| (construction_mur[k+1] == 6)|| (construction_mur[k+1] == 10)|| (construction_mur[k+1] == 14))){ // si ya que D qui nous interesse
                    if((construction_mur[k-taille[1]] == 5) || (construction_mur[k-taille[1]] == 7) || (construction_mur[k-taille[1]] == 4) || (construction_mur[k-taille[1]] == 6)){ // si ya un mur en haut à D
                        pick_t = cas_speciaux[9 + correspondance_spe[biomes[k]]];
                        cas_spe = 1;
                    }
                }
            }
        }
        if(cas_spe){
            SDL_RenderCopy(renderer, pick_t, NULL, &dest);
        }else{
            SDL_RenderCopy(renderer, pick_t, &pick_rect[val], &dest);
        }

        if((k+taille[1] < taille[1]*taille[0])&&(biomes[k+taille[1]] == 2)&&(biomes[k] == 4)){ // si la case du dessous est biome eau
            if((construction_mur[k+taille[1]] == 0)||(construction_mur[k+taille[1]] == 8)){ // si ya pas de mur en dessous
                if((construction_mur[k] == 0)||(construction_mur[k] == 2)){ // si ya pas de mur de coté
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[0], NULL, &r);
                }else if((construction_mur[k] == 1)||(construction_mur[k] == 3)){ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[3], NULL, &r);
                }else if((construction_mur[k] == 4)||(construction_mur[k] == 6)){ // si ya que un mur a droite
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[2], NULL, &r);
                }else if((construction_mur[k] == 5)||(construction_mur[k] == 7)){ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[1], NULL, &r);
                }
            }
            if((construction_mur[k+taille[1]] == 5)||(construction_mur[k+taille[1]] == 13)){ // si on passe entre 2 murs
                SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                SDL_RenderCopy(renderer, texture_water_top[1], NULL, &r);
            }
            if((construction_mur[k+taille[1]] == 4)||(construction_mur[k+taille[1]] == 12)){ // si ya un mur a droite
                if((construction_mur[k] == 1)||(construction_mur[k] == 3)){ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[1], NULL, &r);
                }else{ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[2], NULL, &r);
                }
            }if((construction_mur[k+taille[1]] == 1)||(construction_mur[k+taille[1]] == 9)){ // si ya un mur a gauche
                if((construction_mur[k] == 4)||(construction_mur[k] == 6)){ // si ya un mur a droite
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[1], NULL, &r);
                }else{ // sinon
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]+1) - dim_case/2, dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_top[3], NULL, &r);
                }
            }
        }



        if((k-taille[1] >= 0)&&(biomes[k-taille[1]] == 2)&&(biomes[k] == 4)){ // si la case du dessus est biome eau
            if((construction_mur[k-taille[1]] == 0)||(construction_mur[k-taille[1]] == 2)){ // si ya pas de mur en dessous
                if((construction_mur[k] == 0)||(construction_mur[k] == 8)){ // si ya pas de mur de coté
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[0], NULL, &r);
                }else if((construction_mur[k] == 1)||(construction_mur[k] == 9)){ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[3], NULL, &r);
                }else if((construction_mur[k] == 4)||(construction_mur[k] == 12)){ // si ya que un mur a droite
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[2], NULL, &r);
                }else if((construction_mur[k] == 5)||(construction_mur[k] == 13)){ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[1], NULL, &r);
                }
            }
            if((construction_mur[k-taille[1]] == 5)||(construction_mur[k-taille[1]] == 13)){ // si on passe entre 2 murs
                SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                SDL_RenderCopy(renderer, texture_water_bot[1], NULL, &r);
            }
            if((construction_mur[k-taille[1]] == 4)||(construction_mur[k-taille[1]] == 12)){ // si ya un mur a droite
                if((construction_mur[k] == 1)||(construction_mur[k] == 3)){ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]) , dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[1], NULL, &r);
                }else{ // si ya que un mur a gauche
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[2], NULL, &r);
                }
            }if((construction_mur[k-taille[1]] == 1)||(construction_mur[k-taille[1]] == 9)){ // si ya un mur a gauche
                if((construction_mur[k] == 4)||(construction_mur[k] == 6)){ // si ya un mur a droite
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[1], NULL, &r);
                }else{ // sinon
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case, dim_case/2};
                    SDL_RenderCopy(renderer, texture_water_bot[3], NULL, &r);
                }
            }
        }


        if((k-1 >= 0)&&(biomes[k-1] == 2)&&(biomes[k] == 4)){ // si la case de gauche est biome eau
            if((construction_mur[k-1] == 0)||(construction_mur[k-1] == 1)){ // si ya pas de mur a gauche
                if((construction_mur[k] == 0)||(construction_mur[k] == 4)){ // si ya pas de mur de haut bas
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[0], NULL, &r);
                }else if((construction_mur[k] == 2)||(construction_mur[k] == 6)){ // si ya que un mur en haut
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[2], NULL, &r);
                }else if((construction_mur[k] == 8)||(construction_mur[k] == 12)){ // si ya que un mur en bas
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[3], NULL, &r);
                }else if((construction_mur[k] == 10)||(construction_mur[k] == 14)){ // si ya un mur en haut et en bas
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[1], NULL, &r);
                }
            }
            if((construction_mur[k-1] == 10)||(construction_mur[k-1] == 11)){ // si on passe entre 2 murs
                SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                SDL_RenderCopy(renderer, texture_water_left[1], NULL, &r);
            }
            if((construction_mur[k-1] == 2)||(construction_mur[k-1] == 3)){ // si ya un mur en haut
                if((construction_mur[k] == 6)||(construction_mur[k] == 2)||(construction_mur[k] == 0)||(construction_mur[k] == 4)){ // si ya que un mur en haut ou pas de murs
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[2], NULL, &r);
                }else{ // si ya un mur en bas
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[1], NULL, &r);
                }
            }if((construction_mur[k-1] == 8)||(construction_mur[k-1] == 9)){ // si ya un mur en bas
                if((construction_mur[k] == 4)||(construction_mur[k] == 8)||(construction_mur[k] == 12)||(construction_mur[k] == 0)){ // si ya un mur que en bas au max
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[3], NULL, &r);
                }else{ // sinon
                    SDL_Rect r = {dim_case*(k%taille[1]), dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_left[1], NULL, &r);
                }
            }
        }

        if((k+1 < taille[1]*taille[0])&&(biomes[k+1] == 2)&&(biomes[k] == 4)){ // si la case de droite est biome eau
            if((construction_mur[k+1] == 0)||(construction_mur[k+1] == 4)){ // si ya pas de mur a gauche
                if((construction_mur[k] == 0)||(construction_mur[k] == 1)){ // si ya pas de mur de haut bas
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[0], NULL, &r);
                }else if((construction_mur[k] == 2)||(construction_mur[k] == 3)){ // si ya que un mur en haut
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[3], NULL, &r);
                }else if((construction_mur[k] == 8)||(construction_mur[k] == 9)){ // si ya que un mur en bas
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[2], NULL, &r);
                }else if((construction_mur[k] == 10)||(construction_mur[k] == 11)){ // si ya un mur en haut et en bas
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[1], NULL, &r);
                }
            }
            if((construction_mur[k+1] == 10)||(construction_mur[k+1] == 14)){ // si on passe entre 2 murs
                SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                SDL_RenderCopy(renderer, texture_water_right[1], NULL, &r);
            }
            if((construction_mur[k+1] == 2)||(construction_mur[k+1] == 6)){ // si ya un mur en haut
                if((construction_mur[k] == 3)||(construction_mur[k] == 2)||(construction_mur[k] == 0)||(construction_mur[k] == 1)){ // si ya que un mur en haut ou pas de murs
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[2], NULL, &r);
                }else{ // si ya un mur en bas
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[1], NULL, &r);
                }
            }if((construction_mur[k+1] == 8)||(construction_mur[k+1] == 12)){ // si ya un mur en bas
                if((construction_mur[k] == 1)||(construction_mur[k] == 8)||(construction_mur[k] == 9)||(construction_mur[k] == 0)){ // si ya un mur que en bas au max
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[3], NULL, &r);
                }else{ // sinon
                    SDL_Rect r = {dim_case*(k%taille[1])+dim_case/2, dim_case*(k/taille[1]), dim_case/2, dim_case};
                    SDL_RenderCopy(renderer, texture_water_right[1], NULL, &r);
                }
            }
        }

        i++;
    }

    return dim_case;
}


maze * get_labyrinthe_map(SDL_Window * window, SDL_Renderer * renderer, labyrinthe * l, int with_texture, int * biomes){
 
    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);
    int taille_labyrinthe[2]; taille_labyrinthe[0] = l->nb_ligne; taille_labyrinthe[1] = l->nb_colonne;
    int nb_noeud_maze = l->nb_colonne*l->nb_ligne;
    //printf("constru : %d\n", l->construction[0]);
    //labyrinthe_textuel(taille_labyrinthe[0], taille_labyrinthe[1], construction_mur);


    int dim[2] = {4, 4};
    maze * m = malloc(sizeof(maze));

    if(with_texture){
        SDL_Texture * texture[8];
        texture[0] = load_texture_from_image("textures/sheet_offi1.png", window, renderer);
        texture[1] = load_texture_from_image("textures/sheet_offi2.png", window, renderer);
        texture[2] = load_texture_from_image("textures/sheet_offi3.png", window, renderer);
        texture[3] = load_texture_from_image("textures/sheet_offi4.png", window, renderer);
        texture[4] = load_texture_from_image("textures/biomes/sheet_offi1_ice.png", window, renderer);
        texture[5] = load_texture_from_image("textures/biomes/sheet_offi1_water.png", window, renderer);
        texture[6] = load_texture_from_image("textures/biomes/sheet_offi1_swamp.png", window, renderer);
        texture[7] = load_texture_from_image("textures/biomes/sheet_offi1_sand.png", window, renderer);

        int correspondance[16] = {3 ,6 ,12 ,9 ,10 ,5 ,15 ,0 ,7 ,13 ,14 ,11 ,2 ,4 ,8 ,1}; 
        SDL_Rect * tab_rect[8];
        tab_rect[0] = load_rectangle_from_sprite("textures/sheet_offi1.png", window, renderer, dim, correspondance, 0);
        tab_rect[1] = load_rectangle_from_sprite("textures/sheet_offi2.png", window, renderer, dim, correspondance, 0);
        tab_rect[2] = load_rectangle_from_sprite("textures/sheet_offi3.png", window, renderer, dim, correspondance, 0);
        tab_rect[3] = load_rectangle_from_sprite("textures/sheet_offi4.png", window, renderer, dim, correspondance, 0);
        tab_rect[4] = load_rectangle_from_sprite("textures/biomes/sheet_offi1_ice.png", window, renderer, dim, correspondance, 0);
        tab_rect[5] = load_rectangle_from_sprite("textures/biomes/sheet_offi1_water.png", window, renderer, dim, correspondance, 0);
        tab_rect[6] = load_rectangle_from_sprite("textures/biomes/sheet_offi1_swamp.png", window, renderer, dim, correspondance, 0);
        tab_rect[7] = load_rectangle_from_sprite("textures/biomes/sheet_offi1_sand.png", window, renderer, dim, correspondance, 0);
    
        SDL_Texture * cas_speciaux[50];
        cas_speciaux[0] = load_texture_from_image("textures/Cas_speciaux/L.png", window, renderer);
        cas_speciaux[1] = load_texture_from_image("textures/Cas_speciaux/R.png", window, renderer);
        cas_speciaux[2] = load_texture_from_image("textures/Cas_speciaux/LB.png", window, renderer);
        cas_speciaux[3] = load_texture_from_image("textures/Cas_speciaux/RB.png", window, renderer);
        cas_speciaux[4] = load_texture_from_image("textures/Cas_speciaux/B1.png", window, renderer);
        cas_speciaux[5] = load_texture_from_image("textures/Cas_speciaux/B2.png", window, renderer);
        cas_speciaux[6] = load_texture_from_image("textures/Cas_speciaux/B3.png", window, renderer);
        cas_speciaux[7] = load_texture_from_image("textures/Cas_speciaux/N1.png", window, renderer);
        cas_speciaux[8] = load_texture_from_image("textures/Cas_speciaux/N2.png", window, renderer);
        cas_speciaux[9] = load_texture_from_image("textures/Cas_speciaux/N3.png", window, renderer);

        cas_speciaux[10] = load_texture_from_image("textures/biomes/Cas_speciaux/L_ice.png", window, renderer);
        cas_speciaux[11] = load_texture_from_image("textures/biomes/Cas_speciaux/R_ice.png", window, renderer);
        cas_speciaux[12] = load_texture_from_image("textures/biomes/Cas_speciaux/LB_ice.png", window, renderer);
        cas_speciaux[13] = load_texture_from_image("textures/biomes/Cas_speciaux/RB_ice.png", window, renderer);
        cas_speciaux[14] = load_texture_from_image("textures/biomes/Cas_speciaux/B1_ice.png", window, renderer);
        cas_speciaux[15] = load_texture_from_image("textures/biomes/Cas_speciaux/B2_ice.png", window, renderer);
        cas_speciaux[16] = load_texture_from_image("textures/biomes/Cas_speciaux/B3_ice.png", window, renderer);
        cas_speciaux[17] = load_texture_from_image("textures/biomes/Cas_speciaux/N1_ice.png", window, renderer);
        cas_speciaux[18] = load_texture_from_image("textures/biomes/Cas_speciaux/N2_ice.png", window, renderer);
        cas_speciaux[19] = load_texture_from_image("textures/biomes/Cas_speciaux/N3_ice.png", window, renderer);

        cas_speciaux[20] = load_texture_from_image("textures/biomes/Cas_speciaux/L_water.png", window, renderer);
        cas_speciaux[21] = load_texture_from_image("textures/biomes/Cas_speciaux/R_water.png", window, renderer);
        cas_speciaux[22] = load_texture_from_image("textures/biomes/Cas_speciaux/LB_water.png", window, renderer);
        cas_speciaux[23] = load_texture_from_image("textures/biomes/Cas_speciaux/RB_water.png", window, renderer);
        cas_speciaux[24] = load_texture_from_image("textures/biomes/Cas_speciaux/B1_water.png", window, renderer);
        cas_speciaux[25] = load_texture_from_image("textures/biomes/Cas_speciaux/B2_water.png", window, renderer);
        cas_speciaux[26] = load_texture_from_image("textures/biomes/Cas_speciaux/B3_water.png", window, renderer);
        cas_speciaux[27] = load_texture_from_image("textures/biomes/Cas_speciaux/N1_water.png", window, renderer);
        cas_speciaux[28] = load_texture_from_image("textures/biomes/Cas_speciaux/N2_water.png", window, renderer);
        cas_speciaux[29] = load_texture_from_image("textures/biomes/Cas_speciaux/N3_water.png", window, renderer);

        cas_speciaux[30] = load_texture_from_image("textures/biomes/Cas_speciaux/L_swamp.png", window, renderer);
        cas_speciaux[31] = load_texture_from_image("textures/biomes/Cas_speciaux/R_swamp.png", window, renderer);
        cas_speciaux[32] = load_texture_from_image("textures/biomes/Cas_speciaux/LB_swamp.png", window, renderer);
        cas_speciaux[33] = load_texture_from_image("textures/biomes/Cas_speciaux/RB_swamp.png", window, renderer);
        cas_speciaux[34] = load_texture_from_image("textures/biomes/Cas_speciaux/B1_swamp.png", window, renderer);
        cas_speciaux[35] = load_texture_from_image("textures/biomes/Cas_speciaux/B2_swamp.png", window, renderer);
        cas_speciaux[36] = load_texture_from_image("textures/biomes/Cas_speciaux/B3_swamp.png", window, renderer);
        cas_speciaux[37] = load_texture_from_image("textures/biomes/Cas_speciaux/N1_swamp.png", window, renderer);
        cas_speciaux[38] = load_texture_from_image("textures/biomes/Cas_speciaux/N2_swamp.png", window, renderer);
        cas_speciaux[39] = load_texture_from_image("textures/biomes/Cas_speciaux/N3_swamp.png", window, renderer);

        cas_speciaux[40] = load_texture_from_image("textures/biomes/Cas_speciaux/L_sand.png", window, renderer);
        cas_speciaux[41] = load_texture_from_image("textures/biomes/Cas_speciaux/R_sand.png", window, renderer);
        cas_speciaux[42] = load_texture_from_image("textures/biomes/Cas_speciaux/LB_sand.png", window, renderer);
        cas_speciaux[43] = load_texture_from_image("textures/biomes/Cas_speciaux/RB_sand.png", window, renderer);
        cas_speciaux[44] = load_texture_from_image("textures/biomes/Cas_speciaux/B1_sand.png", window, renderer);
        cas_speciaux[45] = load_texture_from_image("textures/biomes/Cas_speciaux/B2_sand.png", window, renderer);
        cas_speciaux[46] = load_texture_from_image("textures/biomes/Cas_speciaux/B3_sand.png", window, renderer);
        cas_speciaux[47] = load_texture_from_image("textures/biomes/Cas_speciaux/N1_sand.png", window, renderer);
        cas_speciaux[48] = load_texture_from_image("textures/biomes/Cas_speciaux/N2_sand.png", window, renderer);
        cas_speciaux[49] = load_texture_from_image("textures/biomes/Cas_speciaux/N3_sand.png", window, renderer);

        SDL_Texture *map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);
        SDL_SetRenderTarget(renderer, map); // dessine dans la map
        SDL_RenderClear(renderer); // efface l’ancien contenu 
        int dim_case = draw_maze_texture(renderer, w_x, w_y, l->construction, nb_noeud_maze, taille_labyrinthe, texture, tab_rect, cas_speciaux, biomes, window);
        SDL_SetRenderTarget(renderer, NULL); // revient au rendu normal

        for(int i=0;i<8;i++){
            free(tab_rect[i]);
        }

        for(int i=0;i<8;i++){
            SDL_DestroyTexture(texture[i]);
        }

        for(int i=0;i<50;i++){
            SDL_DestroyTexture(cas_speciaux[i]);
        }

        m->map = map;
        m->dim_case = dim_case;
        m->longueur = taille_labyrinthe[1];
        m->hauteur = taille_labyrinthe[0];
        m->nb_noeud = nb_noeud_maze;
        m->construction = l->construction;
        m->poids = biomes;
        SDL_Rect r = {(w_x - dim_case*taille_labyrinthe[1]) / 2, (w_y - dim_case*taille_labyrinthe[0]) / 2, dim_case*taille_labyrinthe[1], dim_case*taille_labyrinthe[0]};
        m->dest = r;
    }else{
        SDL_Texture *map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);
        SDL_SetRenderTarget(renderer, map); // dessine dans la map
        SDL_RenderClear(renderer); // efface l’ancien contenu
        int dim_case = draw_maze(renderer, w_x, w_y, l->construction, nb_noeud_maze, taille_labyrinthe);
        SDL_SetRenderTarget(renderer, NULL); // revient au rendu normal
        m->map = map;
        m->dim_case = dim_case;
        m->longueur = taille_labyrinthe[1];
        m->hauteur = taille_labyrinthe[0];
        m->nb_noeud = nb_noeud_maze;
        m->construction = l->construction  ;
        SDL_Rect r = {(w_x - dim_case*taille_labyrinthe[1]) / 2, (w_y - dim_case*taille_labyrinthe[0]) / 2, dim_case*taille_labyrinthe[1], dim_case*taille_labyrinthe[0]};
        m->dest = r;
    }

    
    return m;
}

void draw_maze_BFS(SDL_Renderer *renderer, int window_size_x, int window_size_y, int * tab_coloration, maze * m, int * path, int depart, int arrivee, TTF_Font *font) {

    int i = 0;
    int j = -1;
    int taille_point = m->dim_case / 2;

    int coo_d[2]; coo_d[0] = depart % m->longueur; coo_d[1] = depart / m->longueur;
    int coo_a[2]; coo_a[0] = arrivee % m->longueur; coo_a[1] = arrivee / m->longueur;

    int max = 0;
    for (int p = 0; p < m->nb_noeud; p++) {
        if (tab_coloration[p] > max) {
            max = tab_coloration[p];
        }
    }

    for (int k = 0; k < m->nb_noeud; k++) {
        if (k % m->longueur == 0) {
            j++;
            i = 0;
        }

        int val = tab_coloration[k];
        float ratio = (float)val / max;

        int r = (int)(180 * (1 - ratio));
        int g = (int)(180 * (1 - ratio));
        int b = (int)(255 * (1 - ratio));

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_Rect dest = { i * m->dim_case , j * m->dim_case, m->dim_case , m->dim_case };
        SDL_RenderFillRect(renderer, &dest);

        i++;
    }

    i = 0;
    while (path[i] != -1) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        int x = path[i] % m->longueur;
        int y = path[i] / m->longueur;
        SDL_Rect dest = { x * m->dim_case + taille_point / 2, y * m->dim_case + taille_point / 2, taille_point, taille_point };
        SDL_RenderFillRect(renderer, &dest);
        i++;
    }

    SDL_Color colorD = {0, 0, 0, 255};
    SDL_Surface *text_surfaceD = TTF_RenderText_Blended(font, "D", colorD);
    SDL_Texture *text_textureD = SDL_CreateTextureFromSurface(renderer, text_surfaceD);
    SDL_Rect text_rectD = { coo_d[0] * m->dim_case + m->dim_case / 4, coo_d[1] * m->dim_case + m->dim_case / 4,
                            m->dim_case / 2, m->dim_case / 2 };
    SDL_RenderCopy(renderer, text_textureD, NULL, &text_rectD);
    SDL_FreeSurface(text_surfaceD);
    SDL_DestroyTexture(text_textureD);

    SDL_Color colorA = {255, 255, 255, 255}; 
    SDL_Surface *text_surfaceA = TTF_RenderText_Blended(font, "A", colorA);
    SDL_Texture *text_textureA = SDL_CreateTextureFromSurface(renderer, text_surfaceA);
    SDL_Rect text_rectA = { coo_a[0] * m->dim_case + m->dim_case / 4, coo_a[1] * m->dim_case + m->dim_case / 4,
                            m->dim_case / 2, m->dim_case / 2 };
    SDL_RenderCopy(renderer, text_textureA, NULL, &text_rectA);
    SDL_FreeSurface(text_surfaceA);
    SDL_DestroyTexture(text_textureA);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}



void draw_maze_Dijkstra(SDL_Renderer *renderer, int window_size_x, int window_size_y, int * tab_visite, maze * m, int * path, int depart, int arrivee, TTF_Font * font) {
    int i = 0;
    int j = -1;
    int taille_point = m->dim_case / 2; 

    int coo_d[2] = { depart % m->longueur, depart / m->longueur };
    int coo_a[2] = { arrivee % m->longueur, arrivee / m->longueur };

    for (int k = 0; k < m->nb_noeud; k++) {
        if (k % m->longueur == 0) {
            j++;
            i = 0;
        }

        if (tab_visite[k] == 1) {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  
            SDL_Rect dest = { i * m->dim_case, j * m->dim_case, m->dim_case, m->dim_case };
            SDL_RenderFillRect(renderer, &dest);
        }

        i++;
    }

    i = 0;
    while (path[i] != -1) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        int x = path[i] % m->longueur;
        int y = path[i] / m->longueur;
        SDL_Rect dest = { x * m->dim_case + taille_point / 2, y * m->dim_case + taille_point / 2, taille_point, taille_point };
        SDL_RenderFillRect(renderer, &dest);
        i++;
    }

    SDL_Color noir = {0, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    SDL_Surface *surface_d = TTF_RenderText_Blended(font, "D", noir);
    SDL_Texture *texture_d = SDL_CreateTextureFromSurface(renderer, surface_d);
    SDL_Rect dest_d = { coo_d[0] * m->dim_case + m->dim_case / 4, coo_d[1] * m->dim_case + m->dim_case / 4, m->dim_case / 2, m->dim_case / 2 };
    SDL_RenderCopy(renderer, texture_d, NULL, &dest_d);
    SDL_FreeSurface(surface_d);
    SDL_DestroyTexture(texture_d);

    SDL_Surface *surface_a = TTF_RenderText_Blended(font, "A", blanc);
    SDL_Texture *texture_a = SDL_CreateTextureFromSurface(renderer, surface_a);
    SDL_Rect dest_a = { coo_a[0] * m->dim_case + m->dim_case / 4, coo_a[1] * m->dim_case + m->dim_case / 4, m->dim_case / 2, m->dim_case / 2 };
    SDL_RenderCopy(renderer, texture_a, NULL, &dest_a);
    SDL_FreeSurface(surface_a);
    SDL_DestroyTexture(texture_a);

    TTF_CloseFont(font);
}


// affiche un changement de case dans le cadre de déplacements auto
void affiche_movement_auto(entity * player, int direction, maze * m, SDL_Renderer * renderer, int speed, SDL_Window * window, int coo_a[2], int coo_d[2]){
     
    int taille_point = m->dim_case; 
    int k = 0;

    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);
    SDL_Texture * tmp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);
    SDL_Rect tmp_r = {0, 0, m->dim_case*m->longueur, m->dim_case*m->hauteur};
    SDL_Texture * t = load_texture_from_image("textures/chest.png", window, renderer);
    SDL_Texture * t2 = load_texture_from_image("textures/spawn1.png", window, renderer);

    SDL_Rect rect_a = { coo_a[0] * m->dim_case + m->dim_case/4, coo_a[1] * m->dim_case + m->dim_case/4, m->dim_case - m->dim_case/2, m->dim_case - m->dim_case/2};
    SDL_Rect rect_d = { coo_d[0] * m->dim_case + m->dim_case/4, coo_d[1] * m->dim_case + m->dim_case/2 - 5, m->dim_case - m->dim_case/2, m->dim_case - m->dim_case/2};

    switch (direction){
    case 0: // gauche
        while(speed*k < m->dim_case){
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer, tmp);
            SDL_RenderCopy(renderer, m->map, NULL, NULL);
            SDL_RenderCopy(renderer, t, NULL, &rect_a);
            SDL_RenderCopy(renderer, t2, NULL, &rect_d);
            SDL_Rect dest = { (player->x+1) * m->dim_case - speed*k, player->y * m->dim_case, taille_point, taille_point};
            get_texture_entity(player->feuille_animation, 2, k%player->feuille_animation->duree[2], dest, renderer);
            render_focus_centered(renderer, tmp, tmp_r, w_x, w_y);
            SDL_RenderPresent(renderer);
            SDL_Delay(50);
            //printf("%d %d %d %d\n", (player->x+1) * m->dim_case - speed*k, player->y * m->dim_case, taille_point, taille_point);
            k++;
        }
        break;
    case 1: // droite
        while(speed*k < m->dim_case){
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer, tmp);
            SDL_RenderCopy(renderer, m->map, NULL, NULL);
            SDL_RenderCopy(renderer, t, NULL, &rect_a);
            SDL_RenderCopy(renderer, t2, NULL, &rect_d);
            SDL_Rect dest = { (player->x-1) * m->dim_case + speed*k, player->y * m->dim_case, taille_point, taille_point};
            get_texture_entity(player->feuille_animation, 3, k%player->feuille_animation->duree[2], dest, renderer);
            render_focus_centered(renderer, tmp, tmp_r, w_x, w_y);
            SDL_RenderPresent(renderer);
            SDL_Delay(50);
            k++;
        }
        break;
    case 2: // haut
        while(speed*k < m->dim_case){
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer, tmp);
            SDL_RenderCopy(renderer, m->map, NULL, NULL);
            SDL_RenderCopy(renderer, t, NULL, &rect_a);
            SDL_RenderCopy(renderer, t2, NULL, &rect_d);
            SDL_Rect dest = { player->x * m->dim_case, (player->y+1) * m->dim_case - speed*k, taille_point, taille_point};
            get_texture_entity(player->feuille_animation, 1, k%player->feuille_animation->duree[2], dest, renderer);
            render_focus_centered(renderer, tmp, tmp_r, w_x, w_y);
            SDL_RenderPresent(renderer);
            SDL_Delay(50);
            k++;
        }
        break;
    case 3: // bas
        while(speed*k < m->dim_case){
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer, tmp);
            SDL_RenderCopy(renderer, m->map, NULL, NULL);
            SDL_RenderCopy(renderer, t, NULL, &rect_a);
            SDL_RenderCopy(renderer, t2, NULL, &rect_d);
            SDL_Rect dest = { player->x * m->dim_case, (player->y-1) * m->dim_case + speed*k, taille_point, taille_point};
            get_texture_entity(player->feuille_animation, 0, k%player->feuille_animation->duree[2], dest, renderer);
            render_focus_centered(renderer, tmp, tmp_r, w_x, w_y);
            SDL_RenderPresent(renderer);
            SDL_Delay(50);
            k++;
        }
        break;
    default:
        break;
    }

    SDL_DestroyTexture(tmp);
    SDL_DestroyTexture(t);
    SDL_DestroyTexture(t2);
}

void reset_pos(int coo[2], entity * player, maze* m, SDL_Renderer * renderer, SDL_Window * window, int coo_a[2], int coo_d[2]){
    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);
    SDL_Texture * tmp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);
    SDL_Rect tmp_r = {0, 0, m->dim_case*m->longueur, m->dim_case*m->hauteur};
    SDL_Texture * t = load_texture_from_image("textures/chest.png", window, renderer);
    SDL_Texture * t2 = load_texture_from_image("textures/spawn1.png", window, renderer);
    SDL_Rect rect_a = { coo_a[0] * m->dim_case + m->dim_case/4, coo_a[1] * m->dim_case + m->dim_case/4, m->dim_case - m->dim_case/2, m->dim_case - m->dim_case/2};
    SDL_Rect rect_d = { coo_d[0] * m->dim_case + m->dim_case/4, coo_d[1] * m->dim_case + m->dim_case/2 - 5, m->dim_case - m->dim_case/2, m->dim_case - m->dim_case/2};
 
    player->x = coo[0];
    player->y = coo[1]; 
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, tmp);
    SDL_RenderCopy(renderer, m->map, NULL, NULL);
    SDL_RenderCopy(renderer, t, NULL, &rect_a);
    SDL_RenderCopy(renderer, t2, NULL, &rect_d);
    SDL_Rect dest = { player->x * m->dim_case, (player->y) * m->dim_case, m->dim_case, m->dim_case};
    get_texture_entity(player->feuille_animation, 0, 0, dest, renderer);
    render_focus_centered(renderer, tmp, tmp_r, w_x, w_y);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    SDL_DestroyTexture(t);
    SDL_DestroyTexture(t2);
}
 
void auto_movement_with_path(entity * player, int * path, maze * m, SDL_Renderer * renderer, int speed, SDL_Window * window, int arrivee, int depart){
    
    int direction;
    int i= 0;
    int coo_a[2]; coo_a[0] = arrivee % m->longueur; coo_a[1] = arrivee / m->longueur;
    int coo_d[2]; coo_d[0] = depart % m->longueur; coo_d[1] = depart / m->longueur;
    player->x = coo_d[0];
    player->y = coo_d[1];

    while(path[i] != -1){
        direction = calcul_direction(player->y*m->longueur + player->x, m->longueur, path[i]);
        player->direction = direction;
        movement(player, m);
        affiche_movement_auto(player, direction, m, renderer, speed, window, coo_a, coo_d);
        //printf("%d, coo : %d %d\n", path[i],player->x, player->y);
        i++;
    }
    reset_pos(coo_d, player, m, renderer, window, coo_a, coo_d); // si on veut revenir au point de depart
}

void init_button(SDL_Renderer * renderer, maze * m, SDL_Window * window, int maj, int w_x, int w_y){
    
    SDL_Texture * texture[5];
    texture[0] = load_texture_from_image("textures/button_base.png", window, renderer);
    texture[1] = load_texture_from_image("textures/button_ice.png", window, renderer);
    texture[2] = load_texture_from_image("textures/button_water.png", window, renderer);
    texture[3] = load_texture_from_image("textures/button_swamp.png", window, renderer);
    texture[4] = load_texture_from_image("textures/button_sand.png", window, renderer);

    int dim[2] = {2, 1};
    int corres[2] = {0, 1};
    SDL_Rect * tab_rect[5];
    tab_rect[0] = load_rectangle_from_sprite("textures/button_base.png", window, renderer, dim, corres, 0);
    tab_rect[1] = load_rectangle_from_sprite("textures/button_ice.png", window, renderer, dim, corres, 0);
    tab_rect[2] = load_rectangle_from_sprite("textures/button_water.png", window, renderer, dim, corres, 0);
    tab_rect[3] = load_rectangle_from_sprite("textures/button_swamp.png", window, renderer, dim, corres, 0);
    tab_rect[4] = load_rectangle_from_sprite("textures/button_sand.png", window, renderer, dim, corres, 0);
    SDL_Texture * button_texture;

    if(maj){
        button_texture = m->button_texture;
    }else{
        button_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);
        SDL_SetTextureBlendMode(button_texture, SDL_BLENDMODE_BLEND);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, button_texture); // dessine dans la map
    SDL_RenderClear(renderer); // efface l’ancien contenu

    int correspondance[9] = {0, 1, 2, 0, 0, 0, 3, 0, 4}; // corespondance poids/biome dans le tab pour cas classique
    
    for(int i=0;i<m->hauteur*m->longueur;i++){
        if(m->button[i] == 1){
            SDL_Rect dest = {((int) i % m->longueur)*m->dim_case +m->dim_case/4, (i / m->longueur)*m->dim_case + m->dim_case/3, m->dim_case/2, m->dim_case/2}; 
            SDL_RenderCopy(renderer, texture[correspondance[m->poids[i]]], &tab_rect[correspondance[m->poids[i]]][0], &dest);
        }else if(m->button[i] == 2){
            SDL_Rect dest = {((int) i % m->longueur)*m->dim_case +m->dim_case/4, (i / m->longueur)*m->dim_case +m->dim_case/3, m->dim_case/2, m->dim_case/2}; 
            SDL_RenderCopy(renderer, texture[correspondance[m->poids[i]]], &tab_rect[correspondance[m->poids[i]]][1], &dest);
        } 
    }

    if(!maj){
        m->button_texture = button_texture;
    }

    SDL_SetRenderTarget(renderer, NULL); // revient au rendu normal
}
 
void maj_button(maze * m, SDL_Renderer * renderer, SDL_Window * window, entity * player, int * button_pressed){
    if(m->button[player->x + player->y*m->longueur] == 1){
        m->button[player->x + player->y*m->longueur] ++;
        init_button(renderer, m, window, 1, 0, 0);
        (*button_pressed) ++;
        //SON button player
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
            return ;
        }
        Mix_Chunk * click = Mix_LoadWAV("./son/click.wav");
        if (!click) {
            printf("Erreur chargement click : %s\n", Mix_GetError());
        }
        else {
            Mix_VolumeChunk(click, 90);
            Mix_PlayChannel(0, click,0);
        }
    } 
}

void maj_button_vm(maze * m, SDL_Renderer * renderer, SDL_Window * window, entity * monstre, int * button_pressed){
    if(m->button[monstre->x + monstre->y*m->longueur] == 2){
        m->button[monstre->x + monstre->y*m->longueur] --;
        init_button(renderer, m, window, 1, 0, 0);
        (*button_pressed) --;
        //SON button monstre
        Mix_Chunk * click = Mix_LoadWAV("./son/click_vm.wav");
        if (!click) {
            printf("Erreur chargement click : %s\n", Mix_GetError());
        }
        else {
            Mix_VolumeChunk(click, 90);
            Mix_PlayChannel(0, click,0);
        }
    } 
}

// initialise les variables pour faire tourner un niveau
void init_level(SDL_Renderer * renderer, SDL_Window * window, maze ** m, labyrinthe * l, entity_name * tab_e, animation_page *** all_anim, entity ** player, int id_slime, int with_texture, int nb_anim, int * biomes, int * button, point_interet* spawns, entity ** monster){
         
    *m = get_labyrinthe_map(window, renderer, l, with_texture, biomes);
    
    int w_x; int w_y; 
    SDL_GetWindowSize(window,&w_x,&w_y);

    (*m)->button = button;
    init_button(renderer, *m, window, 0, w_x, w_y);
    
 
    *all_anim = load_entity_animation(tab_e, nb_anim, window, renderer);

    //afficher_animation_page(*all_anim, nb_anim);

    *player = malloc(sizeof(entity));
    (*player)->feuille_animation = (*all_anim)[id_slime];
    (*player)->feuille_animation2 = (*all_anim)[id_slime+3];
    (*player)->feuille_animation3 = (*all_anim)[id_slime+6];
    (*player)->feuille_animation4 = (*all_anim)[id_slime+9];
    (*player)->feuille_animation5 = (*all_anim)[id_slime+15];
    (*player)->feuille_animation6 = (*all_anim)[id_slime+18];
    (*player)->direction = 0; 
    (*player)->x = spawns->spawn_player%(*m)->longueur; 
    (*player)->y = spawns->spawn_player/(*m)->longueur; 
    (*player)->gliding = 0; 
    (*player)->x_draw = spawns->spawn_player%(*m)->longueur*(*m)->dim_case; 
    (*player)->y_draw = spawns->spawn_player/(*m)->longueur*(*m)->dim_case;
    (*player)->speed = 0;

    *monster = malloc(sizeof(entity));
    (*monster)->feuille_animation = (*all_anim)[12];
    (*monster)->feuille_animation2 = (*all_anim)[13];
    (*monster)->feuille_animation3 = (*all_anim)[14];
    (*monster)->feuille_animation4 = (*all_anim)[21];
    (*monster)->direction = 0; 
    (*monster)->x = spawns->spawn_monster%(*m)->longueur; 
    (*monster)->y = spawns->spawn_monster/(*m)->longueur; 
    (*monster)->gliding = 0; 
    (*monster)->x_draw = spawns->spawn_monster%(*m)->longueur*(*m)->dim_case; 
    (*monster)->y_draw = spawns->spawn_monster/(*m)->longueur*(*m)->dim_case;
    (*monster)->speed = 1;
}


SDL_Texture *create_halo_texture(SDL_Renderer *renderer, int radius) {
    int diameter = 2 * radius;

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, diameter, diameter, 32, SDL_PIXELFORMAT_RGBA8888);
    if (!surface) return NULL;

    SDL_LockSurface(surface);
    Uint32* pixels = (Uint32*)surface->pixels;
    int pitch = surface->pitch / 4;

    for (int y = 0; y < diameter; y++) {
        for (int x = 0; x < diameter; x++) {
            int dx = x - radius;
            int dy = y - radius;
            float dist = sqrtf(dx * dx + dy * dy);
            float t = dist / (float)radius;

            Uint8 alpha = (t >= 1.0f) ? 255 : (Uint8)(255 * t * t);  // dégradé vers l'extérieur
            pixels[y * pitch + x] = SDL_MapRGBA(surface->format, 0, 0, 0, alpha);
        }
    }

    SDL_UnlockSurface(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_FreeSurface(surface);
    return texture;
}

void render_halo(SDL_Renderer *renderer, SDL_Texture *halo_texture, int player_x, int player_y, int radius) {
    SDL_Rect dst = {
        .x = player_x - radius,
        .y = player_y - radius,
        .w = 2 * radius,
        .h = 2 * radius
    };
    SDL_RenderCopy(renderer, halo_texture, NULL, &dst);
}

void black_fog(SDL_Renderer *renderer, int player_x, int player_y, int radius, int screen_width, int screen_height) {
    // Rectangle central (zone de lumière) — on ne dessine rien ici
    SDL_Rect light_rect = {
        .x = player_x - radius,
        .y = player_y - radius,
        .w = 2 * radius,
        .h = 2 * radius
    };

    // Couleur noire opaque
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // 1. Haut
    SDL_Rect top = {0, 0, screen_width, light_rect.y};
    SDL_RenderFillRect(renderer, &top);

    // 2. Bas
    SDL_Rect bottom = {0, light_rect.y + light_rect.h, screen_width, screen_height - (light_rect.y + light_rect.h)};
    SDL_RenderFillRect(renderer, &bottom);

    // 3. Gauche
    SDL_Rect left = {0, light_rect.y, light_rect.x, light_rect.h};
    SDL_RenderFillRect(renderer, &left);

    // 4. Droite
    SDL_Rect right = {light_rect.x + light_rect.w, light_rect.y, screen_width - (light_rect.x + light_rect.w), light_rect.h};
    SDL_RenderFillRect(renderer, &right);
}

  
void labyrinthe_ui(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *icon_texture, int nb_switch, int w_x, int nb_button, SDL_Texture * icon_texture2, int nb_button_tot) {
    int icon_size = w_x / 20;
    int margin = 10;

    // === Formatage du texte (ex : "05") ===
    char text[3];
    snprintf(text, sizeof(text), "%02d", nb_switch);

    char text2[7];
    snprintf(text2, sizeof(text2), "%02d/%02d", nb_button, nb_button_tot);

    SDL_Color text_color = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, text, text_color);
    SDL_Surface *text_surface2 = TTF_RenderText_Blended(font, text2, text_color);
    if (!text_surface) {
        SDL_Log("Erreur TTF_RenderText_Blended : %s", TTF_GetError());
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Texture *text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);
    if (!text_texture) {
        SDL_Log("Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_FreeSurface(text_surface);
        return;
    }

    int text_w, text_h;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_w, &text_h);
    int text_w2, text_h2;
    SDL_QueryTexture(text_texture2, NULL, NULL, &text_w2, &text_h2);

    // === Icône à gauche ===
    SDL_Rect icon_left_rect = {margin, margin, icon_size, icon_size};
    SDL_Rect text_left_rect = {
        icon_left_rect.x + icon_left_rect.w + 10,
        icon_left_rect.y + (icon_left_rect.h - text_h) / 2,
        text_w,
        text_h
    };

    SDL_RenderCopy(renderer, icon_texture, NULL, &icon_left_rect);
    SDL_RenderCopy(renderer, text_texture, NULL, &text_left_rect);

    // === Icône à droite ===
    int total_width = icon_size + 10 + text_w2;
    SDL_Rect icon_right_rect = {
        w_x - total_width - margin,
        margin,
        icon_size,
        icon_size
    };
    SDL_Rect text_right_rect = {
        icon_right_rect.x + icon_size + 10,
        icon_right_rect.y + (icon_right_rect.h - text_h2) / 2,
        text_w2,
        text_h2
    };

    SDL_RenderCopy(renderer, icon_texture2, NULL, &icon_right_rect);
    SDL_RenderCopy(renderer, text_texture2, NULL, &text_right_rect);

    // Nettoyage
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void exit_management(SDL_Renderer * renderer){

}

void init_anim_tab(char * image, SDL_Renderer * renderer, SDL_Texture ** tab_texture_anim){
    SDL_Surface * s = IMG_Load(image);
    SDL_Surface * s2 = IMG_Load(image);
    SDL_Surface * s3 = IMG_Load(image);
    SDL_Surface * s4 = IMG_Load(image);
    SDL_Surface * s5 = IMG_Load(image);

    transformation * t = init_t();
    t->theta_max = M_PI/3;
    t->z_0.re = s->w/2;
    t->z_0.im = s->h/2;
    t->d0 = 0;
    t->dmax = s->h/4;
    t->d1 = s->h/2;
    /*
    for(int i=0;i<20;i++){
        printf("it %d\n", i);
        t->theta_max = i*M_PI/10;
        printf("modif t %f\n", t->theta_max);
        SDL_Surface *s_transformed = surface_to_surface(s, t, &rotation_transformation_inverse_rond);
        printf("it %d\n", i);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, s_transformed);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, 50); 
        printf("it %d\n", i);
        tab_texture_anim[i] = texture;
        //SDL_FreeSurface(s_transformed);
        printf("it %d\n", i);
    }*/
    //SDL_FreeSurface(s);
    SDL_Surface *s_transformed = surface_to_surface(s, t, &rotation_transformation_inverse_rond);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, s_transformed);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, 50); 
    tab_texture_anim[0] = texture;

    t->theta_max = 2*M_PI/3;
    SDL_Surface *s_transformed2 = surface_to_surface(s2, t, &rotation_transformation_inverse_rond);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, s_transformed2);
    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture2, 50); 
    tab_texture_anim[1] = texture2;

    t->theta_max = M_PI;
    SDL_Surface *s_transformed3 = surface_to_surface(s3, t, &rotation_transformation_inverse_rond);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, s_transformed3);
    SDL_SetTextureBlendMode(texture3, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture3, 50); 
    tab_texture_anim[2] = texture3;

    t->theta_max = 4*M_PI/3;
    SDL_Surface *s_transformed4 = surface_to_surface(s4, t, &rotation_transformation_inverse_rond);
    SDL_Texture *texture4 = SDL_CreateTextureFromSurface(renderer, s_transformed4);
    SDL_SetTextureBlendMode(texture4, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture4, 50); 
    tab_texture_anim[3] = texture4;

    t->theta_max = 5*M_PI/3;
    SDL_Surface *s_transformed5 = surface_to_surface(s5, t, &rotation_transformation_inverse_rond);
    SDL_Texture *texture5 = SDL_CreateTextureFromSurface(renderer, s_transformed5);
    SDL_SetTextureBlendMode(texture5, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture5, 50); 
    tab_texture_anim[4] = texture5;
} 

void draw_spawns(SDL_Renderer * renderer, point_interet * spawns, SDL_Texture ** spawn_tab_texture, SDL_Rect ** spawn_tab_rect, maze * m, int exit_open, int it_spawns){
    
    SDL_Rect dest = {(spawns->spawn_player%m->longueur)*m->dim_case, (spawns->spawn_player/m->longueur)*m->dim_case, m->dim_case, m->dim_case};
    SDL_RenderCopy(renderer, spawn_tab_texture[0], &spawn_tab_rect[0][it_spawns%8], &dest);

    SDL_Rect dest2 = {(spawns->spawn_monster%m->longueur)*m->dim_case, (spawns->spawn_monster/m->longueur)*m->dim_case, m->dim_case, m->dim_case};
    SDL_RenderCopy(renderer, spawn_tab_texture[1], &spawn_tab_rect[1][it_spawns%8], &dest2);

    if(exit_open){
        SDL_Rect dest3 = {(spawns->exit%m->longueur)*m->dim_case + m->dim_case/8, (spawns->exit/m->longueur)*m->dim_case + m->dim_case/8, m->dim_case - m->dim_case/4, m->dim_case - m->dim_case/4};
        SDL_RenderCopy(renderer, spawn_tab_texture[2], &spawn_tab_rect[2][it_spawns%5], &dest3);
    }else{
        SDL_Rect dest3 = {(spawns->exit%m->longueur)*m->dim_case + m->dim_case/8, (spawns->exit/m->longueur)*m->dim_case + m->dim_case/8, m->dim_case - m->dim_case/4, m->dim_case - m->dim_case/4};
        SDL_RenderCopy(renderer, spawn_tab_texture[3], &spawn_tab_rect[3][it_spawns%5], &dest3);
    }
}

void init_spawns_tab(SDL_Renderer * renderer, SDL_Window * window,SDL_Rect ** tab_rect, SDL_Texture ** texture_tab){
    
    texture_tab[0] = load_texture_from_image("textures/player_portal.png", window, renderer);
    texture_tab[1] = load_texture_from_image("textures/monster_portal.png", window, renderer);
    texture_tab[2] = load_texture_from_image("textures/exit_portal.png", window, renderer);
    texture_tab[3] = load_texture_from_image("textures/exit_portal_close.png", window, renderer);

    int correspondance[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int correspondance2[6] = {0, 1, 2, 3, 4, 5};
    int dim[2] = {8, 1};
    tab_rect[0] = load_rectangle_from_sprite("textures/player_portal.png", window, renderer, dim, correspondance, 10);
    tab_rect[1] = load_rectangle_from_sprite("textures/monster_portal.png", window, renderer, dim, correspondance, 10);
    dim[0] = 3; dim[1] = 2;
    tab_rect[2] = load_rectangle_from_sprite("textures/exit_portal.png", window, renderer, dim, correspondance2, 0);
    tab_rect[3] = load_rectangle_from_sprite("textures/exit_portal_close.png", window, renderer, dim, correspondance2, 0);
}

void manage_player_path(SDL_Renderer * renderer, entity * player, int tab_path[][2], int * curseur_tab_path, int taille_tab, maze * m, int light, int light_radius, SDL_Texture * slime_trace[4]){

    //printf("passe 1 %d %d %d\n", *curseur_tab_path, player->x, player->y);
    int calc = 0;
    if(*curseur_tab_path != 0){ 
        if((tab_path[*curseur_tab_path-1][0] != player->x)||(tab_path[*curseur_tab_path-1][1] != player->y)){
            calc = 1;
        }
    }else if((tab_path[taille_tab-1][0] != player->x)||(tab_path[taille_tab-1][1] != player->y)){
        calc = 1;
    }

    if(calc){ // si on s'est deplacé on maj le tableau
        tab_path[*curseur_tab_path][0] = player->x;
        tab_path[*curseur_tab_path][1] = player->y; 
        (*curseur_tab_path)++; 
        if(*curseur_tab_path%taille_tab == 0){
            *curseur_tab_path = 0;
        }
    }
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    //SDL_SetRenderDrawColor(renderer, 0, 200, 175, 200);

    for(int i=0;i<taille_tab;i++){
        if(tab_path[i][0] != -1){
            SDL_Rect r = {tab_path[i][0]*m->dim_case + m->dim_case/4, tab_path[i][1]*m->dim_case+ m->dim_case/4, m->dim_case/2, m->dim_case/2};
            SDL_RenderCopy(renderer, slime_trace[i%4], NULL, &r);
        }
    }
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void manage_monster_path(SDL_Renderer * renderer, entity * monster, int tab_path[][2], int * curseur_tab_path, int taille_tab, maze * m, SDL_Texture * slime_trace[4]){

    //printf("passe 1 %d %d %d\n", *curseur_tab_path, monster->x, monster->y);
    int calc = 0;
    if(*curseur_tab_path != 0){ 
        if((tab_path[*curseur_tab_path-1][0] != monster->x)||(tab_path[*curseur_tab_path-1][1] != monster->y)){
            calc = 1;
        }
    }else if((tab_path[taille_tab-1][0] != monster->x)||(tab_path[taille_tab-1][1] != monster->y)){
        calc = 1;
    }

    if(calc){ // si on s'est deplacé on maj le tableau
        tab_path[*curseur_tab_path][0] = monster->x;
        tab_path[*curseur_tab_path][1] = monster->y; 
        (*curseur_tab_path)++; 
        if(*curseur_tab_path%taille_tab == 0){
            *curseur_tab_path = 0;
        }
    }
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    //SDL_SetRenderDrawColor(renderer, 0, 200, 175, 200);

    for(int i=0;i<taille_tab;i++){
        if(tab_path[i][0] != monster->x + monster->y*m->longueur){
            SDL_Rect r = {tab_path[i][0]*m->dim_case + m->dim_case/4, tab_path[i][1]*m->dim_case+ m->dim_case/4, m->dim_case/2, m->dim_case/2};
            SDL_RenderCopy(renderer, slime_trace[i%4], NULL, &r);
        }
        
    }
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void drawGauge(SDL_Renderer* renderer, int compteur, int val_max) {

    int screen_width, screen_height;
    SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

    int gauge_width = screen_width / 4;
    int gauge_height = screen_width / 30;

    int x = (screen_width - gauge_width) / 2;
    int y = 10;

    float ratio = (float)compteur / (float)val_max;
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    int filled_width = (int)(gauge_width * ratio);

    SDL_Rect filled = { x, y, filled_width, gauge_height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &filled);

    SDL_Rect border = { x, y, gauge_width, gauge_height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &border);
}

void afficher_grille(SDL_Renderer *renderer, TTF_Font *font, int *tab, int nb_lignes, int nb_colonnes,
                     int taille_case, int start_index, int end_index) {
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color bleu = {0, 0, 255, 255};
    SDL_Color rouge = {255, 0, 0, 255};

    int screen_width, screen_height;
    SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

   
    int total_height = nb_lignes * taille_case;

    int offset_x = 0; // marge à gauche, modifiable
    int offset_y = (screen_height - total_height) / 2;


    for (int i = 0; i < nb_lignes; i++) {
        for (int j = 0; j < nb_colonnes; j++) {
            int index = i * nb_colonnes + j;
            SDL_Rect cell = {
                offset_x + j * taille_case,
                offset_y + i * taille_case,
                taille_case,
                taille_case
            };

            // Couleur de fond spéciale pour départ et arrivée
            if (index == start_index) {
                SDL_SetRenderDrawColor(renderer, bleu.r, bleu.g, bleu.b, bleu.a);
                SDL_RenderFillRect(renderer, &cell);
            } else if (index == end_index) {
                SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);
                SDL_RenderFillRect(renderer, &cell);
            }

            // Bordure noire
            //SDL_SetRenderDrawColor(renderer, noir.r, noir.g, noir.b, noir.a);
            //SDL_RenderDrawRect(renderer, &cell);

            // Préparation du texte à afficher
            char buf[16];
            snprintf(buf, sizeof(buf), "%d", tab[index]);

            SDL_Surface *text_surface = TTF_RenderText_Blended(font, buf, blanc);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            int text_w = text_surface->w;
            int text_h = text_surface->h;
            SDL_FreeSurface(text_surface);

            SDL_Rect dst = {
                cell.x + (taille_case - text_w) / 2,
                cell.y + (taille_case - text_h) / 2,
                text_w,
                text_h
            };

            SDL_RenderCopy(renderer, text_texture, NULL, &dst);
            SDL_DestroyTexture(text_texture);
        }
    }
}