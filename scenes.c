#include "raylib.h"

int makeStopMenu(const int screenWidth,const int screenHeight,int actual){
    int click_counter=actual;
    int exit=0;
    if( IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_UP)) click_counter++;
    DrawRectangle( screenWidth/2-200, screenHeight/2-100, 400,  200, (Color){ 230, 41, 55, 100 });
    if(click_counter%2==0){
        DrawText("Quit <--", 300, 220, 20, YELLOW);
        DrawText("Start", 300, 320, 20, BLACK);
        exit=1;
    }
    else{
        DrawText("Quit", 300, 220, 20, BLACK);
        DrawText("Start <--", 300, 320, 20, YELLOW);
        exit=2;
    }
    if( IsKeyPressed(KEY_ENTER)) return exit;
    return 0;
}
int makeDeathMenu(const int screenWidth,const int screenHeight,int actual){
    int click_counter=actual;
    int exit=1;
    if( IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_UP)) click_counter++;
    DrawRectangle( screenWidth/2-200, screenHeight/2-100, 400,  200, (Color){ 230, 41, 55, 100 });
    DrawText("YOU DIED", 400, 260, 40, BLACK);
    if(click_counter%2==0){
        DrawText("Quit <--", 300, 220, 20, YELLOW);
        DrawText("Retry", 300, 320, 20, BLACK);
        exit=1;
    }
    else{
        DrawText("Quit", 300, 220, 20, BLACK);
        DrawText("Retry <--", 300, 320, 20, YELLOW);
        exit=2;
    }
    if( IsKeyPressed(KEY_ENTER)) return exit;
    return 0;
}