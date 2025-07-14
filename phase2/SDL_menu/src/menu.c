#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>
#include "menu.h"

// Fonctions de base pour la destion de sdl2 ----------------------------------------------------

void end_sdl2(char ok, char const* msg, SDL_Window* window,SDL_Renderer* renderer) {
        char msg_formated[255];
        int l;

        if (!ok) {                                                        // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
        }

        if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
        }
        if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
        window= NULL;
        }

        SDL_Quit();

        if (!ok) {                                       // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

SDL_Texture* load_texture_from_image2(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
    if (my_image == NULL) end_sdl2(0, "Chargement de l'image impossible", window, renderer);
    
    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl2(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}





// Fonctions d'affichages ----------------------------------------------------------------------

void fond_fixe_fenetre(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    SDL_RenderCopy(renderer, my_texture, &source, &destination);                 // Création de l'élément à afficher
}

void fond_fixe_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, coord coord) {
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                &source.w, &source.h);       // Récupération des dimensions de l'image

    destination.w = coord.w;              // On fixe les dimensions de l'affichage à  celles de la fenêtre
    destination.h = coord.h;
    destination.x= coord.x;
    destination.y= coord.y;   

    SDL_RenderCopy(renderer, my_texture, &source, &destination);                 // Création de l'élément à afficher
}

void scroll3_background(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer, int scroll_x, float zoom) {
    SDL_Rect window_dimensions = {0};
    SDL_Rect source = {0};
    SDL_Rect rect1 = {0}, rect2 = {0}, rect3 ={0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    int bg_width = source.w * zoom;
    int bg_height = source.h * zoom;

    rect1.w = rect2.w = rect3.w= bg_width;
    rect1.h = rect2.h = rect3.h= bg_height;
    rect1.y = rect2.y = rect3.y=window_dimensions.h - bg_height;

    scroll_x %= bg_width; // remet à 0 quand on dépasse une largeur
    rect1.x = -scroll_x;
    rect2.x = rect1.x + bg_width;
    rect3.x = rect2.x +bg_width;

    SDL_RenderCopy(renderer, texture, NULL, &rect1);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
    SDL_RenderCopy(renderer, texture, NULL, &rect3);
}

void parallax(SDL_Texture ** text, SDL_Window * window, SDL_Renderer * renderer, 
    int scroll1, int scroll2, int scroll3, int scroll4, int scroll_sol, coord coord_sol){
    fond_fixe_fenetre(text[0], window, renderer);
    scroll3_background(text[5], window, renderer, scroll1, 3);
    scroll3_background(text[4], window, renderer, scroll2, 2);
    scroll3_background(text[3], window, renderer, scroll3, 2.5);
    scroll3_background(text[2], window, renderer, scroll4, 3);
    fond_fixe_xy(text[1], window, renderer, coord_sol);
    scroll3_background(text[6], window, renderer, scroll_sol, 2);
}

void frame (SDL_Texture *my_texture, SDL_Window *window, int nb_images, int nb_ligne,SDL_Rect * state) {
    SDL_Rect source = {0}, window_dimensions = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,  &source.w, &source.h); 

    //float zoom = 4;                             // zoom, car ces images sont un peu petites
    int offset_x = source.w /nb_images,                // La largeur d'une vignette de l'image
    offset_y = source.h/nb_ligne;                // La hauteur d'une vignette de l'image

    int i=0;
    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    for (int y = 0; y < source.h/nb_ligne ; y += offset_y) {
        for (int x = 0; x < source.w; x += offset_x) {
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            ++i;
        }
    }                                   
}

void afficher (SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int num_frame, coord perso, SDL_Rect * state){
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,  &source.w, &source.h); 

    //float zoom = 4;                             // zoom, car ces images sont un peu petites

    destination.w = perso.w;            // Largeur du sprite à l'écran
    destination.h = perso.h ;            // Hauteur du sprite à l'écran
    destination.x = perso.x; // Position en x pour l'affichage du sprite
    destination.y = perso.y;  // Position en y pour l'affichage du sprite
    //SDL_Delay(20);
    SDL_RenderCopy(renderer, my_texture, &state[num_frame], &destination);
}





