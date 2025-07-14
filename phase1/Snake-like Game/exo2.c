#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

    void end_sdl(char ok,                                               
          char const* msg,                                       
          SDL_Window* window,                                   
          SDL_Renderer* renderer) {                              
    
        char msg_formated[255];                                            
       int l;                                                     
                                            
       if (!ok) {                                                      
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
     
    int snake(SDL_Renderer *renderer, SDL_Window *window, int s[][3], int size, int apple[2]){
      
      SDL_RenderClear(renderer);

      int w_x; int w_y;
      SDL_GetWindowSize(window,&w_x,&w_y);

      SDL_Rect rect;
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      rect.x = 0; rect.y = 0;
      rect.w = w_x; rect.h = w_y;
      SDL_RenderFillRect(renderer, &rect);

      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      rect.x = apple[0]*w_x/20; rect.y = apple[1]*w_y/20;
      rect.w = w_x/20; rect.h = w_y/20;
      SDL_RenderFillRect(renderer, &rect);

      for(int i=size-1;i>-1;i--){
        if(s[i][2] == 1){ // si on va a droite
          s[i][0] ++;
        }else if(s[i][2] == 0){ // si on va a gauche
          s[i][0] --;
        }
        else if(s[i][2] == 2){ // si on va en haut
          s[i][1] --;
        }else{ // si on va en bas
          s[i][1] ++;
        }

        if(i != 0){
          s[i][2] = s[i-1][2];
        }else{
          if((s[i][0] < 0)||(s[i][1] < 0)||(s[i][0] > 20)||(s[i][1] > 20)){ // si on se cogne au bord
            printf("lost : %d %d %d\n", s[i][0], s[i][1], s[i][2]);
            return -1;
          }
        }

        SDL_SetRenderDrawColor(renderer, (i*40)%255, 0, 0, 255);
        rect.x = s[i][0]*w_x/20; rect.y = s[i][1]*w_y/20;
        rect.w = w_x/20; rect.h = w_y/20;
        SDL_RenderFillRect(renderer, &rect);
      }

      for(int j=0;j<size;j++){
        for(int i=0;i<size;i++){
            if((i!=j)&&(s[i][0] == s[j][0])&&(s[i][1] == s[j][1])){
              printf("lost 2: %d %d %d\n", s[i][0], s[i][1], s[i][2]);
              return -1;
            }
          }
      }


      return 0;
    }
    
    void pick_apple(int apple[2], int s[][3], int size){
      int tab[20][20] = {0};
      for(int i=0;i<size;i++){
        tab[s[i][0]][s[i][1]] = 1;
      }
      int jump = rand() % (400 - size - 1);
      int k = 0;
      int i=0; int j=0;
      while(k != jump){
        if(tab[i][j] == 0){
          k++;
        }
        i++;
        if(i%20 == 0){
          i=0;j++;
        }
      }
      apple[0] = i;
      apple[1] = j; 
      printf("apple : %d %d\n", i, j);
    }
    

    int main(int argc, char** argv) {
       (void)argc;
       (void)argv;
       srand(time(NULL));

       SDL_Window* window = NULL;
       SDL_Renderer* renderer = NULL;

       SDL_DisplayMode screen;

      if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

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
       printf("Résolution écran\n\tw : %d\n\th : %d\n",
          screen.w, screen.h);

       window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w * 0.66, screen.h * 0.66, SDL_WINDOW_OPENGL);
       if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

       renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
       if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

        SDL_bool
        program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
        event_utile = SDL_FALSE;                        // Booléen pour savoir si on a trouvé un event traité 
        SDL_Event event;                                // Evènement à traiter
        
        // Variables pour le logo animé
        int itx = 1;
        int ity = 1;
        int x; int y;
        int xdir = 1; int ydir = 1;
        SDL_GetWindowSize(window,&x,&y);

        // Variables pour le snake
        int s[400][3] = {{4, 10, 1}, {3, 10, 1}, {2, 10, 1}, {1, 10, 1}, {0,10, 1}}; 
        int lost = 0;
        int switch_prog = 1;
        int it_g = 0;
        int size = 5;
        int apple[2];
        pick_apple(apple, s, size);
        for(int i = 5;i<400;i++){
          s[i][0] = 0;
          s[i][1] = 0;
          s[i][2] = 0;
        }
        char message[20];

        while (program_on){                           
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
                        case SDLK_SPACE:
                            switch_prog *= -1;
                            break;
                        case SDLK_RIGHT:
                            if(s[0][2] != 0){s[0][2] = 1;}
                            break;
                        case SDLK_LEFT:
                            if(s[0][2] != 1){s[0][2] = 0;}
                            break;
                        case SDLK_UP:
                            if(s[0][2] != 3){s[0][2] = 2;}
                            break;
                        case SDLK_DOWN:
                            if(s[0][2] != 2){s[0][2] = 3;}
                            break;
                        default:                                   
                            break;
                        }
                }
            }

            // Logo windows rebondissant
            if(switch_prog == 1){
              SDL_Rect rect;
              SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
              rect.x = 0; rect.y = 0;
              rect.w = x; rect.h = y;
              SDL_RenderFillRect(renderer, &rect); 

              if((itx == x-50)||(itx == 0)){
                  xdir *= -1;
              }
              if((ity == y-50)||(ity == 0)){
                  ydir *= -1;
              }
              itx += xdir;
              ity += ydir;

              SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
              rect.x = itx;                                 
              rect.y = ity;                        
              rect.w = 50;                              
              rect.h = 50;
              SDL_RenderFillRect(renderer, &rect);
              
              SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200);
              rect.x = itx + 25;                                 
              rect.y = ity;                        
              rect.w = 25;                              
              rect.h = 25;
              SDL_RenderFillRect(renderer, &rect);

              SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200);
              rect.x = itx;                                 
              rect.y = ity + 25;                        
              rect.w = 25;                              
              rect.h = 25;
              SDL_RenderFillRect(renderer, &rect);

              SDL_SetRenderDrawColor(renderer, 245, 255, 14, 200);
              rect.x = itx + 25;                                 
              rect.y = ity + 25;                        
              rect.w = 25;                              
              rect.h = 25;
              SDL_RenderFillRect(renderer, &rect);

              SDL_RenderPresent(renderer);
              SDL_Delay(10);
            }else if((switch_prog == -1)&&(it_g%40 == 0)){
              if(lost == 0){
                lost = snake(renderer, window, s, size, apple);
                if((s[0][0] == apple[0])&&(s[0][1] == apple[1])){
                  switch (s[size-1][2]){
                  case 1:
                    s[size][0] = s[size-1][0] - 1;
                    s[size][1] = s[size-1][1];
                    break;
                  case 0:
                    s[size][0] = s[size-1][0] + 1;
                    s[size][1] = s[size-1][1];
                    break;
                  case 2:
                    s[size][0] = s[size-1][0];
                    s[size][1] = s[size-1][1]+1;
                    break;
                  case 3:
                    s[size][0] = s[size-1][0];
                    s[size][1] = s[size-1][1]-1;
                    break;
                  default:
                    break;
                  }
                  s[size][2] = s[size-1][2];
                  size++;
                  printf("add : %d %d %d\n", s[size-1][0], s[size-1][1], s[size-1][2]);
                  pick_apple(apple, s, size);
                }
              }else{
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                rect.x = 0; rect.y = 0;
                rect.w = x; rect.h = y;
                SDL_RenderFillRect(renderer, &rect); 

                // Affichage score snake
                SDL_Color textColor = {255, 255, 255, 255}; 
                sprintf(message, "Score : %d", size);
                SDL_Surface* textSurface = TTF_RenderText_Blended(font, message, textColor);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                int textW = textSurface->w;
                int textH = textSurface->h;
                SDL_FreeSurface(textSurface);
                SDL_Rect dstRect;
                dstRect.x = (x - textW) / 2;
                dstRect.y = (y - textH) / 2;
                dstRect.w = textW;
                dstRect.h = textH;
                SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
              }
              SDL_RenderPresent(renderer);
              SDL_Delay(200);
            }
            it_g ++;
        }

       /* on referme proprement la SDL */
       end_sdl(1, "Normal ending", window, renderer);
       return EXIT_SUCCESS;
     }