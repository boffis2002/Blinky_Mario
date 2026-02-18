#include "raylib/include/raylib.h"

typedef struct {
    Vector2 pos;
    Vector2 vel;
    bool onGround;
    Rectangle collider; 
} Player;
typedef struct {
    Vector2 pos;
    bool enemy;
    Rectangle collider;
    char image[16];
} Obj;