// Gestion des Textures  -----------------------------------------------------------------------------

SDL_Texture ** charge_texture (SDL_Texture ** text, SDL_Window * window, SDL_Renderer * renderer){
    text[0] = load_texture_from_image2("textures/foret/extra/color_bg.png", window, renderer); //couleur de fond
    text[1] = load_texture_from_image2("textures/foret/extra/floor_bg.png", window, renderer); //sol fond
    text[2] = load_texture_from_image2("textures/foret/parallax/trees4.png", window, renderer); //arbre 4
    text[3] = load_texture_from_image2("textures/foret/parallax/trees3.png", window, renderer); //arbre 3
    text[4] = load_texture_from_image2("textures/foret/parallax/trees2.png", window, renderer); //arbre 2
    text[5] = load_texture_from_image2("textures/foret/parallax/trees1.png", window, renderer); //arbre 1
    text[6] = load_texture_from_image2("textures/foret/parallax/sol_plateforme.png", window, renderer); //sol noir
    text[7] = load_texture_from_image2("textures/logo.png", window, renderer); //logo
    text[8] = load_texture_from_image2("textures/bouton/bouton_play.png", window, renderer); //bouton play
    text[9] = load_texture_from_image2("textures/bouton/bouton_play_hover.png", window, renderer); //bouton play hover
    text[10] = load_texture_from_image2("textures/bouton/param.png", window, renderer); //bouton ?
    text[11] = load_texture_from_image2("textures/bouton/param2.png", window, renderer); //bouton ? hover
    text[12] = load_texture_from_image2("textures/bouton/bouton_perso.png", window, renderer); //bouton menu perso
    text[13] = load_texture_from_image2("textures/bouton/bouton_perso_hover.png", window, renderer); //bouton menu perso hover
    text[14] = load_texture_from_image2("textures/bouton/next.png", window, renderer); //bouton next
    text[15] = load_texture_from_image2("textures/bouton/bouton_jaune.png", window, renderer); //bouton jaune
    text[16] = load_texture_from_image2("textures/bouton/bouton_jaune_hover.png", window, renderer); //bouton jaune hover
    text[17] = load_texture_from_image2("textures/bouton/cadre.png", window, renderer); //cadre
    text[18] = load_texture_from_image2("textures/bouton/next_hover.png", window, renderer); //bouton next hover
    text[19] = load_texture_from_image2("textures/bouton/cadre_fin.png", window, renderer); //cadre
    return text;
}

void Destroy_Texture(SDL_Texture ** text, int n) {
    for (int i=0; i<n; i++) {
        SDL_DestroyTexture(text[0]);
    }
    //détruire les n textures en 1 fonction
}

SDL_Texture ** charge_slime (SDL_Texture ** slime, SDL_Window * window, SDL_Renderer * renderer){
    slime[0] = load_texture_from_image2("textures/Slime1_Walk_full.png", window, renderer); //slime 1: bobby
    slime[1] = load_texture_from_image2("textures/Slime2_Walk_full.png", window, renderer); //slime 2: ricky
    slime[2] = load_texture_from_image2("textures/Slime3_Walk_full.png", window, renderer); //slime 3: johnny
    return slime;
}

SDL_Texture ** charger_map (SDL_Texture ** map, SDL_Window * window, SDL_Renderer * renderer) {
    map[0] = load_texture_from_image2("textures/laby/labyrinthe1.png", window, renderer); //laby neutre
    map[1] = load_texture_from_image2("textures/laby/labyrinthe2.png", window, renderer); //laby bleu
    return map;
}

SDL_Texture ** charger_flèches (SDL_Texture ** fleches, SDL_Window *window, SDL_Renderer * renderer) {
    fleches[0]=load_texture_from_image2("textures/bouton/fleche_droite.png", window, renderer);
    fleches[1]=load_texture_from_image2("textures/bouton/fleche_droite_hover.png", window, renderer);
    fleches[2]=load_texture_from_image2("textures/bouton/fleche_gauche.png", window, renderer);
    fleches[3]=load_texture_from_image2("textures/bouton/fleche_gauche_hover.png", window, renderer);
    return fleches;
}





