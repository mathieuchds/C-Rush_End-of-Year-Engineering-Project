CC = gcc
CFLAGS = -Wall -MMD -I./src -I../partition/src -I../Kruskal/src -I../sdd -I../calcul_chemin/src

SRC = src/Moteur_labyrinthe.c
BUILD_DIR = build
OBJ = $(BUILD_DIR)/Moteur_labyrinthe.o
DEP = $(OBJ:.o=.d)
LIB = $(BUILD_DIR)/libmoteur_labyrinthe.a

all: $(BUILD_DIR) $(LIB)

$(BUILD_DIR):
	mkdir -p $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR)

# Inclusion automatique des dépendances
-include $(DEP)
