#include "texture_management.h"

// Affiche un fond fixe
void play_with_texture_2(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer, float zoom) {
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);  

    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x = (window_dimensions.w - destination.w) /2; // milieu
    destination.y =
    (window_dimensions.h - destination.h) / 2;  // milieu

    SDL_RenderCopy(renderer, my_texture, &source, &destination);                       
}


SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;       
    SDL_Texture* my_texture = NULL;
    
    if (renderer == NULL) printf("renderer très sad\n");

    my_image = IMG_Load(file_image_name);  
                                            
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer, NULL, NULL, 0);
   
    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); 
    SDL_FreeSurface(my_image);                                      
    if (my_texture == NULL){
        printf("ou est la texture?\n");
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer, NULL,  NULL, 0);
    } 

    return my_texture;
}

SDL_Rect *load_rectangle_from_sprite(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer, int dim[2], int * correspondance, int offset){
    SDL_Surface *my_image = IMG_Load(file_image_name);
    if (my_image == NULL) 
        end_sdl(0, "Chargement de l'image impossible", window, renderer, NULL,  NULL, 0);

    SDL_Rect *my_rect_tab = malloc(sizeof(SDL_Rect) * dim[0]*dim[1]);
    if (my_rect_tab == NULL) {
        free(my_rect_tab);
        end_sdl(0, "Erreur d'allocation mémoire", window, renderer, NULL,  NULL, 0);
    }

    int sprite_width = my_image->w / dim[0];
    int sprite_height = my_image->h / dim[1];

    for (int i = 0; i < dim[0]; ++i) {
        for(int j=0; j<dim[1]; j++){
            SDL_Rect src_rect = { i * sprite_width + offset, j*sprite_height, sprite_width -2*offset, sprite_height};

            my_rect_tab[correspondance[i+j*dim[1]]] = src_rect;
        }
    }

    SDL_FreeSurface(my_image);
    return my_rect_tab;
}

// Permet de charger un tableau de reclangle par ligne de sprite
SDL_Rect ** load_rectangle_tab2D_from_sprite(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer, int dim[2], int * correspondance, int offset){
    SDL_Surface *my_image = IMG_Load(file_image_name);
    if (my_image == NULL)
        return NULL;
    SDL_Rect **my_rect_tab = malloc(sizeof(SDL_Rect*) * dim[0]);
    if (my_rect_tab == NULL) {
        free(my_rect_tab);
        return NULL;
    }
    for(int i=0;i<dim[0];i++){
        my_rect_tab[i] = malloc(sizeof(SDL_Rect) * dim[1]);
        if (my_rect_tab[i] == NULL) {
            free(my_rect_tab);
            return NULL;
        }
    }

    int sprite_width = my_image->w / dim[1];
    int sprite_height = my_image->h / dim[0];

    if((!strcmp(file_image_name,"textures/Slime3_Walk_full.png"))||(!strcmp(file_image_name,"textures/Slime1_Walk_full.png"))||(!strcmp(file_image_name,"textures/Slime2_Walk_full.png"))){
        for (int i = 0; i < dim[0]; i++) {
            for(int j=0; j<dim[1]; j++){
                if(i < 2){
                    SDL_Rect src_rect = {j*sprite_width + offset, i * sprite_height + offset, sprite_width - 2*offset, sprite_height - 2*offset};
                    my_rect_tab[i][correspondance[j]] = src_rect;
                }else if(i == 2){
                    SDL_Rect src_rect = {j*sprite_width + offset/2, i * sprite_height + offset, sprite_width - 2*offset, sprite_height - 2*offset};
                    my_rect_tab[i][correspondance[j]] = src_rect;
                }else if(i == 3){
                    SDL_Rect src_rect = {j*sprite_width + offset*3/2, i * sprite_height + offset, sprite_width - 2*offset, sprite_height - 2*offset};
                    my_rect_tab[i][correspondance[j]] = src_rect;
                }  
            }
        }
    }else{
        for (int i = 0; i < dim[0]; i++) {
            for(int j=0; j<dim[1]; j++){
                SDL_Rect src_rect = {j*sprite_width + offset, i * sprite_height + offset, sprite_width - 2*offset, sprite_height - 2*offset};
                my_rect_tab[i][correspondance[j]] = src_rect;
            }
        }
    }

    SDL_FreeSurface(my_image);
    return my_rect_tab;
}

void render_focus_centered(SDL_Renderer* renderer, SDL_Texture* source_texture, SDL_Rect focus_rect, int window_width, int window_height){
    // Calcul de la position pour centrer la zone ciblée dans la fenêtre
    SDL_Rect dst_rect = {
        (window_width - focus_rect.w) / 2,
        (window_height - focus_rect.h) / 2,
        focus_rect.w,
        focus_rect.h
    };

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, source_texture, &focus_rect, &dst_rect);
}

