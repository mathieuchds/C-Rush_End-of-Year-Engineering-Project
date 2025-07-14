CC = gcc
CFLAGS = -Wall -g -MMD -I./src -I../structure/src -I../partition/src -I../Kruskal/src -I../Moteur_labyrinthe/src

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/calcul

SRC = $(SRC_DIR)/calcul_chemin.c
OBJ = $(OBJ_DIR)/calcul_chemin.o
DEP = $(OBJ:.o=.d)
LIB = $(BUILD_DIR)/libcalcul_chemin.a

all: $(OBJ_DIR) $(LIB)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ): $(SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR)

# Inclure les dépendances générées par -MMD
-include $(DEP)
