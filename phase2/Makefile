# Compilateur et options
CC = gcc
CFLAGS = -Wall -g -MMD \
	-I./structure/src \
	-I./partition/src \
	-I./Kruskal/src \
	-I./Moteur_labyrinthe/src \
	-I./calcul_chemin/src \
	-I./graphique/src \
	-I./SDL_menu/src \
	$(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lm -lSDL2_ttf -lSDL2_mixer

# Dossier build pour l'exécutable principal
BUILD_DIR = build
MAIN_OBJ = $(BUILD_DIR)/main.o
DEPS = $(MAIN_OBJ:.o=.d)
EXEC = $(BUILD_DIR)/main

# Bibliothèques statiques générées par les sous-Makefiles
STRUCTURE_LIB = structure/build/libstructure.a
PARTITION_LIB = partition/build/libpartition.a
KRUSKAL_LIB = Kruskal/build/libkruskal.a
MOTEUR_LIB = Moteur_labyrinthe/build/libmoteur_labyrinthe.a
CALCUL_LIB = calcul_chemin/build/libcalcul_chemin.a
GRAPH_LIB = graphique/build/libgraphique.a
SDL_MENU_LIB = SDL_menu/build/libSDL_menu.a

# Liste des bibliothèques à linker (dans l'ordre)
LIBS = $(PARTITION_LIB) $(KRUSKAL_LIB) $(MOTEUR_LIB) $(CALCUL_LIB) $(GRAPH_LIB) $(STRUCTURE_LIB) $(SDL_MENU_LIB)

# Cible principale
all: $(BUILD_DIR) libs $(EXEC)

# Création dossier build
$(BUILD_DIR):
	mkdir -p $@

# Appel des sous-make pour générer les libs
.PHONY: libs
libs:
	$(MAKE) -C structure
	$(MAKE) -C partition
	$(MAKE) -C Kruskal
	$(MAKE) -C Moteur_labyrinthe
	$(MAKE) -C calcul_chemin
	$(MAKE) -C graphique
	$(MAKE) -C SDL_menu
# Compilation de main.c
$(MAIN_OBJ): main.c $(LIBS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link final de l'exécutable
$(EXEC): $(MAIN_OBJ) $(LIBS)
	$(CC) -o $@ $(MAIN_OBJ) $(LIBS) $(LDFLAGS)

# Nettoyage
.PHONY: clean
clean:
	$(MAKE) -C structure clean
	$(MAKE) -C partition clean
	$(MAKE) -C Kruskal clean
	$(MAKE) -C Moteur_labyrinthe clean
	$(MAKE) -C calcul_chemin clean
	$(MAKE) -C graphique clean
	$(MAKE) -C SDL_menu clean
	rm -rf $(BUILD_DIR)

# Reconstruction complète
.PHONY: rebuild
rebuild: clean all

# Inclusion des dépendances
-include $(DEPS)
