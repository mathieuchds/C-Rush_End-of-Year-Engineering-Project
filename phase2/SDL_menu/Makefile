CC = gcc
CFLAGS = -Wall -MMD -I./src

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/SDL_menu/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

LIB = $(BUILD_DIR)/libSDL_menu.a
all: $(BUILD_DIR)/SDL_menu $(LIB)

# Création du dossier objet
$(BUILD_DIR)/SDL_menu:
	mkdir -p $@

# Compilation des .c en .o dans build/SDL_menu/
$(BUILD_DIR)/SDL_menu/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/SDL_menu
	$(CC) $(CFLAGS) -c $< -o $@

# Construction de la bibliothèque statique
$(LIB): $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR)

# Inclusion des dépendances pour recompilation si .h changé
-include $(DEPS)
