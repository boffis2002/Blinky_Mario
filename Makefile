TARGET     = BlinkyMario
BUILD_DIR  = build
SOURCES    = main.c

CC         = gcc


CFLAGS     = -Wall -Wextra -std=c11 -O2


RAYLIB_PATH   = ./raylib
CFLAGS       += -I$(RAYLIB_PATH)/include
LDFLAGS       = -L$(RAYLIB_PATH)/lib -lraylib


LDFLAGS      += -framework CoreVideo
LDFLAGS      += -framework IOKit
LDFLAGS      += -framework Cocoa
LDFLAGS      += -framework GLUT
LDFLAGS      += -framework OpenGL



all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean