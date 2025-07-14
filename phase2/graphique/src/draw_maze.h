#include "Moteur_labyrinthe.h"
#include "player_movement_graphic.h"

// Renvoi la taille d'une case graphique et crée la texture pour le labyrinthe
int draw_maze_texture(SDL_Renderer *renderer, int window_size_x, int window_size_y, int *construction_mur, int nb_noeud, int taille[2], SDL_Texture **textures, SDL_Rect ** tab_rect, SDL_Texture ** cas_speciaux, int * biomes, SDL_Window * window);

// Dessine le labyrinthe
maze * get_labyrinthe_map(SDL_Window * window, SDL_Renderer * renderer, labyrinthe * l, int with_texture, int * biomes);
 
// Labyrinthe basique
void draw_mur_gauche(SDL_Renderer * renderer, int i, int j, int taille_trait);
void draw_mur_droite(SDL_Renderer * renderer, int i, int j, int taille_trait);
void draw_mur_haut(SDL_Renderer * renderer, int i, int j, int taille_trait);
void draw_mur_bas(SDL_Renderer * renderer, int i, int j, int taille_trait);
int draw_maze(SDL_Renderer * renderer, int window_size_x, int window_size_y, int * construction_mur, int nb_noeud, int taille[2]);
void draw_spawns(SDL_Renderer * renderer, point_interet * spawns, SDL_Texture ** spawn_tab_texture, SDL_Rect ** spawn_tab_rect, maze * m, int exit_open, int it_spawns);
// Affiche le graphe coloré 
void draw_maze_BFS(SDL_Renderer *renderer, int window_size_x, int window_size_y, int * tab_coloration, maze * m, int * path, int depart, int arrivee, TTF_Font *font);
void auto_movement_with_path(entity * player, int * path, maze * m, SDL_Renderer * renderer, int speed, SDL_Window * window, int arrivee, int depart);
void draw_maze_Dijkstra(SDL_Renderer *renderer, int window_size_x, int window_size_y, int * tab_visite, maze * m, int * path, int depart, int arrivee, TTF_Font * font);

// animation
void affiche_movement_auto(entity * player, int direction, maze * m, SDL_Renderer * renderer, int speed, SDL_Window * window, int coo_a[2], int coo_d[2]);

void init_level(SDL_Renderer * renderer, SDL_Window * window, maze ** m, labyrinthe * l, entity_name * tab_e, animation_page *** all_anim, entity ** player, int id_slime, int with_texture, int nb_anim, int * biomes, int * button, point_interet * spawns, entity ** monster);

SDL_Texture *create_halo_texture(SDL_Renderer *renderer, int radius);
void black_fog(SDL_Renderer *renderer, int player_x, int player_y, int radius, int screen_width, int screen_height);
void render_halo(SDL_Renderer *renderer, SDL_Texture *halo_texture, int player_x, int player_y, int radius);

void labyrinthe_ui(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *icon_texture, int nb_switch, int w_x, int nb_button, SDL_Texture * icon_texture2, int tot_button);

void maj_button(maze * m, SDL_Renderer * renderer, SDL_Window * window, entity * player, int * button_pressed);
void maj_button_vm(maze * m, SDL_Renderer * renderer, SDL_Window * window, entity * monstre, int * button_pressed);

void init_spawns_tab(SDL_Renderer * renderer, SDL_Window * window,SDL_Rect ** tab_rect, SDL_Texture ** texture_tab);
void draw_spawns(SDL_Renderer * renderer, point_interet * spawns, SDL_Texture ** spawn_tab_texture, SDL_Rect ** spawn_tab_rect, maze * m, int exit_open, int it_spawns);
//void anim_exit(SDL_Renderer * renderer, char * image,int w_x, int w_y, entity * player, int duree);

void manage_player_path(SDL_Renderer * renderer, entity * player, int tab_path[][2], int * curseur_tab_path, int taille_tab, maze * m, int light, int light_radius, SDL_Texture * slime_trace[4]);
void manage_monster_path(SDL_Renderer * renderer, entity * monster, int tab_path[][2], int * curseur_tab_path, int taille_tab, maze * m, SDL_Texture * slime_trace[4]);
void drawGauge(SDL_Renderer* renderer, int compteur, int val_max);
void init_anim_tab(char * image, SDL_Renderer * renderer, SDL_Texture ** tab_texture_anim);
void afficher_grille(SDL_Renderer *renderer, TTF_Font *font, int *tab, int nb_lignes, int nb_colonnes,
                     int taille_case, int start_index, int end_index);