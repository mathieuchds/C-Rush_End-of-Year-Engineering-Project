#define SDL_ON 1
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "base_func.h"
#include "graphic_func.h"


int main(int argc, char** argv){

    // Variables permanentes

    (void)argc;
    (void)argv;
    srand(time(NULL));

    int up = 0;
    int tab_pipe[8] = {0}; // tableau réel de taille 6, deux cases de marge pour graphique
    tab_pipe[0] = 1;
    float it_pipe = 0;
    int it_pipe_int = 0;
    int bee = 0; 
    float sensi = 1;
    int lost = 0;
    char message[20];
    int score = 0;
    int program_on = 1;

#if SDL_ON

        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        SDL_DisplayMode screen;

        if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer, NULL);

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            end_sdl(0, "Erreur IMG_Init", window, renderer, NULL);
        }

        if (TTF_Init() != 0) {
            printf("Erreur TTF: %s\n", TTF_GetError());
            SDL_Quit();
            return 1;
        }

        TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 48); 
        if (!font) {
            printf("Erreur chargement police: %s\n", TTF_GetError());
            return 1;
        }

        SDL_GetCurrentDisplayMode(0, &screen);
        printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

        window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, SDL_WINDOW_OPENGL);
        if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer, NULL);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer, NULL);

        SDL_Texture * tab_texture[20] = {NULL};

        SDL_Texture * bee_anim[4];
        bee_anim[0] = load_texture_from_image("textures/bee_a.png", window, renderer);
        bee_anim[1] = load_texture_from_image("textures/bee_b.png", window, renderer);

        tab_texture[0] = bee_anim[0];
        tab_texture[1] = bee_anim[1];

        SDL_Texture * background1 = load_texture_from_image("textures/background_solid_sky2.png", window, renderer);
        SDL_Texture * background2 = load_texture_from_image("textures/background_color_trees2.png", window, renderer);
        SDL_Texture * background3 = load_texture_from_image("textures/background_color_trees3.png", window, renderer);
        SDL_Texture * background4 = load_texture_from_image("textures/background_clouds4.png", window, renderer);
        SDL_Texture * background5 = load_texture_from_image("textures/background_clouds.png", window, renderer);

        tab_texture[2] = background1;
        tab_texture[3] = background2;
        tab_texture[4] = background3;
        tab_texture[5] = background4;
        tab_texture[6] = background5;

        SDL_Texture * pipe_up = load_texture_from_image("textures/pipe_up2.png", window, renderer);
        SDL_Texture * pipe_down = load_texture_from_image("textures/pipe_down2.png", window, renderer);

        tab_texture[7] = pipe_up;
        tab_texture[8] = pipe_down;

        SDL_Event event;                              // Evènement à traiter
        
        //paused = SDL_FALSE,                             // Booléen pour dire que le programme est en pause
        SDL_bool event_utile = SDL_FALSE;                        // Booléen pour savoir si on a trouvé un event traité 
        

        int w_x; int w_y;
        SDL_GetWindowSize(window,&w_x,&w_y);
        int it = 0;
        int scroll_x = 0;
        sensi = 6;