// Gestion des boutons ---------------------------------------------------------------------------------

int pos_cursor(coord coord) {
    int dessus;
    int x, y;
    SDL_GetMouseState(&x,&y);
    if ( (x>coord.x) && (x<coord.x+coord.w) && (y>coord.y) && (y<coord.y+coord.h)) {
        dessus=1; //la souris est sur la zone
    }
    else {
        dessus=0; //la souris n'est pas sur la zone
    }
    return dessus;
}

int * bouleen_bouton(int * int_boutons, coord coord_play, coord coord_play2, coord coord_param, coord coord_perso, 
    coord slime1, coord slime2, coord slime3, coord f_droit, coord f_gauche, coord next, coord suiv) {
    int_boutons[0]= pos_cursor(coord_play); //play
    int_boutons[1]= pos_cursor(coord_play2); //play2
    int_boutons[2] =pos_cursor(coord_param); //param ?
    int_boutons[3] =pos_cursor(coord_perso); //perso
    int_boutons[4] =pos_cursor(slime1); //slime 1
    int_boutons[5] =pos_cursor(slime2); //slime 2
    int_boutons[6] =pos_cursor(slime3); //slime 3
    int_boutons[7] =pos_cursor(f_droit); //fleche droite
    int_boutons[8] =pos_cursor(f_gauche); //fleche gauche
    int_boutons[9] =pos_cursor(next); // next
    int_boutons[10] = pos_cursor(suiv); //back
    return int_boutons;
}

void hover_bouton (SDL_Window * window, SDL_Renderer * renderer, SDL_Texture *text1, SDL_Texture *text2 , int boul_bouton, coord coord_bouton){
    if (boul_bouton==1) {
        fond_fixe_xy(text2, window, renderer, coord_bouton);
    }
    else {
        fond_fixe_xy(text1, window, renderer, coord_bouton);
    }
}

void hover_menu_principal(int * int_bouton, SDL_Texture ** text, SDL_Window * window, SDL_Renderer * renderer, 
    coord coord_play, coord coord_play2, coord coord_param){
    hover_bouton(window, renderer, text[8], text[9], int_bouton[0], coord_play);
    hover_bouton(window, renderer, text[8], text[9], int_bouton[1], coord_play2);
    hover_bouton(window, renderer, text[10], text[11], int_bouton[2], coord_param);
}

