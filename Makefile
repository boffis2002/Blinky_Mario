# Makefile per raylib su macOS (con Homebrew)
# Nome eseguibile
TARGET = BlinkyMario

# Cartella build
BUILD_DIR = build

# File sorgente (cambia se hai più .c)
SOURCES = main.c
# SOURCES = $(wildcard *.c)   ← se vuoi compilare tutti i .c automaticamente

# Compilatore
CC = gcc
# CC = clang   ← puoi usare clang se preferisci

CFLAGS = -Wall -Wextra -std=c11 -O2
# Per debug: aggiungi -g -fsanitize=address

# togli o commenta le righe vecchie
# CFLAGS += $(shell brew --prefix raylib)/include
# LDFLAGS = -L$(shell brew --prefix raylib)/lib -lraylib

# metti invece così (corretto con -I e -L)
CFLAGS += -I$(shell brew --prefix raylib)/include
LDFLAGS += -L$(shell brew --prefix raylib)/lib -lraylib

# Framework macOS necessari
LDFLAGS += -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean