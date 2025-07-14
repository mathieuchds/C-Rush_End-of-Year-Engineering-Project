#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>


typedef struct {
    int x;
    int y;
    int w;
    int h;
} coord;

// Gestion de la SDL ------------------------------------------------------------------------------------------------
void end_sdl2(char ok, char const* msg, SDL_Window* window,SDL_Renderer* renderer) ;
SDL_Texture* load_texture_from_image2(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );


// Gestion des Textures ----------------------------------------------------------------------------------------------
SDL_Texture ** charge_texture (SDL_Texture ** text, SDL_Window * window, SDL_Renderer * renderer);
void Destroy_Texture(SDL_Texture ** text, int n);
SDL_Texture ** charge_slime (SDL_Texture ** slime, SDL_Window * window, SDL_Renderer * renderer);
SDL_Texture ** charger_map (SDL_Texture ** map, SDL_Window * window, SDL_Renderer * renderer);
SDL_Texture ** charger_flèches (SDL_Texture ** fleches, SDL_Window *window, SDL_Renderer * renderer);


//Fonctions d'affichages ---------------------------------------------------------------------------------------------
void fond_fixe_fenetre(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void fond_fixe_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, coord coord);
void scroll3_background(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer, int scroll_x, float zoom);
void parallax(SDL_Texture ** text, SDL_Window * window, SDL_Renderer * renderer,
    int scroll1, int scroll2, int scroll3, int scroll4, int scroll_sol, coord coord_sol);
void frame (SDL_Texture *my_texture, SDL_Window *window, int nb_images, int nb_ligne,SDL_Rect * state) ;
void afficher (SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int num_frame, coord perso, SDL_Rect * state);


// Gestion des boutons ---------------------------------------------------------------------------------------------------
int pos_cursor(coord coord_button);
int * bouleen_bouton(int * int_boutons, coord coord_play, coord coord_play2, coord coord_param, coord coord_perso, coord slime1, coord slime2, coord slime3, coord f_droit, coord f_gauche, coord next, coord suiv) ;
void hover_bouton (SDL_Window * window, SDL_Renderer * renderer, SDL_Texture *text1, SDL_Texture *text2 , int boul_bouton, coord coord_bouton);
void hover_menu_principal(int * int_bouton, SDL_Texture ** text, SDL_Window * window, SDL_Renderer * renderer, coord coord_play, 
    coord coord_play2, coord coord_param);
void maj_coord(coord * play, coord * play2, coord * param, coord * perso, coord * coord_sol, coord * logo, 
     coord * slime1, coord * slime2, coord * slime3,coord * perso_b, coord * f_droit, coord * f_gauche, coord * police_play, 
     coord * police_play2, coord * police_slime, coord * p_nom_slime1,coord * p_nom_slime2,coord * p_nom_slime3, coord * coord_next, 
     coord* coord_suiv, coord * p_next, coord * p_suiv, SDL_Rect window_dimensions);
void maj_coord_texte(SDL_Rect window_dimensions,coord * police_play, coord * police_play2, coord * police_slime, coord * p_nom_slime1,coord * p_nom_slime2,coord * p_nom_slime3 ) ;
int activer_int(int bouléen);



// Gestion des fenêtres -------------------------------------------------------------------------------------------------
void menu_perso(int slime_clic, SDL_Rect window_dimensions, SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * text);
void bouton_choix_perso(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * button, SDL_Texture * button_hover,
    int bouton, coord slime1, coord slime2, coord slime3);
void bouton_règles (int param, SDL_Rect window_dimensions, SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * text );
void page_de_base(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions,int b_personnalisation,SDL_Texture ** text, coord play2, 
    coord coord_next, coord coord_suiv, int * int_bouton, int page_i, int diff_i);
void page_choix_map(SDL_Window * window, SDL_Renderer * renderer, SDL_Rect window_dimensions, int b_personnalisation, SDL_Texture ** map, int map_i, SDL_Texture ** fleche, 
    coord f_droit, coord f_gauche, int b_droit, int b_gauche);
void page_difficulte(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, int b_personnalisation, SDL_Texture ** fleche, SDL_Texture ** t_diff, int diff_i,
    coord f_droit, coord f_gauche, int b_droit, int b_gauche);
void page_custom(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, SDL_Texture * nb_param, SDL_Texture ** fleche, 
    coord f_droit, coord f_gauche, int b_droit, int b_gauche);

void afficher_pages_custom(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, SDL_Texture * text_next, SDL_Texture * text_suiv, SDL_Texture * t_nb_switch, 
    SDL_Texture * t_nb_button, SDL_Texture * t_density,SDL_Texture * t_diff, SDL_Texture ** fleche, SDL_Texture ** map, coord p_next, coord p_suiv, coord f_droit, coord f_gauche, 
    int * int_bouton, int b_droit, int b_gauche, int b_personnalisation, int page_i, int map_i, int diff_i);


void case_density(SDL_Window * window, SDL_Renderer * renderer,SDL_Rect window_dimensions, char * char_density, int nb_density, int boul);

//char * compteur_custom(int n);

// Gestion des polices -----------------------------------------------------------------------------------------

SDL_Texture * chargement_police (SDL_Window * window, SDL_Renderer * renderer, char * text);
void afficher_text(SDL_Renderer *renderer, SDL_Texture * police, coord c_police, int bouton);