void afficher_animation_page(animation_page **all_anim, int nb_anim) {

    for (int i = 0; i < nb_anim; i++) {
        printf("Animation entity %d :\n", i);
        if (all_anim[i] == NULL) {
            printf("  NULL animation_page\n");
            continue;
        }

        printf("  Nombre d'animations : %d\n", all_anim[i]->nb_anim);
        printf("  Durées : ");
        for (int j = 0; j < all_anim[i]->nb_anim; j++) {
            printf("%d ", all_anim[i]->duree[j]);
        }
        printf("\n");

        for (int j = 0; j < all_anim[i]->nb_anim; j++) {
            printf("  Animation %d :\n", j);
            for (int k = 0; k < all_anim[i]->duree[j]; k++) {
                SDL_Rect r = all_anim[i]->tab[j][k];
                printf("    Frame %d : x=%d y=%d w=%d h=%d\n", k, r.x, r.y, r.w, r.h);
            }
        }

        printf("\n");
    }
}

// free les ressources SDL 
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture ** tab_texture, animation_page ** all_anim, int nb_anim) {                           

    char msg_formated[255];                                            
    int l;                                                     
    printf("END \n");                        

    if (!ok) {                                      
        strncpy(msg_formated, msg, 250);                                         
        l = strlen(msg_formated);                                            
        strcpy(msg_formated + l, " : %s\n");                                              
        SDL_Log(msg_formated, SDL_GetError());                                   
    }                                                          
                                            
    if (renderer != NULL) {                                          
        SDL_DestroyRenderer(renderer);                              
        renderer = NULL;
    }
    if (window != NULL) {                                         
        SDL_DestroyWindow(window);                                  
        window = NULL;
    }

    int i = 0;
    if(tab_texture != NULL){
        while(tab_texture[i] != NULL){
            SDL_DestroyTexture(tab_texture[i]);
            i++;
        }
    }

    if (all_anim != NULL) {
        for (int i = 0; i < nb_anim; i++) {
            if (all_anim[i] != NULL) {
                if (all_anim[i]->texture != NULL) {
                    SDL_DestroyTexture(all_anim[i]->texture);
                }

                if (all_anim[i]->tab != NULL) {
                    for (int j = 0; j < all_anim[i]->nb_anim; j++) {
                        if (all_anim[i]->tab[j] != NULL) {
                            free(all_anim[i]->tab[j]); // ligne d'animation
                        }
                    }
                    free(all_anim[i]->tab); // tableau des lignes
                }

                if (all_anim[i]->duree != NULL) {
                    free(all_anim[i]->duree);
                }

                free(all_anim[i]); // structure animation_page
            }
        }

        free(all_anim); // tableau de pointeurs
    }
    TTF_Quit();
    SDL_Quit();                                                    
                                            
    if (!ok) {                                               
        exit(EXIT_FAILURE);                                                  
    }                                                          
} 

void init_sdl(SDL_Renderer ** renderer, SDL_Window ** window){
    SDL_DisplayMode screen;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", *window, NULL, NULL, NULL, 0);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        end_sdl(0, "Erreur IMG_Init", *window, NULL, NULL, NULL, 0);
    
    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    *window = SDL_CreateWindow("Mativa's Adventures",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               0, 0,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (*window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", NULL, NULL, NULL, NULL, 0);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (*renderer == NULL){
        printf("renderer null\n");
        end_sdl(0, "ERROR RENDERER CREATION", *window, NULL, NULL, NULL, 0);
    }
}

SDL_Surface* TextureToSurface(SDL_Renderer* renderer, SDL_Texture* texture) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    // Crée une texture cible compatible pour copier dedans
    SDL_Texture* copy = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!copy) {
        SDL_Log("Erreur SDL_CreateTexture : %s", SDL_GetError());
        return NULL;
    }

    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, copy);

    // On nettoie la cible
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // On copie la texture source dedans
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // On lit les pixels de la copie
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        SDL_Log("Erreur SDL_CreateRGBSurfaceWithFormat : %s", SDL_GetError());
        SDL_DestroyTexture(copy);
        SDL_SetRenderTarget(renderer, old_target);
        return NULL;
    }

    if (SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch) != 0) {
        SDL_Log("Erreur SDL_RenderReadPixels : %s", SDL_GetError());
        SDL_FreeSurface(surface);
        surface = NULL;
    }

    SDL_SetRenderTarget(renderer, old_target);
    SDL_DestroyTexture(copy);
    return surface;
}

void free_maze(maze *m) {
    if (m == NULL) return;
    if (m->map) {
        SDL_DestroyTexture(m->map);
        m->map = NULL;
    }
    if (m->button_texture) {
        SDL_DestroyTexture(m->button_texture);
        m->button_texture = NULL;
    }
    if (m->construction) {
        free(m->construction);
        m->construction = NULL;
    }
    if (m->poids) {
        free(m->poids);
        m->poids = NULL;
    }
    if (m->button) {
        free(m->button);
        m->button = NULL;
    }
}