void maj_coord(coord * play, coord * play2, coord * param, coord * perso, coord * coord_sol, coord * logo, 
     coord * slime1, coord * slime2, coord * slime3,coord * perso_b, coord * f_droit, coord * f_gauche, coord * police_play, 
     coord * police_play2, coord * police_slime, coord * p_nom_slime1,coord * p_nom_slime2,coord * p_nom_slime3, coord * coord_next, 
     coord* coord_suiv, coord * p_next, coord * p_suiv, SDL_Rect window_dimensions) {
    play->x=(window_dimensions.w-play->w)/2;
    play->y=window_dimensions.h/2;
    play->w= window_dimensions.w/3;
    play->h=150;

    play2->x=(window_dimensions.w-play2->w)/2;
    play2->y=window_dimensions.h/2+200;
    play2->w= window_dimensions.w/3;
    play2->h=150;

    param->x=window_dimensions.w/16*14;
    param->y=50;
    param->w=window_dimensions.w/16;
    param->h=window_dimensions.h/12;

    perso->x=window_dimensions.w/16;
    perso->y=50;
    perso->w=window_dimensions.w/16;
    perso->h=window_dimensions.h/12;

    coord_sol->x=0;
    coord_sol->y=window_dimensions.h-50;
    coord_sol->w=window_dimensions.w;
    coord_sol->h=50;

    slime2->w=150;
    slime2->h=150;
    slime2->x=(window_dimensions.w-slime2->w)/2;
    slime2->y=(window_dimensions.h-slime2->h)/2;

    slime1->w=150;
    slime1->h=150;
    slime1->x=slime2->x-slime2->x*0.33;
    slime1->y=(window_dimensions.h-slime2->h)/2;

    slime3->w=150;
    slime3->h=150;
    slime3->x=slime2->x+slime2->x*0.33;
    slime3->y=(window_dimensions.h-slime2->h)/2;

    logo->x=window_dimensions.w/4;
    logo->y=75;
    logo->w=window_dimensions.w/2;
    logo->h=350;

    perso_b->x=window_dimensions.w*0.5;
    perso_b->y=window_dimensions.h*0.7;
    perso_b->w=(-window_dimensions.x+perso_b->w)/2;
    perso_b->h=(perso_b->h-window_dimensions.y)/4;

    f_droit->w =window_dimensions.w/12*0.8;
    f_droit->h =f_droit->w;
    f_droit->x =(window_dimensions.w-f_droit->w)/3*2;
    f_droit->y =(window_dimensions.h-f_droit->w)/3;

    f_gauche->w =window_dimensions.w/12*0.8;
    f_gauche->h =f_gauche->w;
    f_gauche->x =(window_dimensions.w-f_gauche->w)/3;
    f_gauche->y =(window_dimensions.h-f_gauche->w)/3;

    police_play->w=150;
    police_play->h=75;
    police_play->x=(window_dimensions.w- police_play->w)/2;
    police_play->y=play->y+75/1.75;

    police_play2->w=150;
    police_play2->h=75;
    police_play2->x=(window_dimensions.w- police_play2->w)/2;
    police_play2->y=play2->y+75/1.75;

    police_slime->w=window_dimensions.w/2.5;
    police_slime->h=85;
    police_slime->x=perso_b->x/2+police_slime->w/8;
    police_slime->y=perso_b->y/2-police_slime->h/2;

    p_nom_slime1->w= slime1->w;
    p_nom_slime1->h=window_dimensions.h/20;
    p_nom_slime1->x=slime1->x;
    p_nom_slime1->y=slime1->y+ window_dimensions.h/5;

    p_nom_slime2->w= slime1->w;
    p_nom_slime2->h=window_dimensions.h/20;
    p_nom_slime2->x=slime2->x;
    p_nom_slime2->y=slime1->y+ window_dimensions.h/5;

    p_nom_slime3->w= slime1->w+ slime1->w/5;
    p_nom_slime3->h=window_dimensions.h/20;
    p_nom_slime3->x=slime3->x-slime1->w/10;
    p_nom_slime3->y=slime1->y+ window_dimensions.h/5;

    coord_next->w=window_dimensions.w/8;
    coord_next->h=window_dimensions.h/12;
    coord_next->x= window_dimensions.w/7*4;
    coord_next->y= window_dimensions.h/7*4;

    coord_suiv->w=window_dimensions.w/8;
    coord_suiv->h=window_dimensions.h/12;
    coord_suiv->x= window_dimensions.w/7*2+25;
    coord_suiv->y= window_dimensions.h/7*4;

    p_next->w= window_dimensions.w/14;
    p_next->h= window_dimensions.h/25;
    p_next->x= coord_next->x+p_next->w/4*1.7;
    p_next->y= coord_next->y+p_next->h/2;

    p_suiv->w= window_dimensions.w/14;
    p_suiv->h=window_dimensions.h/25;
    p_suiv->x=coord_suiv->x+p_suiv->w/4*1.7;
    p_suiv->y=coord_suiv->y+p_suiv->h/2;
}


int activer_int(int bouléen) {
    if (bouléen==0) {
        bouléen=1;
    }
    else {
        bouléen=0;
    }
    return bouléen;
}




// Gestion des fenêtres -------------------------------------------------------------------------------------


