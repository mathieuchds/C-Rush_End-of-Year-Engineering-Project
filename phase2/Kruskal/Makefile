CC = gcc
CFLAGS = -Wall -MMD -I./src -I../partition/src

SRC_DIR = src
PARTITION_SRC_DIR = ../partition/src
BUILD_DIR = build

KRUSKAL_SRCS = $(wildcard $(SRC_DIR)/*.c)
PARTITION_SRCS = $(wildcard $(PARTITION_SRC_DIR)/*.c)

# Objets dans des sous-dossiers du build
KRUSKAL_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/kruskal/%.o,$(KRUSKAL_SRCS))
PARTITION_OBJS = $(patsubst $(PARTITION_SRC_DIR)/%.c,$(BUILD_DIR)/partition/%.o,$(PARTITION_SRCS))

OBJS = $(KRUSKAL_OBJS) $(PARTITION_OBJS)
DEPS = $(OBJS:.o=.d)

LIB = $(BUILD_DIR)/libkruskal.a

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $@ $^

# Création des dossiers nécessaires
$(BUILD_DIR)/kruskal:
	mkdir -p $@

$(BUILD_DIR)/partition:
	mkdir -p $@

# Compilation des .c → .o dans les bons sous-dossiers
$(BUILD_DIR)/kruskal/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/kruskal
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/partition/%.o: $(PARTITION_SRC_DIR)/%.c | $(BUILD_DIR)/partition
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# Inclusion des .d pour recompilation automatique si .h changé
-include $(DEPS)