#endif
    
    
    while(program_on){

#if SDL_ON // Mode SDL    

            if (SDL_PollEvent(&event)){      
                switch(event.type){
                    case SDL_QUIT:
                        program_on = SDL_FALSE;                
                        event_utile = SDL_TRUE;
                        break;
                    case SDL_KEYDOWN:                            
                        switch (event.key.keysym.sym) {
                        case SDLK_q:                               
                            program_on = 0;                         
                            break;
                        /*case SDLK_UP:
                            if(bee<3*sensi){
                                bee ++;
                            }
                            break;
                        case SDLK_DOWN:
                            if(bee>-3*sensi){
                                bee --;
                            }
                            break;*/
                        default:                                   
                            break;
                        }
                }
            }

            const Uint8* keystates = SDL_GetKeyboardState(NULL);
            if (keystates[SDL_SCANCODE_UP]) {
                if (bee < 3 * sensi) {
                    bee++;
                }
            }
            if (keystates[SDL_SCANCODE_DOWN]) {
                if (bee > -3 * sensi) {
                    bee--;
                }
            }

            it++;
            scroll_x += 7;
            SDL_RenderClear(renderer);

            if(lost == 0){
                play_with_texture_2(background1 ,window, renderer, 3); // ciel
                scroll_background(background4, window, renderer, scroll_x/4, 1.5); // arbre en fond
                scroll_background(background3, window, renderer, scroll_x/2, 1.5); // arbre en fond
                scroll_background(background2, window, renderer, scroll_x, 1.5); // arbres verts
                bee_moove(window, renderer, bee, bee_anim[it%2], 0.7, sensi);
                pipe_spawn(window, renderer, pipe_up, pipe_down, tab_pipe, it_pipe); // dessi tuyau
            }
#else
    char saisie;
    int modif = 0;
    while (!modif) {
        printf("Tape 'u' (monter), 'd' (descendre), 'q' (quitter) : ");
        scanf(" %c", &saisie);

        if (saisie == 'u') {
            bee += 1;
            modif = 1;
        } else if (saisie == 'd') {
            bee -= 1;
            modif = 1;
        } else if (saisie == 'q') {
            program_on = 0;
            break;
        } else {
            printf("Entrée invalide\n");
        }
    }
    printf("\n\nNouvelle position de l'abeille en hauteur: %d\n", bee);
    printf("L'abeille est au niveau du tuyau numéro 5\n");
#endif 

        if(lost == 0){
            if(tab_pipe[4] > 0){
                if((bee >= 0)&&((3==tab_pipe[4])||((bee/sensi >= 1)&&(tab_pipe[4]==2))||((bee/sensi >= 2)&&(tab_pipe[4]==1)))){
                    //printf("bee :%d pipe:%f \n",bee, tab_pipe[4]*sensi);
                    lost = 1;
                }
            }
            if(tab_pipe[4] < 0){
                if((bee <= 0)&&((-3==tab_pipe[4])||((bee/sensi <= -1)&&(tab_pipe[4]==-2))||((bee/sensi <= -2)&&(tab_pipe[4]==-1)))){
                    //printf("bee :%d pipe:%f \n",bee, tab_pipe[4]*sensi);
                    lost = 1;
                }
            }
            if(up == 1){
                up = 0;
            }else{
                up = 1;
            }
        }

        if(lost == 0){
            it_pipe_int ++;
#if(SDL_ON)
            it_pipe += w_x/48;
            if(it_pipe_int%8 == 0){ // modif réelle des tuyaux
                it_pipe = 0;
                score = pipe_management(tab_pipe, score);
            }
#else
            score = pipe_management(tab_pipe, score);
            
            printf("Tuyaux actuels : ");
            for(int i=0;i<8;i++){
                printf("%d ", tab_pipe[i]);
            }
            printf("\nScore : %d\n\n",score);
#endif

#if(SDL_ON)
            SDL_Color textColor = {200, 200, 200, 255}; 
            sprintf(message, "%d", score);
            SDL_Surface* textSurface = TTF_RenderText_Blended(font, message, textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            int textW = textSurface->w;
            int textH = textSurface->h;
            SDL_FreeSurface(textSurface);
            SDL_Rect dstRect;
            dstRect.x = 25;
            dstRect.y = 25;
            dstRect.w = textW;
            dstRect.h = textH;
            SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
#endif
        }

        if(lost == 1){ // Mode SDL
#if SDL_ON
            play_with_texture_2(background5 ,window, renderer, 3); // fin
            
            SDL_Color textColor = {255, 255, 255, 255};

            SDL_Surface* textSurface1 = TTF_RenderText_Blended(font, "Game Over", textColor);
            SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
            int textW1 = textSurface1->w;
            int textH1 = textSurface1->h;
            SDL_FreeSurface(textSurface1);
            SDL_Rect dstRect1;
            dstRect1.x = (w_x - textW1) / 2;
            dstRect1.y = (w_y - textH1) / 2 - 30;  
            dstRect1.w = textW1;
            dstRect1.h = textH1;
            SDL_RenderCopy(renderer, textTexture1, NULL, &dstRect1);

            char scoreText[50];
            sprintf(scoreText, "Score : %d", score);
            SDL_Surface* textSurface2 = TTF_RenderText_Blended(font, scoreText, textColor);
            SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
            int textW2 = textSurface2->w;
            int textH2 = textSurface2->h;
            SDL_FreeSurface(textSurface2);
            SDL_Rect dstRect2;
            dstRect2.x = (w_x - textW2) / 2;
            dstRect2.y = dstRect1.y + textH1 + 10;  
            dstRect2.w = textW2;
            dstRect2.h = textH2;
            SDL_RenderCopy(renderer, textTexture2, NULL, &dstRect2);

            SDL_DestroyTexture(textTexture1);
            SDL_DestroyTexture(textTexture2);
#endif

#if(!SDL_ON)
            program_on = 0;
            printf("GAME OVER : score = %d\nPosition finale abeille : %d\nPosition finale tuyaux :", score, bee);
            for(int i=0;i<8;i++){
                printf("%d ", tab_pipe[i]);
            }
            printf("\n");
#endif    
        }
            
#if SDL_ON
            SDL_RenderPresent(renderer);         
            SDL_Delay(100);
#endif
    } // Fin boucle event
    
#if SDL_ON
        end_sdl(1, "Normal ending", window, renderer, tab_texture);
        IMG_Quit();
        return EXIT_SUCCESS;
#endif
        printf("Fin\n");
        return 0;
}