/* Choix des personnages */
void menu_perso(int slime_clic, SDL_Rect window_dimensions, SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * text){
    //afficher un rectangle (une fenetre) à partir d'une fenêtre
    SDL_Rect rect2;
    coord page_perso;
    page_perso.w=window_dimensions.w*0.5;
    page_perso.h=window_dimensions.h*0.7;
    page_perso.x=(-window_dimensions.x+page_perso.w)/2;
    page_perso.y=(page_perso.h-window_dimensions.y)/4;

    SDL_SetRenderDrawColor(renderer, 0,0,0,120);

    if (slime_clic==1){  
        rect2.x=0;
        rect2.y=0;
        rect2.w=window_dimensions.w;
        rect2.h=window_dimensions.h; 
        SDL_RenderFillRect(renderer, &rect2); 

        fond_fixe_xy(text,window, renderer, page_perso);
    }
    else {
        rect2.x=0;
        rect2.y=0;
        rect2.w=0;
        rect2.h=0; 
        SDL_RenderFillRect(renderer, &rect2);                                                        
    }
}

void bouton_choix_perso(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * button, SDL_Texture * button_hover,
    int bouton, coord slime1, coord slime2, coord slime3) {
    int b_slime1 = pos_cursor(slime1);
    int b_slime2 = pos_cursor(slime2);
    int b_slime3 = pos_cursor(slime3);
    if (bouton == 1){
        hover_bouton(window, renderer, button, button_hover, b_slime1, slime1);
        hover_bouton(window, renderer, button, button_hover, b_slime2, slime2);
        hover_bouton(window, renderer, button, button_hover, b_slime3, slime3);
    }
}


