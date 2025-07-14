CC = gcc
CFLAGS = -Wall -MMD -I./src

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/partition/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

LIB = $(BUILD_DIR)/libpartition.a

all: $(BUILD_DIR)/partition $(LIB)

# Création du dossier objet
$(BUILD_DIR)/partition:
	mkdir -p $@

# Compilation des .c en .o dans build/partition/
$(BUILD_DIR)/partition/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/partition
	$(CC) $(CFLAGS) -c $< -o $@

# Construction de la bibliothèque statique
$(LIB): $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR)

# Inclusion des dépendances pour recompilation si .h changé
-include $(DEPS)
