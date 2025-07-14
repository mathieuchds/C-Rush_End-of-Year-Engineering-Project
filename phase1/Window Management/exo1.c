#include <SDL2/SDL.h>
    #include <stdio.h>

/************************************/
/*

Le programme permet de faire apparaitre 9 fenêtres et de les sélectionner
avec les touches de 1 à 9.
Une fois une fenêtre séléctionnée, il est possible de la déplacer grace aux
fleches directionnelles, de les faire grossir avec le bouton p, ou rétrécir
avec le bouton m.
On peut quitter avec q.

*/
/************************************/

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    SDL_Window * tab_windows[9];
    SDL_Renderer * tab_renderer[9];

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());                
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode dim_ecran;
    if (SDL_GetCurrentDisplayMode(0, &dim_ecran) != 0) {
        printf("Erreur SDL_GetCurrentDisplayMode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int j =0;
    for(int i = 0;i<9;i++){
        char tmp[10];
        if(i%3 == 0){j++;}
        sprintf(tmp,"%c", i+1+'0');
        tab_windows[i] = SDL_CreateWindow(tmp,300 + (i%3)*150, j*150, 100, 100,  SDL_WINDOW_RESIZABLE);
        tab_renderer[i] = SDL_CreateRenderer(tab_windows[i], -1, SDL_RENDERER_ACCELERATED);
        //printf("%d %d\n",(i%3)*100, j*100);
        if (tab_windows[i] == NULL) {
            SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());    
            SDL_Quit();                                                                
            exit(EXIT_FAILURE);
        }
    }

    // SDL_Delay(5000);                        

    SDL_bool
    program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
    paused = SDL_FALSE,                             // Booléen pour dire que le programme est en pause
    event_utile = SDL_FALSE;                        // Booléen pour savoir si on a trouvé un event traité 
    SDL_Event event;                                // Evènement à traiter

    int current = 0;

    while (program_on){                           // Voilà la boucle des évènements 
        if (SDL_PollEvent(&event)){                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
            switch(event.type){
                case SDL_QUIT:
                    program_on = SDL_FALSE;                
                    event_utile = SDL_TRUE;
                    break;
                case SDL_KEYDOWN:
                    int x; 
                    int y;                             
                    switch (event.key.keysym.sym) {
                    case SDLK_1:                                
                        current = 0;
                        break;
                    case SDLK_2:                                
                        current = 1;
                        break;
                    case SDLK_3:                                
                        current = 2;
                        break;
                    case SDLK_4:                                
                        current = 3;
                        break;
                    case SDLK_5:                                
                        current = 4;
                        break;
                    case SDLK_6:                                
                        current = 5;
                        break;
                    case SDLK_7:                                
                        current = 6;
                        break;
                    case SDLK_8:                                
                        current = 7;
                        break;
                    case SDLK_9:                                
                        current = 8;
                        break;
                    case SDLK_q:                               
                        program_on = 0;                         
                        break;
                    case SDLK_LEFT:
                        SDL_GetWindowPosition(tab_windows[current],&x,&y);
                        if(x-20 > 0){
                            x -= 20;
                        }else{
                            x = 0;
                        }
                        SDL_SetWindowPosition(tab_windows[current],x,y);
                        break;
                    case SDLK_RIGHT:
                        SDL_GetWindowPosition(tab_windows[current],&x,&y);
                        if(x+20 < dim_ecran.w){
                            x += 20;
                        }else{
                            x = dim_ecran.w;
                        }
                        SDL_SetWindowPosition(tab_windows[current],x,y);
                        break;
                    case SDLK_UP:
                        SDL_GetWindowPosition(tab_windows[current],&x,&y);
                        if(y-20 > 0){
                            y -= 20;
                        }else{
                            y = 0;
                        }
                        SDL_SetWindowPosition(tab_windows[current],x,y);
                        break;
                    case SDLK_DOWN:
                        SDL_GetWindowPosition(tab_windows[current],&x,&y);
                        if(y+20 < dim_ecran.h){
                            y += 20;
                        }else{
                            y = dim_ecran.h;
                        }
                        SDL_SetWindowPosition(tab_windows[current],x,y);
                        break;
                    case SDLK_p:
                        SDL_GetWindowSize(tab_windows[current],&x,&y);
                        x += 20; y += 20;
                        SDL_SetWindowSize(tab_windows[current],x,y);
                        SDL_SetRenderDrawColor(tab_renderer[current], 0, 0, 0, 255); // noir
                        SDL_RenderClear(tab_renderer[current]);
                        SDL_RenderPresent(tab_renderer[current]);
                        break;
                    case SDLK_m:
                        SDL_GetWindowSize(tab_windows[current],&x,&y);
                        x -= 20; y -= 20;
                        SDL_SetWindowSize(tab_windows[current],x,y);
                        break;
                    default:                                   
                        break;
                    }
            }
        }
    }  

    
    for(int i = 0;i<9;i++){
        SDL_DestroyWindow(tab_windows[i]); 
        SDL_DestroyRenderer(tab_renderer[i]);               
    }

    SDL_Quit();                          

    return 0;
}