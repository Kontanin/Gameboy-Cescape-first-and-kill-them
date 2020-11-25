
// Gameboy C:escape first and kill them


// if you hited by moster or dead moster you are game over.
// button A: from shoot
// button right:move right
// button left:move left
// button up:move up
// button down:move down


#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"
#include "simplebackground.c"
#include "simplebackgroundmap.c"
#include <gb/font.h>
#include <rand.h>
#include <stdlib.h>
GameCharacter ship;
GameCharacter bug;
GameCharacter shoot;
GameCharacter onepoint;

UBYTE spritesize = 8;
UBYTE spriteridersize=2;
UINT8 xOnehundred;
UINT8 yOnehundred;


unsigned char levelup[] =
{
  0x17,0x10,0x21,0x10,0x17,0x00,0x00,0x20,0x1B
};




unsigned char windowmap[] =
{
  0x02,0x02,0x02,0x02
};

unsigned char gameover[] =
{
  0x12,0x0C,0x18,0x10,0x00,0x00,0x1A,0x21,0x10,0x1D
};
unsigned char onehundred[] =
{
  0x03,0x02,0x02,0x02
};

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}
UBYTE checkcollisions(GameCharacter* one, GameCharacter* two){
    return (one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height);
}
void movegamecharacter( GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}
void movegamecharacter1( GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spriteridersize, y);
    move_sprite(character->spritids[2], x, y + spriteridersize);
    move_sprite(character->spritids[3], x + spriteridersize, y + spriteridersize);
}
void setupship(){
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    // load sprites for ship
    set_sprite_tile(0, 0);
    ship.spritids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spritids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spritids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spritids[3] = 3;

    movegamecharacter(&ship, ship.x, ship.y);
}
void setupbugsmall(){
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;    

    // load sprites for bug
    set_sprite_tile(4, 4);
    bug.spritids[0] = 4;
    set_sprite_tile(5, 5);
    bug.spritids[1] = 5;
    set_sprite_tile(6, 6);
    bug.spritids[2] = 6;
    set_sprite_tile(7, 7);
    bug.spritids[3] = 7;

    // movegamecharacter(&bug, bug.x, bug.y);
}
void setupbug(){
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;    

    // load sprites for bug
    set_sprite_tile(4, 4);
    bug.spritids[0] = 4;
    set_sprite_tile(5, 5);
    bug.spritids[1] = 5;
    set_sprite_tile(6, 6);
    bug.spritids[2] = 6;
    set_sprite_tile(7, 7);
    bug.spritids[3] = 7;

    movegamecharacter(&bug, bug.x, bug.y);
}
void setuponepoint(){
    onepoint.x = -50;
    onepoint.y = -50;
    onepoint.width = 16;
    onepoint.height = 16;    

    // load sprites for bug
    set_sprite_tile(12, 12);
    onepoint.spritids[0] = 12;
    set_sprite_tile(13, 13);
    onepoint.spritids[1] = 13;
    set_sprite_tile(14, 14);
    onepoint.spritids[2] = 14;
    set_sprite_tile(15, 15);
    onepoint.spritids[3] = 15;

    movegamecharacter(&onepoint, onepoint.x, onepoint.y);
}
void setupshoot(){
    shoot.x = 80;
    shoot.y = 130;
    shoot.width = 8;
    shoot.height = 8;

    // load sprites for ship
    set_sprite_tile(8, 8);
    shoot.spritids[0] = 8;
    set_sprite_tile(9, 9);
    shoot.spritids[1] = 9;
    set_sprite_tile(10, 10);
    shoot.spritids[2] = 10;
    set_sprite_tile(11, 11);
    shoot.spritids[3] = 11;

    movegamecharacter(&shoot, shoot.x, shoot.y);
}
int s=0;
int dicrection=1;
int dicrectionShoot=1;
int point=0;
int i,j;
char martixoo[5];
int bugo=0;
int bugway=1;
void main(){

    
    font_t min_font;
    font_init();
    min_font = font_load(font_min); // 36 tile
    font_set(min_font);
    // UINT8 currentspriteindex = 0;
    set_sprite_data(0, 16, GameSprites);
    setuponepoint();
    setupship();
    setupbug();
    setupshoot();
    set_win_tiles(0,0,4,1,windowmap);
    SHOW_SPRITES;
    SHOW_WIN;
    DISPLAY_ON;
    

    while(!checkcollisions(&ship, &bug)){
//control

        if (checkcollisions(&shoot, &bug)){
            bugo=1;
            onepoint.x =bug.x;
            onepoint.y =bug.y;
            point+=100;
            sprintf (martixoo, "%d", point); 
                for (i=0; i<=3; i++){
                    switch (martixoo[i]){
                        case '0':
                            windowmap[i+1]=0x02;
                            break;
                        case '1':
                            windowmap[i+1]=0x03;
                            break;
                        case '2':
                            windowmap[i+1]=0x04;
                            break;
                        case '3':
                            windowmap[i+1]=0x05;
                            break;
                        case'4':
                            windowmap[i+1]=0x06;
                            break;
                        case '5':
                            windowmap[i+1]=0x07;
                            break;
                        case '6':
                            windowmap[i+1]=0x08;
                            break;
                        case '7':
                            windowmap[i+1]=0x09;
                            break;
                        case '8':
                            windowmap[i+1]=0x0A;
                            break;
                        case '9':
                            windowmap[i+1]=0x0B;
                            break;
                    }  
                }
            set_win_tiles(0,0,4,1,windowmap);

        }
       if(joypad() & J_LEFT){
           ship.x -= 3;
            if(s==0){
                shoot.x -= 3;
                dicrectionShoot=1;
            }
       }
       if(joypad() & J_RIGHT){
           ship.x += 3;
            if(s==0){
                shoot.x += 3;
                dicrectionShoot=2;
            }
       }
       if(joypad() & J_UP){
           ship.y -= 3;
            if(s==0){
                shoot.y -= 3;
                dicrectionShoot=3;
            }

       }
       if(joypad() & J_DOWN){
           ship.y += 3;
            if(s==0){
                shoot.y += 3;
                dicrectionShoot=4;
            }

       }
       if(joypad() & J_B){
           s=1;
           dicrection=dicrectionShoot;

       }



       if(s==1){
            switch(dicrection){
                case 1: 
                    shoot.x -= 8;
                    break;
                case 2: 
                    shoot.x += 8;
                    break;  
                case 3: 
                    shoot.y -= 8;
                    break; 
                case 4: 
                    shoot.y += 8;
                    break; 
            }   
        }

        if (shoot.y>144||shoot.y<0) {
            s=0;
            shoot.y=ship.y;
            shoot.x=ship.x;
        }
        else if(shoot.x>144||shoot.x<0) {
            s=0;
            shoot.y=ship.y;
            shoot.x=ship.x;
        }
       
        onepoint.y-=5; 
       if(onepoint.y >144){
           onepoint.y=-50;
           onepoint.x = -50;
       }


        if(bugway==1){
        bug.y+=4;
        }
        else if(bugway==2){
        bug.y-=4;
        }
        else if(bugway==3){
        bug.x+=4;
        }
        else if(bugway==4){
        bug.x-=4;
        }  
       if((bug.y > 144||bug.y <1)||(bug.x > 143||bug.x <1)){
            bugo=0;
            for( j = 0 ; j < 1; j++ ) {
                bugway=(rand() %3);
            }
            if(bugway<0){
                bugway=-bugway;
            }     
            if(bugway==257){
                bug.x=0;
                bug.y=ship.y-2;
                bugway=3;
            }
            else if(bugway==258||bugway==0){
                bug.x=143;
                bug.y=ship.y+2;
                bugway=4;
            }
            else if(bugway==1){
                bug.x=ship.x-2;
                bug.y=0;
            }
            else if(bugway==2){
                bug.x=ship.x+2;
                bug.y=143;
            }    
        }
       
       
       
       
       
       




        movegamecharacter(&onepoint, onepoint.x, onepoint.y);
        movegamecharacter(&shoot, shoot.x, shoot.y);

        if(bugo==1){
        movegamecharacter1(&bug,bug.x,bug.y);}
        else{
        movegamecharacter(&bug,bug.x,bug.y);    
        }

        movegamecharacter(&ship, ship.x, ship.y);
        performantdelay(5);  
        if (point==1000){
            set_win_tiles(0,0,4,1,onehundred);
            break;
        }


    }//while loop
    
    if (point==1000){
        set_win_tiles(5,8,9,1,levelup);
    }else{
        set_win_tiles(5,8,10,1,gameover);
    }
    
}
