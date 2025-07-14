#include <stdio.h>
#include "draw_maze.h"
#include "calcul_chemin.h"
#include "Moteur_labyrinthe.h"
#include "end.h"
#include <SDL2/SDL_mixer.h>

int main(int argc, char** argv){

    // Variables permanentes

    (void)argc;
    (void)argv;
    int graine = time(NULL);
    srand(graine);
    FILE *debug_file = fopen("debug_graine.txt", "w");
    if (debug_file != NULL) {
        fprintf(debug_file, "Graine utilisée : %d\n", graine);
        fclose(debug_file);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de debug.\n");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
    }

    Mix_Music* musique = Mix_LoadMUS("./son/musique.wav");
    if (!musique) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
    }
    if (musique) {
        Mix_VolumeMusic(40);
        Mix_PlayMusic(musique, -1);
    }

    Mix_Chunk * click = Mix_LoadWAV("./son/click.wav");
    if (!click) {
        printf("Erreur chargement click : %s\n", Mix_GetError());
        
    }

    Mix_Music* chill = Mix_LoadMUS("./son/combat.wav");
    if (!chill) {
        printf("Erreur chargement chill : %s\n", Mix_GetError());
    }

    Mix_Music* tungtung = Mix_LoadMUS("./son/tutut.wav");
    if (!tungtung) {
        printf("Erreur chargement tungtung : %s\n", Mix_GetError());
      
    }

    Mix_Chunk * pas = Mix_LoadWAV("./son/pas.wav");
    if (!pas) {
        printf("Erreur chargement pas : %s\n", Mix_GetError());
      
    }

     //affiche_tab_construction(l) ;
 

   // labyrinthe_textuel(l);
   // S* s = BFS(l, 0);
   // chemin_plus_court* c= chemin_plus_court_bfs(l, d, a);
    //afficher_labyrinthe_avec_chemin(c);
    //affiche_tab_poids(l);

    //affiche_boutons(l);

    //S* s = BFS(l, 0);
    //chemin_plus_court* c= chemin_plus_court_bfs(l, d, a);
    //afficher_labyrinthe_avec_chemin(c);

   // poids_aleatoire(l);
    // chemin_plus_court* c2 = chemin_plus_court_dijkstra(l,d, a);
    //  afficher_labyrinthe_avec_chemin_dijkstra(c2);
    // chemin_plus_court* c3 = chemin_plus_court_A_etoiles(l, d, a, heuristique_euclidienne);
    //  afficher_labyrinthe_avec_chemin_A_etoiles (c3);
    // chemin_plus_court* c4 = chemin_plus_court_A_etoiles(l, d, a, heuristique_tchebychev);
    // afficher_labyrinthe_avec_chemin_A_etoiles (c4);
    // chemin_plus_court * c5 = chemin_plus_court_A_etoiles(l, d, a, heuristique_manhattan);
    //  afficher_labyrinthe_avec_chemin_A_etoiles(c5);

    
    
    /*for(int i=0;i<=c->taille_chemin;i++){
        printf("%d ", c->chemin[i]);
    }
    printf("\n");*/
    //int depart[1] = {0}; 
    //int arrivee[2] = {8,30};

    //affiche_distance(l, arrivee,  1);
    

  

    //boucle_affichage_prochaine_case_vm(l, vm, 0, arrivee, 1,0);
   // int * noeuds_visite= chemin_destination_inconnue(l, lab, 0, a);
    //afficher_noeuds_visites(noeuds_visite);

    //afficher_tableau_dist(dist, l->nb_ligne, l->nb_colonne);
    //labyrinthe *explore = malloc(sizeof(labyrinthe));
     //parcours_chemin *testdist = destination_minisante_destination_connue(l, explore, 0, 30);
    //afficher_parcours_chemin(testdist);
   // afficher_chemin_dans_labyrinthe(l, testdist);
   //void affiche_distance_connue(labyrinthe *lab, int *distance_connue)
   // affiche_tab_construction(l) ;
    //boucle_affichage_prochaine_case_inconnue_vm(l, vm, 0, l->boutons,0);
    // Init pour la SDL
    int program_on = 1;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    maze * m = NULL;
    SDL_Event event;       
    SDL_bool event_utile = SDL_FALSE;
    entity_name tab_e[22] = {SLIME1, SLIME2, SLIME3,
                            SLIME1CHILL, SLIME2CHILL, SLIME3CHILL,
                            SLIME1RUN, SLIME2RUN, SLIME3RUN,
                            SLIME1LIGHT, SLIME2LIGHT, SLIME3LIGHT,
                            MONSTER_ICON1, MONSTER_ICON2, MONSTER_WALK,
                            SLIME1ATTACK, SLIME2ATTACK, SLIME3ATTACK,
                            SLIME1DEATH, SLIME2DEATH, SLIME3DEATH, 
                            MONSTER_ATTACK}; 
    animation_page ** all_anim = NULL;
    init_sdl(&renderer, &window);
    entity * player = NULL;
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("textures/DungeonFont.ttf", 50);
    TTF_Font *font2 = TTF_OpenFont("textures/Karma Suture.otf", 50);
    SDL_Texture * light_bulb = load_texture_from_image("textures/light_bulb.png", window, renderer);
    SDL_Texture * button_icon = load_texture_from_image("textures/button_icon.png", window, renderer);
    SDL_Texture * slime_trace[4] ;
    slime_trace[0] = load_texture_from_image("textures/trace_slime1.png", window, renderer);
    slime_trace[1] = load_texture_from_image("textures/trace_slime2.png", window, renderer);
    slime_trace[2] = load_texture_from_image("textures/trace_slime3.png", window, renderer);
    slime_trace[3] = load_texture_from_image("textures/trace_slime4.png", window, renderer);

    SDL_Texture * monster_trace[4] ;
    monster_trace[0] = load_texture_from_image("textures/trace_monster1.png", window, renderer);
    monster_trace[1] = load_texture_from_image("textures/trace_monster2.png", window, renderer);
    monster_trace[2] = load_texture_from_image("textures/trace_monster3.png", window, renderer);
    monster_trace[3] = load_texture_from_image("textures/trace_monster4.png", window, renderer);
    entity * monster;
    
    int w_x; int w_y;
    SDL_GetWindowSize(window,&w_x,&w_y);
    SDL_Rect window_dimensions = {0}; 
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    SDL_Texture * tab_texture_anim[10];
    printf("avant init\n");
    init_anim_tab("textures/grayscreen.jpg", renderer, tab_texture_anim );
    printf("apres init\n");


    /*printf("init lvl work\n");
    printf("d1 %d\n", all_anim[21]->duree[1]);
    printf("d2 %d\n", monster->feuille_animation4->duree[2]);
    printf("d3 %d\n", monster->feuille_animation4->texture == NULL);*/

    /* Chargement des polices*/
    char * jouer = "P l a y";
    char * bouton2 = "M o d e";
    char * chose_slime = "C h o o s e  y o u r  c h a r a c t e r";
    char * n_slime1 = "B o b b y ";
    char * n_slime2 = "R i c k y ";
    char * n_slime3 = "J o h n n y";
    char * done = "D o n e";
    char * next = "N e x t";
    char * suiv = "B a c k";

    SDL_Texture * police_texte = chargement_police(window, renderer, jouer);
    SDL_Texture * police_texte2 = chargement_police(window, renderer, bouton2);
    SDL_Texture * p_slime = chargement_police(window, renderer, chose_slime);
    SDL_Texture * nom_slime1 = chargement_police(window, renderer, n_slime1);
    SDL_Texture * nom_slime2 = chargement_police(window, renderer, n_slime2);
    SDL_Texture * nom_slime3 = chargement_police(window, renderer, n_slime3);
    SDL_Texture * done_modif= chargement_police(window, renderer, done);
    SDL_Texture * text_next= chargement_police(window,renderer, next);
    SDL_Texture * text_suiv= chargement_police(window,renderer, suiv);


    SDL_Texture ** text = malloc(50*sizeof(SDL_Texture *));
    text= charge_texture(text, window, renderer);

    SDL_Rect source = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 
    SDL_QueryTexture(text[0], NULL, NULL,  &source.w, &source.h); 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    //différents paramètres
    int scroll4=0;
    int scroll3=0;
    int scroll2=0;
    int scroll1=0;
    int scroll_sol=0;
    int i=0;
    int ite=0;
    int slime_i=0;
    int map_i=0;
    int page_i=0;
    int diff_i=0;
    int nb_density=0;
    int switch_i=0;
    int button_i=0;
    int * int_bouton=malloc(11*sizeof(int));
    int slime_clic=0;
    int b_param=0;
    int b_personnalisation=0;
    int bouton_accueil=1;
    int fin=1;
    int b_switch=0;
    int b_density=0;
    int b_button=0;

    //int custom=0;
    //int bouton_done=0;


    int w= window_dimensions.w/3;
    int w_param=window_dimensions.w/16;
    int h_param=window_dimensions.h/12;

    SDL_Texture ** slime=malloc(3*sizeof(SDL_Texture*));
    slime =charge_slime(slime, window, renderer);
    SDL_Texture ** map=malloc(2*sizeof(SDL_Texture*));
    map =charger_map(map, window, renderer);
    SDL_Texture ** fleche=malloc(4*sizeof(SDL_Texture*));
    fleche =charger_flèches(fleche, window, renderer);

    SDL_Texture ** t_diff=malloc(4*sizeof(SDL_Texture *));
    char * facile = "E a s y";
    char* moyen = "M e d i u m";
    char * difficile = "D i f f i c u l t";
    char * personnalise = "C u s t o m";
    t_diff[0]= chargement_police(window, renderer, facile);
    t_diff[1]= chargement_police(window, renderer, moyen);
    t_diff[2]= chargement_police(window, renderer, difficile);
    t_diff[3]= chargement_police(window, renderer, personnalise);

    char * nb_switch_char= "N u m b e r  o f  s w i t c h :";
    SDL_Texture * t_nb_switch= chargement_police(window, renderer, nb_switch_char);
    char * nb_bouton_char= "N u m b e r  o f  b u t t o n s :";
    SDL_Texture * t_nb_button=chargement_police(window, renderer, nb_bouton_char);
    char * density_char = "D e n s i t y  o f :";
    SDL_Texture * t_density = chargement_police(window, renderer, density_char);
    char * char_density = malloc(sizeof(2*sizeof(char)));
    SDL_Rect state[8];
    frame(slime[slime_i], window, 8,4,state);

    //coord par défaut des boutons
    coord play, play2, param, perso,coord_sol, logo, slime1, slime2, slime3, perso_b, f_droit, f_gauche, police_play, 
    police_play2, police_slime, p_nom_slime1, p_nom_slime2, p_nom_slime3, coord_next, coord_suiv, p_next, p_suiv;
    maj_coord(&play, &play2, &param, &perso, &coord_sol, &logo, &slime1, &slime2, &slime3, &perso_b, &f_droit, &f_gauche,&police_play, 
        &police_play2 , &police_slime, &p_nom_slime1, &p_nom_slime2, &p_nom_slime3, &coord_next, &coord_suiv, &p_next, &p_suiv, window_dimensions);
    // Init pour la SDL
    
 

    SDL_Rect * tab_spawns_rect[4];
    SDL_Texture * tab_spawns_textures[4];
    init_spawns_tab(renderer, window, tab_spawns_rect, tab_spawns_textures);
    
    SDL_Texture * tmp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w_x, w_y);

    
    /*SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // fond gris clair pour bien voir le halo
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, m->button_texture, NULL, NULL);*/

    // Rendu de la fog au centre de l'écran

   /* SDL_Rect dst_rect = {
        .x = (m->longueur*m->dim_case - light_radius) / 2,  
        .y = (m->hauteur*m->dim_case - light_radius) / 2,
        .w = m->longueur*m->dim_case,
        .h = m->hauteur*m->dim_case
    };

    SDL_RenderCopy(renderer, fog_texture, NULL, NULL);

    // Affichage
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    */


    
    /* boucle test
     while(1){
        d = a ; a=rand()%(10*15-1);
        c5 = chemin_plus_court_A_etoiles(l, d, a, heuristique_manhattan);
        auto_movement_with_path(player, c5->chemin, m, renderer, 7, window, a, d);
    } 
    d = a ; a=rand()%(10*15-1);
    c5 = chemin_plus_court_A_etoiles(l, d, a, heuristique_manhattan);
    auto_movement_with_path(player, c5->chemin, m, renderer, 7, window, a, d);
        */

    // Traitement
    //draw_maze_BFS(renderer, w_x, w_y, s->deja_vu,m, c->chemin, 0, 23, font);
    //draw_maze_Dijkstra(renderer, w_x, w_y, c5->noeuds_visites,m, c5->chemin, d, a, font);
    //int taille[2]; taille[1]=m->longueur; taille[0]=m->hauteur;
    //draw_maze(renderer, w_x, w_y, m->construction, m->nb_noeud, taille);
    
    int it = 0;
    int freq_anim = 0;
    int light_on = 1;
    int nb_switch = 5;
    int nb_density2 = 70;
    int switching_light = 0;
    int button_pressed = 0;
    int exit_open = 0;
    int win = 0; // -1 perdu, 1 gagné, 0 pas fini
    int duree_anim = 0;
    int tab_path[20][2];
    for(int i =0;i<20;i++){
        tab_path[i][0] = -1;
        tab_path[i][1] = -1;
    }
    int taille_tab = 20;

    int tab_path2[20][2];
    for(int i =0;i<20;i++){
        tab_path2[i][0] = -1;
        tab_path2[i][1] = -1;
    }
    int taille_tab2 = 20;
    int curseur_tab_path = 0;
    int curseur_tab_path2 = 0;
    int count_monster_decision=0;
    int mode_hunt = 1;
    int next_step = 0;
    unsigned long int count_appel_dest_connu = 0;
    int count_light_couldown = 0;
    int animation_p_attack = -1;
    int animation_m_attack = -1;
    int etat_jeu=0;
    int nb_button_max=0;
    int is_monster_killed = 0;

    labyrinthe * l=NULL; 
    point_interet * spawns= NULL;
    vision_monstre * vm=NULL ;
    labyrinthe *lab = malloc(sizeof(labyrinthe));
    SDL_Texture * halo2;
    SDL_Texture * halo;
    int light_radius;
    while (program_on) {
        switch (etat_jeu){
            case 0: // Menu principal
                event_utile = SDL_FALSE;
                while(!event_utile && SDL_PollEvent(&event)) { 
                    switch (event.type) {                     
                        case SDL_QUIT:                                
                            program_on = SDL_FALSE; 
                            event_utile = SDL_TRUE;
                            break;
                        case SDL_KEYDOWN:
                            if (event.key.keysym.sym == SDLK_q) {
                                program_on = SDL_FALSE;
                                event_utile = SDL_TRUE;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            int_bouton=bouleen_bouton(int_bouton, play, play2, param,perso, slime1, slime2, slime3, f_droit, f_gauche, coord_next, coord_suiv);
                        //play 1
                        if ((int_bouton[0] ==1) && SDL_BUTTON(SDL_BUTTON_LEFT) && (slime_clic==0) && (b_personnalisation==0)&& (b_param==0)) { 
                            Mix_PlayChannel(0, click,0);
                            if (fin ==1){
                                page_i=0;
                                fin=0;
                            }
                            button_pressed=0;
                            etat_jeu=1;
                            switch(diff_i){
                                case 0: //facile
                                    nb_button_max=5;
                                    nb_density2=70;
                                    nb_switch=15;
                                    break;
                                case 1: //moyen
                                    nb_button_max=7;
                                    nb_density2=45;
                                    nb_switch=10;
                                    break;
                                case 2: //difficile
                                    nb_button_max=10;
                                    nb_density2=10;
                                    nb_switch=5;
                                    break;
                                case 3: //personnalise
                                    nb_button_max=button_i;
                                    nb_switch = switch_i;
                                    nb_density2=nb_density;
                                    break;
                                default:
                                    nb_button_max=5;
                                    nb_density2=70;
                                    nb_switch=15;
                                    break;
                            }
                            Mix_PlayMusic(chill, -1);
                            algorithme_kruskal_densite(10,20, nb_density2); //Fixe densite
                            if (l != NULL) {
                                free_labyrinthe(l);
                            }
                            l = init_labyrinthe(10,20,nb_button_max); //Fixe nb boutons
                            calcul_construction(l);
                    
                            generer_boutons_ecartes(l);
                            if (spawns != NULL) {
                                free(spawns);
                            }
                            spawns = malloc(sizeof(point_interet)); 
                            init_points_interet(l, spawns);
                            if (map_i==1){
                                poids_logique_centrique(l);
                            }
                            else{
                                poids_classique(l); 
                            }
                          
                            init_level(renderer, window, &m, l, tab_e, &all_anim, &player, slime_i, 1, 22, l->poids_cases, l->boutons, spawns, &monster); //Choisie le slime
                            
                            lab->nb_ligne = 0;
                            lab->nb_colonne = 0;
                            lab->construction = NULL;
                            lab->poids_cases = NULL;
                            if (lab->construction == NULL || lab->poids_cases == NULL) {
                                lab->nb_ligne = l->nb_ligne;
                                lab->nb_colonne = l->nb_colonne;
                                lab->construction = (int*)malloc(l->nb_ligne * l->nb_colonne * sizeof(int));
                                lab->poids_cases = (int*)malloc(l->nb_ligne * l->nb_colonne * sizeof(int));
                                for (int i = 0; i < l->nb_ligne * l->nb_colonne; i++) {
                                    lab->construction[i] = 0;
                                    lab->poids_cases[i] = 1;
                                }
                            }
                            vm = init_vision_monstre(lab);
                            light_radius = m->dim_case * 3;
                            halo = create_halo_texture(renderer, light_radius);
                            halo2 = create_halo_texture(renderer, m->dim_case);
                            count_monster_decision = m->dim_case + 3;
                            win = 0;
                            exit_open = 0;
                            for(int i =0;i<20;i++){
                                tab_path[i][0] = -1;
                                tab_path[i][1] = -1;
                            }
                            taille_tab = 20;

                            tab_path2[20][2];
                            for(int i =0;i<20;i++){
                                tab_path2[i][0] = -1;
                                tab_path2[i][1] = -1;
                            }
                            taille_tab2 = 20;
                            curseur_tab_path = 0;
                            curseur_tab_path2 = 0;

                            
                        }
                        //play2
                        else if ((int_bouton[1] ==1) && SDL_BUTTON(SDL_BUTTON_LEFT) && (slime_clic==0) && (b_param==0)) { 
                            printf("bouton 2\n");
                            b_switch=0;
                            b_button=0;
                            b_density=0;
                            Mix_PlayChannel(0, click,0);
                            bouton_accueil=activer_int(bouton_accueil);
                            if (b_personnalisation==0) {
                                b_personnalisation=1;
                            }
                            else {
                                b_personnalisation=0;
                            }
                            page_i=0;
                            //diff_i=0;

                        }
                        //règles
                        else if (((int_bouton[2]==1)|| (int_bouton[1]==1) ) && SDL_BUTTON(SDL_BUTTON_LEFT)&& (slime_clic==0)&& (b_personnalisation==0) ) {
                            printf("param\n");
                            Mix_PlayChannel(0, click,0);
                            bouton_accueil=activer_int(bouton_accueil);
                            b_param=activer_int(b_param);
                            
                        } //slime
                        //choix du slime
                        else if ( (int_bouton[1]|| (int_bouton[3]==1) ) && SDL_BUTTON(SDL_BUTTON_LEFT) && (b_param==0)&& (b_personnalisation==0)) {
                            printf("slime\n");
                            Mix_PlayChannel(0, click,0);
                            bouton_accueil=activer_int(bouton_accueil);
                            if (slime_clic ==0 ) {
                                slime_clic=1;
                            }
                            else {
                                slime_clic=0;
                            }
                        }
                        //slime1
                        else if ((int_bouton[4]==1) && SDL_BUTTON(SDL_BUTTON_LEFT)&& (slime_clic==1) ) {
                            printf("slime 1\n");
                            Mix_PlayChannel(0, click,0);
                            slime_i=0;
                        }
                        //slime2
                        else if ((int_bouton[5]==1) && SDL_BUTTON(SDL_BUTTON_LEFT)&& (slime_clic==1) ) {
                            printf("slime 2\n");
                            Mix_PlayChannel(0, click,0);
                            slime_i=1;
                        }
                        //slime3
                        else if ((int_bouton[6]==1) && SDL_BUTTON(SDL_BUTTON_LEFT)&& (slime_clic==1) ) {
                            printf("slime 3\n");
                            Mix_PlayChannel(0, click,0);
                            slime_i=2;
                        }
                        //choix de la map -> flèches gauche et droite
                        else if ((int_bouton[7]==1) && SDL_BUTTON(SDL_BUTTON_LEFT) ) {
                            Mix_PlayChannel(0, click,0);
                            if (page_i==0){
                                map_i=(map_i+1)%2;
                            }
                            else if (page_i==1){
                                diff_i=(diff_i+1)%4;
                            }
                            else if (page_i==2) {
                                switch_i=(switch_i+1)%20;
                                b_switch=1;
                            }
                            else if (page_i==3){
                                button_i=(button_i+1)%11;
                                b_button=1;
                            }
                            else if (page_i==4) {
                                nb_density=(nb_density+1)%100;
                                b_density=1;
                            }
                            

                        }
                        else if ((int_bouton[8]==1) && SDL_BUTTON(SDL_BUTTON_LEFT)  ) {
                            Mix_PlayChannel(0, click,0);
                            if (page_i==0){
                                map_i=(map_i+1)%2;
                            }
                            else if (page_i==1){
                                diff_i=(diff_i+3)%4;
                            }
                            else if (page_i==2) {
                                switch_i=(switch_i+20)%21;
                                b_switch=1;
                            }
                            else if (page_i==3){
                                button_i=(button_i+10)%11;
                                b_button=1;
                            }
                            else if (page_i==4) {
                                nb_density=(nb_density+100)%101;
                                b_density=1;
                            }
                        }
                        // flèches gauches et droites
                        else if ((int_bouton[9]==1) && SDL_BUTTON(SDL_BUTTON_LEFT) && (b_personnalisation==1) && ( (page_i%5==0) || (page_i%5==1)|| (diff_i%4==3) ) ) {
                            printf("next\n");
                            Mix_PlayChannel(0, click,0);
                            page_i=(page_i+1)%5;
                            if (page_i==2){
                                b_density=0;
                                b_button=0;
                            }
                            else if (page_i==3){
                                b_density=0;
                                b_switch=0;
                            }
                            else if (page_i==4){
                                b_switch=0;
                                b_button=0;
                            }
                            else{
                                b_switch=0;
                                b_button=0;
                                b_density=0;
                            }
                        }
                        else if ((int_bouton[10]==1) && SDL_BUTTON(SDL_BUTTON_LEFT)&& (b_personnalisation==1) && (page_i%5!=0) ) {
                            page_i=(page_i+4)%5;
                            Mix_PlayChannel(0, click,0);
                            printf("back\n");
                            if (page_i==2){
                                b_density=0;
                                b_button=0;
                            }
                            else if (page_i==3){
                                b_density=0;
                                b_switch=0;
                            }
                            else if (page_i==4){
                                b_switch=0;
                                b_button=0;
                            }
                            else{
                                b_switch=0;
                                b_button=0;
                                b_density=0;
                            }
                        }
                        
                        event_utile = SDL_TRUE;
                        break;
                    default :
                        break;
                    }
                }
                SDL_RenderClear(renderer);
                //mise à jour des paramètres dans le cas du plein écran
                SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
                maj_coord(&play, &play2, &param, &perso, &coord_sol, &logo, &slime1, &slime2,&slime3, &perso_b, &f_droit, &f_gauche,&police_play, 
                    &police_play2, &police_slime, &p_nom_slime1, &p_nom_slime2, &p_nom_slime3, &coord_next, &coord_suiv,&p_next, &p_suiv, window_dimensions);
                play.w=w;
                play2.w=w;
                param.w=w_param;
                param.h=h_param;
                perso.w=w_param;
                perso.h=h_param;
                int_bouton=bouleen_bouton(int_bouton, play, play2, param,perso,slime1, slime2, slime3, f_droit, f_gauche, coord_next, coord_suiv);

                //parallax:
                parallax(text, window, renderer, scroll1, scroll2, scroll3, scroll4, scroll_sol, coord_sol);
                fond_fixe_xy(text[7], window, renderer, logo); //logo
                
                //boutons
                hover_menu_principal(int_bouton, text, window, renderer, play, play2, param);
                bouton_règles(b_param, window_dimensions,window, renderer, text[17]); 
                menu_perso(slime_clic, window_dimensions,window, renderer, text[17]);
                
                
                //slime
                hover_bouton(window, renderer, text[12], text[13], int_bouton[3], perso);
                afficher(slime[slime_i], window, renderer, ite%8, perso, &state);
                
                //fenêtre de choix de personnages
                bouton_choix_perso(window, renderer,text[15], text[16], slime_clic, slime1, slime2, slime3);
                //affichage des boutons:
                if (slime_clic==1){
                    afficher(slime[0], window, renderer,  ite%8, slime1, &state);
                    afficher(slime[1], window, renderer,  ite%8, slime2, &state);
                    afficher(slime[2], window, renderer,  ite%8, slime3, &state);
                }

                //fenêtre personnalisation des paramètres
                page_de_base(window, renderer, window_dimensions, b_personnalisation, text, play2, coord_next, coord_suiv, int_bouton, page_i, diff_i);

                afficher_pages_custom(window, renderer, window_dimensions, text_next, text_suiv, t_nb_switch, t_nb_button, t_density,t_diff,  fleche,  
                map, p_next,  p_suiv,  f_droit, f_gauche, int_bouton, int_bouton[7],int_bouton[8],  b_personnalisation, page_i, map_i, diff_i);

                //bouton done
                hover_bouton(window, renderer, text[8], text[9], int_bouton[1], play2);


                //textes
                afficher_text(renderer, police_texte, police_play, bouton_accueil);
                afficher_text(renderer, police_texte2, police_play2, bouton_accueil);
                afficher_text(renderer, p_slime, police_slime, slime_clic);
                afficher_text(renderer, nom_slime1, p_nom_slime1, slime_clic );
                afficher_text(renderer, nom_slime2, p_nom_slime2, slime_clic );
                afficher_text(renderer, nom_slime3, p_nom_slime3, slime_clic );
                afficher_text(renderer, done_modif, police_play2, !bouton_accueil);
                
                    
                case_density( window, renderer,window_dimensions, char_density, switch_i, b_switch);
                case_density( window, renderer,window_dimensions, char_density, nb_density, b_density);
                case_density( window, renderer,window_dimensions, char_density, button_i, b_button);


                //gestion des vitesses des différentes textures
                scroll4+=7;
                scroll3+=5;
                scroll2+=3;
                scroll1+=1;
                scroll_sol+=7;
                i++;
                if (i%4==0){
                    ite++;
                }
                // Affichage du rendu
                SDL_RenderPresent(renderer);
                break;
            case 1: // Jeu en cours
            
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    program_on = SDL_FALSE; //quitter le programme
                    break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_q) {
                            program_on = SDL_FALSE; // Quitter le programme si Échap est pressé
                        }else if (event.key.keysym.sym == SDLK_SPACE) {
                            if((nb_switch > 0)&&(!exit_open)&& (light_on!=-1)){
                                light_on *= -1;
                                nb_switch --;
                                switching_light = 200; 
                                Mix_HaltMusic();
                                Mix_PlayMusic(tungtung, -1); 
                            }
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN: //bouton de fin
                        if ((int_bouton[0] ==1) && SDL_BUTTON(SDL_BUTTON_LEFT) && (slime_clic==0)&& (win!=0)) {
                            etat_jeu=0;
                            Mix_PlayChannel(0, click,0);
                            Mix_PlayMusic(musique, -1);
                        }
                        break;
                    default:
                        break;
                    }
                }
                if (count_light_couldown==300){
                    Mix_HaltMusic();
                    Mix_PlayMusic(chill, -1); 
                }

                SDL_RenderClear(renderer);
                if(win != 0){ 
                    page_fin_basique(window, renderer, window_dimensions,text, win, play, police_play);
                }else{

                    SDL_SetRenderTarget(renderer, tmp);
                    SDL_RenderCopy(renderer, m->map, NULL, NULL); // trace le labyrinthe en fond
                    SDL_RenderCopy(renderer, m->button_texture, NULL, NULL); // trace les boutons

                    draw_spawns(renderer, spawns, tab_spawns_textures, tab_spawns_rect, m, exit_open, freq_anim);

                    if((count_monster_decision > m->dim_case/(monster->speed) + 2)||(is_monster_killed == 1)){
                        if(mode_hunt == 1){
                            int arrivee[1] = {player->x + player->y*m->longueur};
                            next_step = prochaine_case_destination_connue_vm(l, vm, monster->x + monster->y*m->longueur, arrivee, 1, count_appel_dest_connu);
                            if(next_step == -1){
                                win = -1;
                            }
                        }else{
                            is_monster_killed = 0;
                            next_step = prochaine_case_destination_inconnue_vm(l, vm, monster->x + monster->y*m->longueur, m->button, count_appel_dest_connu);
                            if(next_step == -1){
                                maj_button_vm(m, renderer, window, monster, &button_pressed);
                                next_step = prochaine_case_destination_inconnue_vm(l, vm, monster->x + monster->y*m->longueur, m->button, count_appel_dest_connu);
                            }
                        }
                        //printf("etape : %d, count :%d, speed %f ratio:%f\n", next_step, count_monster_decision, monster->speed, m->dim_case/(monster->speed));
                        count_monster_decision = 0;
                        count_appel_dest_connu++;
                    }

                    SDL_Rect r1 = {player->x_draw, player->y_draw, m->dim_case*2/3, m->dim_case*2/3};
                    SDL_Rect r2 = {monster->x_draw, monster->y_draw, m->dim_case*2/3, m->dim_case*2/3};
                    if ((SDL_HasIntersection(&r1, &r2)) && mode_hunt == 1) { // pour eviter les bugs sécurité
                        win = -1;
                    }

                    //printf("etape : %d, count :%d, speed %f ratio:%f\n", next_step, count_monster_decision, monster->speed, m->dim_case/(monster->speed));


                    if(!exit_open){ // si on a pas trouvé tout les boutons
                        if(switching_light == 0){
                            smooth_player_movement(player, m, renderer, window, w_x, w_y, it, animation_p_attack, animation_m_attack); // trace le personnage
                        }else{

                            anim_switching_light(switching_light, player, renderer, m);
                            switching_light -= 5;
                            if(switching_light == 5){
                                mode_hunt *= -1;
                            }
                        }
                        
                        if(((light_on == 1)&&(switching_light < 25))||((light_on == -1)&&(switching_light != 0))){
                            render_halo(renderer, halo, player->x_draw + m->dim_case/2, player->y_draw + m->dim_case/2, light_radius);
                            black_fog(renderer, player->x_draw + m->dim_case/2, player->y_draw + m->dim_case/2, light_radius, m->dim_case*m->longueur, m->dim_case*m->hauteur);
                        }else if(((light_on == -1)&&(switching_light < 25))||((light_on == 1)&&(switching_light != 0))){
                            render_halo(renderer, halo2, player->x_draw + m->dim_case/2, player->y_draw + m->dim_case/2, m->dim_case);
                            black_fog(renderer, player->x_draw + m->dim_case/2, player->y_draw + m->dim_case/2, m->dim_case, m->dim_case*m->longueur, m->dim_case*m->hauteur);
                        }
                        manage_player_path(renderer, player, tab_path, &curseur_tab_path, taille_tab, m, light_on, light_radius, slime_trace);
                        manage_monster_path(renderer, monster, tab_path2, &curseur_tab_path2, taille_tab2, m, monster_trace);
                        
                        if(nb_button_max == button_pressed){ // si on a trouvé tout les boutons
                            exit_open = 1;
                            //anim_door();
                        }
                    }else{
                        smooth_player_movement(player, m, renderer, window, w_x, w_y, it, animation_p_attack, animation_m_attack); // trace le personnage
                        if(((it%50 == 0)&&(duree_anim == 0))||((duree_anim < 20)&&(duree_anim != 0))){ 
                            //anim_exit(renderer, "textures/grayscreen.jpg", w_x, w_y, player, duree_anim);
                            SDL_RenderCopy(renderer, tab_texture_anim[duree_anim%5], NULL, NULL);
                            duree_anim ++;
                        }else if(duree_anim == 20){
                            duree_anim =0;
                        }
                    }
                    
                    if(!exit_open){
                        maj_button(m, renderer, window, player, &button_pressed);
                    }else{
                        if((spawns->exit%m->longueur == player->x)&&(spawns->exit/m->longueur == player->y)) { // si on est à la sortie on a fini
                            win = 1;
                            player_anime_fin(renderer,  player, monster, m, spawns, freq_anim, w_x,w_y);
                        }
                    }
                
                    if(win == 0){
                        //printf("coo monstres before: %d %d | %d %d\n", monster->x, monster->y, monster->x_draw, monster->y_draw);
                        monster_icon_movement(renderer, monster, next_step, m, freq_anim, mode_hunt, light_on, light_radius, player, exit_open); // affiche le monstre
                        //printf("coo monstres after: %d %d | %d %d\n", monster->x, monster->y, monster->x_draw, monster->y_draw);
                    }

                    if(mode_hunt == -1){ // gestion attaque
                        player_attack_monster(renderer, player, monster, m, &animation_p_attack, spawns, freq_anim, &is_monster_killed);
                    }

                    if(win == -1){ // animation de mort
                        monster_attack_player(renderer, player, monster, m, spawns, freq_anim, w_x, w_y);
                    }else{
                        SDL_Rect tmp_r = {0, 0, m->dim_case*m->longueur, m->dim_case*m->hauteur};
                        render_focus_centered(renderer, tmp, tmp_r, w_x, w_y); // centre le labyrinthe
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        labyrinthe_ui(renderer, font2, light_bulb, nb_switch, w_x, button_pressed, button_icon, nb_button_max); // affiche l'interface joueur
                        if(count_light_couldown != 0){
                            drawGauge(renderer, count_light_couldown, 250);
                        }
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        
                        if(!exit_open){ // si on a pas trouvé tout les boutons
                            maj_button(m, renderer, window, player, &button_pressed);
                        }else{ // si on les as trouvés
                            if((spawns->exit%m->longueur == player->x)&&(spawns->exit/m->longueur == player->y)) { // si on est à la sortie on a fini
                                win = 1;
                                page_fin_basique(window, renderer, window_dimensions,text, win, play, police_play);
                                
                            }
                        }
                    }
                    
                    // iterateurs du jeu

                    it++;
                    count_monster_decision++;
                    if(it%2 == 0){
                        freq_anim++;
                    }
                    if(light_on == -1){
                        count_light_couldown++;
                    }
                    if(count_light_couldown > 250){
                        light_on = 1;
                        count_light_couldown = 0;
                        mode_hunt *= -1;
                    }
                }
                //printf("coo monstres : %d %d | %d %d\n\n", monster->x, monster->y, monster->x_draw, monster->y_draw);
                // Affichage du rendu

                SDL_RenderPresent(renderer);
                SDL_Delay(50); 
                break;
        
            default:
                break;
        }
    }   

    // Free
    for(int i=0;i<4;i++){
        free(tab_spawns_rect[i]);
        SDL_DestroyTexture(tab_spawns_textures[i]);
    }
    for(int i=0;i<4;i++){
        SDL_DestroyTexture(slime_trace[i]);
        SDL_DestroyTexture(monster_trace[i]);
    }
    SDL_DestroyTexture(m->map);
    SDL_DestroyTexture(tmp);
    SDL_DestroyTexture(halo);
    SDL_DestroyTexture(halo2);
    SDL_DestroyTexture(police_texte);
    Destroy_Texture(text, 19);
    Destroy_Texture(slime, 3);
    SDL_DestroyTexture(police_texte2);
    SDL_DestroyTexture(p_slime);
    SDL_DestroyTexture(police_texte2);
    SDL_DestroyTexture(nom_slime1);
    SDL_DestroyTexture(nom_slime2);
    SDL_DestroyTexture(nom_slime3);
    SDL_DestroyTexture(done_modif);
    SDL_DestroyTexture(text_next);
    SDL_DestroyTexture(text_suiv);
    SDL_DestroyTexture(t_nb_button);
    SDL_DestroyTexture(t_nb_switch);
    SDL_DestroyTexture(t_density);
    
    TTF_CloseFont(font);
    TTF_Quit();
    //end_sdl(1, "Normal ending", window, renderer, NULL, all_anim, 3);
    free_labyrinthe(l);
    free_vision_monstre(vm);
    free_labyrinthe(lab);
    return 1;

}
