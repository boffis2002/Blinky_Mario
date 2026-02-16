#include "raylib/include/raylib.h"
#include "scenes.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define GRAVITA     800.0f
#define SALTO       -500.0f
#define VELOCITA    180.0f


int main(void)
{
    srand(time(NULL));
    const int screenWidth = 960;
    const int screenHeight = 540;
    InitAudioDevice(); 
    Music colonna = LoadMusicStream("./audio/colonna.mp3");        
    Sound colpito = LoadSound("./audio/colpito.mp3");        
    InitWindow(screenWidth, screenHeight, "BlinkyMario");
    SetTargetFPS(60);

    Player mario = {0};
    mario.pos = (Vector2){100, 400};    
    Obj obstacoles[50];
    int obstacoles_size=makeObstacles(obstacoles,1);
    Obj grass = {0};
    grass.pos=(Vector2){0,500};
    Image image_bg = LoadImage("./images/bg.png"); 
    Image image_grass = LoadImage("./images/grass.png");
    Image image = LoadImage("./images/mario.png"); 
    Image image_jump = LoadImage("./images/mario_jump.png"); 
    Image image_dead = LoadImage("./images/mario_dead.png"); 
    Image image_mushroom = LoadImage("./images/mushroom.png"); 
    Image image_tree1 = LoadImage("./images/tree1.png"); 
    Image image_tree2 = LoadImage("./images/tree2.png"); 
    Image image_tree3 = LoadImage("./images/tree3.png"); 
    Image image_tree4 = LoadImage("./images/tree4.png"); 
    Image image_tree5 = LoadImage("./images/tree5.png"); 
    Image image_tree6 = LoadImage("./images/tree6.png"); 
    Texture2D mario_alive = LoadTextureFromImage(image);          
    Texture2D mario_jump = LoadTextureFromImage(image_jump);          
    Texture2D mario_dead = LoadTextureFromImage(image_dead);          
    Texture2D mush = LoadTextureFromImage(image_mushroom);         
    Texture2D bg = LoadTextureFromImage(image_bg);         
    Texture2D grasss = LoadTextureFromImage(image_grass);         
    Texture2D tree1 = LoadTextureFromImage(image_tree1);         
    Texture2D tree2 = LoadTextureFromImage(image_tree2);         
    Texture2D tree3 = LoadTextureFromImage(image_tree3);         
    Texture2D tree4 = LoadTextureFromImage(image_tree4);         
    Texture2D tree5 = LoadTextureFromImage(image_tree5);         
    Texture2D tree6 = LoadTextureFromImage(image_tree6);         
    UnloadImage(image);
    UnloadImage(image_jump);
    UnloadImage(image_mushroom);
    UnloadImage(image_bg);
    UnloadImage(image_grass);
    UnloadImage(image_tree1);
    UnloadImage(image_tree2);
    UnloadImage(image_tree3);
    UnloadImage(image_tree4);
    UnloadImage(image_tree5);
    UnloadImage(image_tree6);

    mario.collider = (Rectangle){mario.pos.x, mario.pos.y, 60, 77};
    

    // rettangolo pavimento di prova
    Rectangle ground = {0, 505, screenWidth*2, 100};

    // rettangolo piattaforma di prova
    int tick_counter=0;
    int death=0;
    int stop=0;
    int death_click_counter=0;
    int stop_click_counter=0;

    PlayMusicStream(colonna);
    SetExitKey(0);

    int treesX[30];
    int treesT[30];
    int treex=rand()%400;
    for(int i=0;i<30;i++){
        treex+=rand()%400;
        treesX[i]=treex;
        treesT[i]=rand()%6;
    }
    while (!WindowShouldClose())
    {
        if(death!=1&&stop!=1){
        // ──────────────── INPUT ────────────────
        mario.vel.x = 0;
        UpdateMusicStream ( colonna );
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))  {
            if(mario.pos.x+60>screenWidth/2){
                mario.vel.x =  0;
                grass.pos.x-=VELOCITA*GetFrameTime();
                for(int i=0;i<obstacoles_size;i++)obstacoles[i].pos.x-=VELOCITA*GetFrameTime();
            }
            else mario.vel.x =  VELOCITA;
        }
        if ((IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A))&& mario.pos.x>0)  mario.pos.x -= VELOCITA*GetFrameTime();

        if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && mario.onGround)
        {
            mario.vel.y = SALTO;
            mario.onGround = false;
        }







        // ──────────────── FISICA ────────────────
        mario.vel.y += GRAVITA * GetFrameTime();
        mario.pos.x += mario.vel.x * GetFrameTime();
        mario.pos.y += mario.vel.y * GetFrameTime();
    
        
        // aggiorna collider
        mario.collider.x = mario.pos.x;
        mario.collider.y = mario.pos.y;
        // reset a terra + collisioni
        mario.onGround = false;
        if( IsKeyPressed(KEY_ESCAPE)) stop=1;
        
        








        if( CheckCollisionRecs(mario.collider, ground))
        {
            if (mario.vel.y > 0)    // sta cadendo
            {
                mario.pos.y = ground.y - mario.collider.height;
                mario.vel.y = 0;
                mario.onGround = true;
            }
        }

        for(int i=0;i<obstacoles_size;i++){
            obstacoles[i].collider.x=obstacoles[i].pos.x;
            obstacoles[i].collider.y=obstacoles[i].pos.y;
            if(obstacoles[i].enemy){
                if(tick_counter%150<=75)obstacoles[i].pos.x += (VELOCITA-100) * GetFrameTime();
                else obstacoles[i].pos.x -= (VELOCITA-100) * GetFrameTime();
            }
            if (CheckCollisionRecs(mario.collider, obstacoles[i].collider))
            {   
                if(obstacoles[i].enemy==true) {PlaySound(colpito);death=1;break;}
                if (mario.vel.y > 0 && 
                    mario.pos.y + mario.collider.height - mario.vel.y*GetFrameTime() <= obstacoles[i].pos.y)
                {
                    mario.pos.y = obstacoles[i].pos.y - mario.collider.height;
                    mario.vel.y = 0;
                    mario.onGround = true;
                }
            }
        }
        
        tick_counter++;

        }


        // ──────────────── DISEGNO ────────────────
        BeginDrawing();
            
            DrawTexture(bg,0,0,WHITE);
            for(int i=0;i<30;i++){
                switch (treesT[i]){
                    case 0:
                        DrawTexture(tree1 ,grass.pos.x+treesX[i], 340, WHITE);
                    break;
                    case 1:
                        DrawTexture(tree2 ,grass.pos.x+treesX[i], 380, WHITE);
                    break;
                    case 2:
                        DrawTexture(tree3 ,grass.pos.x+treesX[i], 430, WHITE);
                    break;
                    case 3:
                        DrawTexture(tree4 ,grass.pos.x+treesX[i], 395, WHITE);
                    break;
                    case 4:
                        DrawTexture(tree5 ,grass.pos.x+treesX[i], 433, WHITE);
                    break;
                    case 5:
                        DrawTexture(tree6 ,grass.pos.x+treesX[i], 420, WHITE);
                    break;
                }

            }
            DrawTexture(grasss,grass.pos.x,470,WHITE);
            for(int i=0;i<obstacoles_size;i++){
                if(!obstacoles[i].enemy) DrawRectangleRec(obstacoles[i].collider, (Color){ 211, 176, 131, 255 });
                else DrawTexture(mush ,obstacoles[i].pos.x, obstacoles[i].pos.y, WHITE);
            }
            if(death==1) DrawTexture(mario_dead ,mario.pos.x, mario.pos.y, WHITE);
            else if(death==0&&mario.vel.y>=0) DrawTexture(mario_alive ,mario.pos.x, mario.pos.y, WHITE);
            else DrawTexture(mario_jump ,mario.pos.x, mario.pos.y, WHITE);
            DrawText("Blinky_Mario", mario.pos.x, mario.pos.y-30, 20, BLACK);
            if(death==1){
                int val=makeMenu(screenWidth,screenHeight,death_click_counter,2);
                if(IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_UP)) death_click_counter++;
                if(val==1)break;
                else if(val==2){
                    mario.pos.x=0;
                    makeObstacles(obstacoles,1);
                    death=0;
                }
            }
            if(stop==1){
                int val=makeMenu(screenWidth,screenHeight,stop_click_counter,1);
                if(IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_UP)) stop_click_counter++;
                if(val==1)break;
                else if(val==2)stop=0;
            }
        EndDrawing();
    }
    UnloadMusicStream(colonna);     
    CloseAudioDevice();
    CloseWindow();
    for(int i=0;i<obstacoles_size;i++)free(&obstacoles[i]);
    return 0;
}