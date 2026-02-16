# Makefile per raylib su macOS – versione con raylib locale

TARGET     = BlinkyMario
BUILD_DIR  = build
SOURCES    = main.c
# SOURCES  = $(wildcard *.c)   # se vuoi compilare tutti i .c

CC         = gcc
# CC       = clang           # se preferisci

CFLAGS     = -Wall -Wextra -std=c11 -O2
# Per debug:  CFLAGS += -g -fsanitize=address

# ───────────────────────────────────────────────
# Percorsi locali a raylib (non dipende più da brew)
# ───────────────────────────────────────────────
RAYLIB_PATH   = ./raylib
CFLAGS       += -I$(RAYLIB_PATH)/include
LDFLAGS       = -L$(RAYLIB_PATH)/lib -lraylib

# Framework macOS necessari (sempre richiesti)
LDFLAGS      += -framework CoreVideo
LDFLAGS      += -framework IOKit
LDFLAGS      += -framework Cocoa
LDFLAGS      += -framework GLUT
LDFLAGS      += -framework OpenGL

# Se usi libraylib.a statica → di solito funziona meglio su macOS
# Se invece hai libraylib.dylib → puoi aggiungere:
# LDFLAGS      += -Wl,-rpath,@executable_path/raylib/lib

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean