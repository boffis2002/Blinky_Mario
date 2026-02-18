#include "raylib/include/raylib.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>
Obj * makeObj(Vector2 pos,bool enemy,Rectangle collider,char image[16]){
    Obj * o=malloc(sizeof(Obj));
    o->pos=pos;
    o->collider = collider;
    o->enemy = enemy;
    strncpy(o->image,image,16);
    return o;
}
Texture2D * handleTextures(char name[16]){
    char path[31]="./images/";
    strcat(path,name);
    strcat(path,".png\0");
    Image image = LoadImage(path); 
    Texture2D * t = malloc(sizeof(Texture2D));
    *t=LoadTextureFromImage(image);      
    UnloadImage(image);
    return t;
}