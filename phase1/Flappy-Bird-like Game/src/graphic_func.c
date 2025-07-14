#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>  
#include "graphic_func.h"


// free les ressources SDL
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture ** tab_texture) {                           
    
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
    if (window != NULL)   {                                         
        SDL_DestroyWindow(window);                                  
        window= NULL;
    }
    int i = 0;
    if(tab_texture != NULL){
        while(tab_texture[i] != NULL){
            SDL_DestroyTexture(tab_texture[i]);
            i++;
        }
    }
                                            
    SDL_Quit();                                                    
                                            
    if (!ok) {                                               
        exit(EXIT_FAILURE);                                                  
    }                                                          
}                    

// Charge une texture
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;       
    SDL_Texture* my_texture = NULL;     

    my_image = IMG_Load(file_image_name);  
                                            
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer, NULL);
   
    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); 
    SDL_FreeSurface(my_image);                                      
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer, NULL);

    return my_texture;
}

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

// Affiche un fond infini en mouvement
void scroll_background(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer, int scroll_x, float zoom) {
    SDL_Rect window_dimensions = {0};
    SDL_Rect source = {0};
    SDL_Rect dest1 = {0}, dest2 = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    int bg_width = source.w * zoom;
    int bg_height = source.h * zoom;

    dest1.w = dest2.w = bg_width;
    dest1.h = dest2.h = bg_height;
    dest1.y = dest2.y = window_dimensions.h - bg_height;

    scroll_x %= bg_width; // remet à 0 quand on dépasse une largeur
    dest1.x = +scroll_x;
    dest2.x = dest1.x - bg_width;

    SDL_RenderCopy(renderer, texture, NULL, &dest1);
    SDL_RenderCopy(renderer, texture, NULL, &dest2);
}

// Affiche les tuyaux
void pipe_spawn(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * pipe_up, SDL_Texture * pipe_down, int tab_pipe[8], int it_pipe){
    SDL_Rect window_dimensions = {0};
    SDL_Rect source = {0};
    SDL_Rect dest1 = {0};

    if (pipe_up == NULL || pipe_down == NULL) {
        printf("Erreur de chargement des tuyaux\n");
    }

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    it_pipe -= window_dimensions.w * 1/12;

    for(int i = 0;i<8;i++){
        if(tab_pipe[i] > 0){
            SDL_QueryTexture(pipe_down, NULL, NULL, &source.w, &source.h);
            float zoom = 0.3;
            //int pipe_width = source.w * zoom;
            int pipe_height = source.h * zoom;

            dest1.w = window_dimensions.w/6;
            dest1.h = tab_pipe[i]*pipe_height/3;
            dest1.y = 0;
            dest1.x = window_dimensions.w/6 * (i-1) + it_pipe;

            SDL_RenderCopy(renderer, pipe_down, NULL, &dest1);
        }else if(tab_pipe[i] < 0){
            SDL_QueryTexture(pipe_up, NULL, NULL, &source.w, &source.h);
            float zoom = 0.3;
            //int pipe_width = source.w * zoom;
            int pipe_height = source.h * zoom;

            dest1.w = window_dimensions.w/6;
            dest1.h = -1*tab_pipe[i]*pipe_height/3;;
            dest1.y = window_dimensions.h - dest1.h;
            dest1.x = window_dimensions.w/6 * (i-1) + it_pipe;

            SDL_RenderCopy(renderer, pipe_up, NULL, &dest1);
        }
        //printf("w:%d h:%d x:%d y:%d\n", dest1.w, dest1.h, dest1.x, dest1.y);
    }
}

// Fais bouger l'abeille sur un axe vertical
void bee_moove(SDL_Window * window, SDL_Renderer * renderer, int bee, SDL_Texture * texture, float zoom, int sensi){
    SDL_Rect 
        source = {0},                      
        window_dimensions = {0},           
        destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);               
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);  

    destination.w = source.w * zoom;         
    destination.h = source.h * zoom;         
    destination.x = 4*window_dimensions.w /6;
    destination.y = (window_dimensions.h - destination.h) / 2 - bee * window_dimensions.h / (6*sensi);
    SDL_RenderCopy(renderer, texture, &source, &destination);                   
}
