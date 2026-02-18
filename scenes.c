#include "raylib/include/raylib.h"
#include "utils.c"
#include <stdlib.h>

int makeMenu(const int screenWidth,const int screenHeight,int actual,int menu){
    int click_counter=actual;
    int exit=0;
    if( IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_UP)) click_counter++;
    DrawRectangle( screenWidth/2-200, screenHeight/2-100, 400,  200, (Color){ 230, 41, 55, 100 });
    if(menu==2) DrawText("YOU DIED", 400, 260, 40, BLACK);
    if(click_counter%2==0){
        DrawText("Quit <--", 300, 220, 20, YELLOW);
        if(menu==1)DrawText("Start", 300, 320, 20, BLACK);
        else DrawText("Retry", 300, 320, 20, BLACK);
        exit=1;
    }
    else{
        DrawText("Quit", 300, 220, 20, BLACK);
        if(menu==1)DrawText("Start <--", 300, 320, 20, YELLOW);
        else DrawText("Retry <--", 300, 320, 20, YELLOW);
        exit=2;
    }
    if( IsKeyPressed(KEY_ENTER)) return exit;
    return 0;
}
int makeObstacles(Obj obstacles[],int level){
    switch(level){
        case 1:
            Obj * o1=makeObj((Vector2){600, 370},false,(Rectangle){o1->pos.x, o1->pos.y, 180, 20},"brick.png");
            Obj * o2=makeObj((Vector2){300, 370},false,(Rectangle){o2->pos.x, o2->pos.y, 180, 20},"brick.png");
            Obj * o3=makeObj((Vector2){950, 370},false,(Rectangle){o3->pos.x, o3->pos.y, 180, 20},"brick.png");
            Obj * o4=makeObj((Vector2){600, 470},true,(Rectangle){o4->pos.x, o4->pos.y, 40, 40},"mushroom.png");
            Obj * o5=makeObj((Vector2){800, 470},true,(Rectangle){o5->pos.x, o5->pos.y, 40, 40},"mushroom.png");
            obstacles[0]=*o1;
            obstacles[1]=*o2;
            obstacles[2]=*o3;
            obstacles[3]=*o4;
            obstacles[4]=*o5;
            return 5;
        break;
    }

    return -1;
}