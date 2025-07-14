#include "Moteur_labyrinthe.h"
#include "texture_management.h"
#include "conversion.h"



// Correspondance nom/id
typedef enum {
    SLIME1 = 0,
    SLIME2 = 1,
    SLIME3 = 2,
    SLIME1CHILL = 3,
    SLIME2CHILL = 4,
    SLIME3CHILL = 5,
    SLIME1RUN = 6,
    SLIME2RUN = 7,
    SLIME3RUN = 8,
    SLIME1LIGHT = 9,
    SLIME2LIGHT = 10,
    SLIME3LIGHT = 11,
    MONSTER_ICON1 = 12,
    MONSTER_ICON2 = 13,
    MONSTER_WALK = 14, 
    SLIME1ATTACK = 15, 
    SLIME1DEATH = 16,
    SLIME2ATTACK = 17, 
    SLIME2DEATH = 18,
    SLIME3ATTACK = 19, 
    SLIME3DEATH = 20,
    MONSTER_ATTACK = 21
} entity_name;   


animation_page ** load_entity_animation(entity_name * tab, int taille, SDL_Window * window, SDL_Renderer * renderer);
void get_texture_entity(animation_page * a, int num_anim, int num_frame, SDL_Rect dest, SDL_Renderer * renderer);
void movement(entity * e, maze * m);
int change_direction();
void smooth_player_movement(entity * player, maze * m, SDL_Renderer * renderer, SDL_Window * window,  int w_x, int w_y, int it, int animation_p_attack, int animation_m_attack);
void anim_switching_light(int switching_light, entity * player, SDL_Renderer * renderer, maze * m);
int calcul_direction(int pos_actuelle, int longueur, int destination);
void monster_icon_movement(SDL_Renderer * renderer, entity * monster, int next_step, maze * m, int freq_anim, int mode_hunt, int light, int light_radius, entity * player, int exit_open);
void player_attack_monster(SDL_Renderer * renderer, entity * player, entity * monster, maze * m, int * animation_p_attack, point_interet * p, int freq_anim, int * next_step);
void monster_attack_player(SDL_Renderer * renderer, entity * player, entity * monster, maze * m, point_interet * p, int freq_anim, int w_x, int w_y);
void player_anime_fin(SDL_Renderer * renderer, entity * player, entity * monster, maze * m, point_interet * p, int freq_anim, int w_x, int w_y);