/* Règles et lore du jeu */
void bouton_règles(int param, SDL_Rect window_dimensions, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *text) {
    SDL_Rect rect2;

    coord page_perso;
    page_perso.w = window_dimensions.w * 0.5;
    page_perso.h = window_dimensions.h * 0.7;
    page_perso.x = (window_dimensions.w - page_perso.w) / 2;
    page_perso.y = (window_dimensions.h - page_perso.h) / 4;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120);

    if (param == 1) {
        rect2.x = 0;
        rect2.y = 0;
        rect2.w = window_dimensions.w;
        rect2.h = window_dimensions.h;
        SDL_RenderFillRect(renderer, &rect2);

        fond_fixe_xy(text, window, renderer, page_perso);

        // Texte des règles/lore
        const char *lore =
            "You awaken... soft, squishy, and utterly alone.\n"
            "\n"
            "You are a slime, lost deep within the twisting corridors of an ancient dungeon. The air is thick. The stone walls whisper secrets. But you have only one mission: find and activate all the forgotten buttons hidden in the shadows.\n"
            "\n"
            "High above your head, a faint counter glows the number of buttons left. Only when every button is lit will the dungeon grant you freedom.\n"
            "\n"
            "But something lurks.\n"
            "\n"
            "A mantis not just any beast, but a tall, silent, merciless hunter. It stalks the maze, searching for the glowing buttons you've lit... and turning them off, one by one. It doesn't know where they are. It doesn't need to. It will find them.\n"
            "\n"
            "Yet you have a weapon: your lamp. When lit, it pushes back the darkness. A warm circle of light surrounds you, revealing the path ahead  but light is dangerous. Light attracts.\n"
            "\n"
            "The moment your lamp flickers to life, the mantis senses your presence. It turns. It hunts. It will not stop until you extinguish the light or until it catches you.\n"
            "\n"
            "There is a delay when you turn the light on or off. And your lamp ... has limited charges. Every use must be earned. Every glow must count.\n"
            "\n"
            "And when (if you) manage to activate every last button ... the exit will creak open. That's when the mantis will lock onto you, with absolute precision. No more hiding. No more searching. Only the chase.\n"
            "\n"
            "Run, little slime.\n"
            "Outsmart the mantis.\n"
            "Light the way.\n"
            "Escape the labyrinth.";

        TTF_Font *font = TTF_OpenFont("./textures/police/pixel-ultima-bold.ttf", 18);
        if (!font) return;

        SDL_Color color = {255, 255, 255, 255};
        int line_spacing = 6;
        int margin = 40; // marge à gauche et à droite
        int max_width = page_perso.w - 2 * margin;
        int x = page_perso.x + margin;
        int y = page_perso.y + 20;
        int bottom = page_perso.y + page_perso.h - 20;

        char buffer[1024];
        const char *ptr = lore;
        int total_text_height = 0;
        int line_count = 0;

        // Première passe : calculer la hauteur totale du texte pour centrage vertical
        const char *ptr_tmp = ptr;
        while (*ptr_tmp) {
            int len = 0, last_space = -1;
            while (ptr_tmp[len] && ptr_tmp[len] != '\n') {
                buffer[len] = ptr_tmp[len];
                if (ptr_tmp[len] == ' ') last_space = len;
                buffer[len + 1] = '\0';

                int w = 0, h = 0;
                TTF_SizeText(font, buffer, &w, &h);
                if (w > max_width) break;
                len++;
            }
            if (ptr_tmp[len] == '\n') {
                buffer[len] = '\0';
                len++;
            } else if (len > 0 && last_space > 0) {
                buffer[last_space] = '\0';
                len = last_space + 1;
            } else {
                buffer[len] = '\0';
            }

            int w = 0, h = 0;
            TTF_SizeText(font, buffer, &w, &h);
            total_text_height += h + line_spacing;
            line_count++;
            ptr_tmp += len;
            while (*ptr_tmp == ' ') ptr_tmp++;
        }

        // Centrage vertical + décalage vers le bas
        int decalage = 100; // Décalage supplémentaire vers le bas (en pixels)
        int start_y = y + (page_perso.h - 40 - total_text_height) / 2 + decalage;
        if (start_y < page_perso.y + 20) start_y = page_perso.y + 20;
        y = start_y;

        // Deuxième passe : affichage du texte centré
        ptr = lore;
        while (*ptr) {
            int len = 0, last_space = -1;
            while (ptr[len] && ptr[len] != '\n') {
                buffer[len] = ptr[len];
                if (ptr[len] == ' ') last_space = len;
                buffer[len + 1] = '\0';

                int w = 0, h = 0;
                TTF_SizeText(font, buffer, &w, &h);
                if (w > max_width) break;
                len++;
            }
            if (ptr[len] == '\n') {
                buffer[len] = '\0';
                len++;
            } else if (len > 0 && last_space > 0) {
                buffer[last_space] = '\0';
                len = last_space + 1;
            } else {
                buffer[len] = '\0';
            }

            SDL_Surface *surf = TTF_RenderText_Blended(font, buffer, color);
            if (surf) {
                SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, surf);
                if (txt) {
                    // Centrage horizontal dans la zone de texte (avec marge)
                    int centered_x = x + (max_width - surf->w) / 2;
                    if (centered_x < page_perso.x + margin) centered_x = page_perso.x + margin;
                    SDL_Rect dst = {centered_x, y, surf->w, surf->h};
                    if (y + surf->h < bottom)
                        SDL_RenderCopy(renderer, txt, NULL, &dst);
                    SDL_DestroyTexture(txt);
                }
                y += surf->h + line_spacing;
                SDL_FreeSurface(surf);
            }
            ptr += len;
            while (*ptr == ' ') ptr++;
        }
        TTF_CloseFont(font);
    } else {
        rect2.x = 0;
        rect2.y = 0;
        rect2.w = 0;
        rect2.h = 0;
        SDL_RenderFillRect(renderer, &rect2);
    }
}

void intro (){
    
}

