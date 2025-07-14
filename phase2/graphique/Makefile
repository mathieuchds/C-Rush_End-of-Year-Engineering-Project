CC = gcc
CFLAGS = -Wall -I./src $(shell sdl2-config --cflags) -I../Moteur_labyrinthe/src -I../Kruskal/src -I../partition/src -I../calcul_chemin/src -I../structure/src -MMD
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lm

SRC_DIR = src
BUILD_DIR = build

# Tous les fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Liste des fichiers pour la libgraphique
GRAPH_NAMES = conversion player_movement_graphic texture_management draw_maze convert effects
GRAPH_SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(GRAPH_NAMES)))
GRAPH_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(GRAPH_SRCS:.c=.o)))
LIB_GRAPH = $(BUILD_DIR)/libgraphique.a

# Les autres fichiers .c (ceux qui ne sont pas dans GRAPH_SRCS)
OTHER_SRCS = $(filter-out $(GRAPH_SRCS), $(SRCS))
OTHER_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(OTHER_SRCS:.c=.o)))
LIB_STRUCTURE = $(BUILD_DIR)/libstructure_graphique.a

all: $(BUILD_DIR) $(LIB_STRUCTURE) $(LIB_GRAPH)

$(BUILD_DIR):
	mkdir -p $@

# Compilation générique
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Création des bibliothèques
$(LIB_STRUCTURE): $(OTHER_OBJS)
	ar rcs $@ $^

$(LIB_GRAPH): $(GRAPH_OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR)/*.o $(LIB_STRUCTURE) $(LIB_GRAPH)