/* Customisation deu mode de jeu */
void page_de_base(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions,int b_personnalisation,SDL_Texture ** text, coord play2, 
    coord coord_next, coord coord_suiv, int * int_bouton, int page_i, int diff_i){
    SDL_Rect rect2;
    SDL_SetRenderDrawColor(renderer, 0,0,0,120);

    coord page_perso;
    page_perso.w=window_dimensions.w*0.5;
    page_perso.h=window_dimensions.w*0.5;
    page_perso.x=(window_dimensions.w-page_perso.w)/2;
    page_perso.y=(window_dimensions.h-page_perso.h)/4;

    if (b_personnalisation==1) {
        rect2.x=0;
        rect2.y=0;
        rect2.w=window_dimensions.w;
        rect2.h=window_dimensions.h; 
        SDL_RenderFillRect(renderer, &rect2); 

        fond_fixe_xy(text[17],window, renderer, page_perso);
        if (page_i==0) {
            hover_bouton(window, renderer, text[14], text[18], int_bouton[9], coord_next);
        }
        else if ((page_i==1) && (diff_i%4!=3)) {
            hover_bouton(window, renderer, text[14], text[18], int_bouton[10], coord_suiv);
        }
        else if (((page_i==1) && (diff_i%4==3) )|| ((page_i==2) && (diff_i%4==3) )|| ((page_i==3) && (diff_i%4==3))){
            hover_bouton(window, renderer, text[14], text[18], int_bouton[9], coord_next);
            hover_bouton(window, renderer, text[14], text[18], int_bouton[10], coord_suiv);
        }
        else if (page_i%5==4) {
            hover_bouton(window, renderer, text[14], text[18], int_bouton[10], coord_suiv);
        }
    }
    else {
        rect2.x=0;
        rect2.y=0;
        rect2.w=0;
        rect2.h=0; 
        SDL_RenderFillRect(renderer, &rect2);
    }
}

void page_choix_map(SDL_Window * window, SDL_Renderer * renderer, SDL_Rect window_dimensions, int b_personnalisation, SDL_Texture ** map, int map_i, SDL_Texture ** fleche, 
    coord f_droit, coord f_gauche, int b_droit, int b_gauche){
    coord c_texture;
    c_texture.w=window_dimensions.w*0.2;
    c_texture.h=window_dimensions.w*0.2;
    c_texture.x=(window_dimensions.w-c_texture.w)/2;
    c_texture.y=(window_dimensions.h-c_texture.h)/4;
    if (b_personnalisation==1){
        fond_fixe_xy(map[map_i], window, renderer, c_texture); //map
        hover_bouton(window, renderer, fleche[0], fleche[1],b_droit, f_droit); //fleche droite
        hover_bouton(window, renderer, fleche[2], fleche[3],b_gauche, f_gauche); //fleche gauche
    } 
}

void page_difficulte(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, int b_personnalisation, SDL_Texture ** fleche, SDL_Texture ** t_diff, int diff_i,
    coord f_droit, coord f_gauche, int b_droit, int b_gauche){
    //char * difficulte = "D i f f i c u l t y";

    coord  c_texture;
  

    c_texture.w=window_dimensions.w/7;
    c_texture.h=window_dimensions.h/8;
    c_texture.x=(window_dimensions.w- c_texture.w)/2;
    c_texture.y=(window_dimensions.h-c_texture.h)/3;

    //afficher_text(renderer, t_diff, c_diff, b_personnalisation);
    if (b_personnalisation==1){
        fond_fixe_xy(t_diff[diff_i], window, renderer, c_texture); //map
        hover_bouton(window, renderer, fleche[0], fleche[1],b_droit, f_droit); //fleche droite
        hover_bouton(window, renderer, fleche[2], fleche[3],b_gauche, f_gauche); //fleche gauche
    } 
}

void page_custom(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, SDL_Texture * nb_param, SDL_Texture ** fleche, 
    coord f_droit, coord f_gauche, int b_droit, int b_gauche){
    coord c_switch;
    //switch
    c_switch.w= window_dimensions.w/5;
    c_switch.h=window_dimensions.h/20;
    c_switch.x=window_dimensions.w/3;
    c_switch.y=window_dimensions.h/5;
    fond_fixe_xy(nb_param,window, renderer, c_switch);
    hover_bouton(window, renderer, fleche[0], fleche[1],b_droit, f_droit); //fleche droite
    hover_bouton(window, renderer, fleche[2], fleche[3],b_gauche, f_gauche); //fleche gauche
}

void afficher_pages_custom(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, SDL_Texture * text_next, SDL_Texture * text_suiv, SDL_Texture * t_nb_switch, 
    SDL_Texture * t_nb_button, SDL_Texture * t_density,SDL_Texture * t_diff, SDL_Texture ** fleche, SDL_Texture ** map, coord p_next, coord p_suiv, coord f_droit, coord f_gauche, 
    int * int_bouton, int b_droit, int b_gauche, int b_personnalisation, int page_i, int map_i, int diff_i){
    if (page_i%5==0){
            //page choix map
            afficher_text(renderer, text_next, p_next, b_personnalisation);
            page_choix_map(window, renderer, window_dimensions, b_personnalisation, map, map_i, fleche, f_droit, f_gauche, int_bouton[7],int_bouton[8]);
        }
        else if ((page_i %5==1) && (diff_i%4!=3)){
            //page difficulte
            afficher_text(renderer, text_suiv, p_suiv, b_personnalisation);
            page_difficulte(window, renderer, window_dimensions, b_personnalisation, fleche, t_diff, diff_i, f_droit, f_gauche, int_bouton[7], int_bouton[8]);
        }
        else if ((page_i%5 ==1) && (diff_i%4==3)) {
            afficher_text(renderer, text_next, p_next, b_personnalisation);
            afficher_text(renderer, text_suiv, p_suiv, b_personnalisation);
            page_difficulte(window, renderer, window_dimensions, b_personnalisation, fleche, t_diff, diff_i, f_droit, f_gauche, int_bouton[7], int_bouton[8]);
        }
        else if (page_i%5==2) {
            afficher_text(renderer, text_suiv, p_suiv, b_personnalisation);
            afficher_text(renderer, text_next, p_next, b_personnalisation);
            page_custom(window, renderer, window_dimensions, t_nb_switch, fleche, f_droit, f_gauche, int_bouton[7], int_bouton[8]);
        }
        else if (page_i%5==3){
            afficher_text(renderer, text_suiv, p_suiv, b_personnalisation);
            afficher_text(renderer, text_next, p_next, b_personnalisation);
            page_custom(window, renderer, window_dimensions, t_nb_button, fleche, f_droit, f_gauche, int_bouton[7], int_bouton[8]);
        }
        else if (page_i%5==4){
            afficher_text(renderer, text_suiv, p_suiv, b_personnalisation);
            page_custom(window, renderer, window_dimensions, t_density, fleche, f_droit, f_gauche, int_bouton[7], int_bouton[8]);
        }
}

void case_density(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, char * char_density, int nb_density, int boul){

    sprintf(char_density, "%d", nb_density);
    SDL_Texture * t_nb_density= chargement_police(window, renderer, char_density);

    coord coord_t;
    coord_t.w= window_dimensions.w/18;
    coord_t.h=window_dimensions.h/15;
    coord_t.x=(window_dimensions.w-coord_t.w)/2;
    coord_t.y=(window_dimensions.h-window_dimensions.w/12*0.8)/3;


    afficher_text(renderer, t_nb_density, coord_t, boul );
}




// Gestion des polices -----------------------------------------------------------------------------------------

SDL_Texture * chargement_police (SDL_Window * window, SDL_Renderer * renderer, char * text){
    TTF_Font* font = NULL;                                               // la variable 'police de caractère'
    font = TTF_OpenFont("./textures/police/pixel-ultima-bold.ttf", 65);                     // La police à charger, la taille désirée
    if (font == NULL) end_sdl2(0, "Can't load font", window, renderer);
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);

    SDL_Color color = {255, 255, 255, 255};                                  // la couleur du texte
    SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, text, color); // création du texte dans la surface
    if (text_surface == NULL) end_sdl2(0, "Can't create text surface", window, renderer);

    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl2(0, "Can't create texture from surface", window, renderer);
    SDL_FreeSurface(text_surface); 
    return text_texture;
}

void afficher_text(SDL_Renderer *renderer, SDL_Texture * police, coord c_police, int bouton){
    SDL_Rect pos = {c_police.x, c_police.y,c_police.w, c_police.h};
    if (bouton ==1) {
        SDL_RenderCopy(renderer, police, NULL, &pos);
    }
    
}