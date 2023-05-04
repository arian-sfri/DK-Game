/* Authors:
    Arian Safari (30161346)
    Aishan Irfan (30157743)
*/

//including all the header files:
#include <unistd.h>
#include <stdio.h>
//#include <wiringPi.h>
#include "gpio.h"
#include "uart.h"
#include "fb.h"
#include "DonkeyKongTitle.h"
#include "controller.h"
#include "character front.h"
#include "character right.h"
#include "character left.h"
#include "character up.h"
#include "full heart.h"
#include "skeleton left.h"
#include "skeleton right.h"
#include "skeleton up.h"
#include "skeleton down.h"
#include "cactus1.h"
#include "cactus2.h"
#include "rock1.h"
#include "rock2.h"
#include "half heart.h"
#include "coin.h"
#include "blue heart.h"
#include "timer.h"
#include "score.h"
#include "door.h"
#include "pause.h"
#include "youLose.h"
#include "shark right.h"
#include "shark up.h"
#include "shark left.h"
#include "shark down.h"
#include "srock1.h"
#include "srock2.h"
#include "sweed1.h"
#include "sweed2.h"
#include "character front b.h"
#include "character up b.h"
#include "character left b.h"
#include "character right b.h"
#include "blue heart b.h"
#include "door b.h"
#include "coin b.h"
#include "prock.h"
#include "thorn.h"
#include "tree.h"
#include "tree2.h"
#include "wolf down.h"
#include "wolf left.h"
#include "wolf right.h"
#include "wolf up.h"
#include "character front  g.h"
#include "character left g.h"
#include "character right g.h"
#include "character up g.h"
#include "door g.h"
#include "blue heart g.h"
#include "coin g.h"
#include "door bl.h"
#include "blue heart bl.h"
#include "coin bl.h"
#include "character right bl.h"
#include "character left bl.h"
#include "character up bl.h"
#include "character front bl.h"
#include "dk left.h"
#include "dk right.h"
#include "dk up.h"
#include "dk down.h"
#include "barrel.h"
#include "ebarrel.h"
#include "youWin.h"
#include "score b.h"

#define GPIO_BASE 0xFE200000
#define CLO_REG 0xFE003004
unsigned int buttons[17] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int game_on =  0;
int character_x_loc, character_y_loc;

int main()
{

// the original printf library won't work. You have to use uart_puts so that it prints to the serial output.
void printf(char *str) {
	uart_puts(str);
}

    uart_init();
    fb_init();

    int q = startScreen();
    if(q == 0){
        return 0;
    }
}
    int level1(){

        //1st stage of the game
        
        //clock
        unsigned *clo = (unsigned*)CLO_REG;
        unsigned int game_start_time = *clo;
        unsigned int game_end_time = game_start_time+(50)*1000000;
     //   ----------------------LEVEL 1---------------------------------------
        //Drawing the background
        for(int i = 320; i < 1600; i++) {
            for (int j = 180; j < 730; j++){
                myDrawPixel(i, j, 0xffefdd6f);
            }
        }

        //Drawing the Status bar
        for(int i = 320; i < 1600; i++) {
            for (int j = 730; j < 900; j++){
                myDrawPixel(i, j, 0xffc9c9c1);
            }
        }

        //Draw the score image on the status bar
        myDrawImage(score_c.pixel_data, score_c.width, score_c.height, 800, 790);

        //Draw the hearts on the status bar
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 550, 760);

        //draw the timer image on the status bar
        myDrawImage(timer_c.pixel_data, timer_c.width, timer_c.height, 1280, 790);

        //characters x coordinate
        character_x_loc = 325;
        //charcaters y coordinate
        character_y_loc = 420;

        //enemy coordinates
        int enemy1_loc, enemy2_loc, enemy3_loc;
        int enemy1_side = 0;
        int enemy2_side = 0;
        int enemy3_side = 0;

        enemy1_loc = 1540;
        enemy2_loc = 185;
        enemy3_loc = 660;

        //health and points
        int health = 6;
        int points = 0;

        //Skeleton 2 
        myDrawImage(skeleton_down.pixel_data, skeleton_down.width, skeleton_down.height, 700, enemy2_loc);
        //Skeleton 3
        myDrawImage(skeleton_up.pixel_data, skeleton_up.width, skeleton_up.height, 1200, enemy3_loc);

        //Skeleton 1 
        myDrawImage(skeleton_left.pixel_data, skeleton_left.width, skeleton_left.height, enemy1_loc, 415);
        

        // drawing the character at the start
        myDrawImage(character_front.pixel_data, character_front.width, character_front.height, character_x_loc, character_y_loc);

        //drawing the cactus
        myDrawImage(cactus_2.pixel_data, cactus_2.width, cactus_2.height, 1300, 510);

        //drawing the rock
        myDrawImage(rock_1.pixel_data, rock_1.width,rock_1.height, 900, 540);

        //drawing the second rock
        myDrawImage(rock_2.pixel_data, rock_2.width,rock_2.height, 1300,300);

        //drawing the second rock
        myDrawImage(cactus_1.pixel_data, cactus_1.width, cactus_1.height, 900, 350);

        //coin3
        myDrawImage(coin_s.pixel_data,coin_s.width,coin_s.height, 550, 320);
        //coin1
        myDrawImage(coin_s.pixel_data,coin_s.width,coin_s.height,830,660);
        //coin2
        myDrawImage(coin_s.pixel_data,coin_s.width,coin_s.height,1330,185);
        
        //variables to keep track of score and, health and timer
        int digit1, digit2, digit3, remainder;
        int score1, score2, score3, score4, score_remainder;
        int heart_drawn = 0;
        char timer[3];
        char score_arr[4];

        //keeping track of the coins and the door
        int coin1_active = 1;
        int coin2_active = 1;
        int coin3_active = 1;
        int heart1_active = 1;
        int door_drawn = 0;

        while(1){

            //clock
            unsigned *clo = (unsigned*)CLO_REG;
            unsigned int current_time = *clo;
            unsigned int time_left = (game_end_time - current_time)/1000000;
            digit1 = time_left % 10;
            remainder = time_left / 10;
            digit2 = remainder % 10;
            remainder = remainder / 10;
            digit3 = remainder % 10;

            //converting the time to a chars
            timer[2] = (char)digit1 + 48;
            timer[1] = (char)digit2 + 48;
            timer[0] = (char)digit3 + 48;

            //converting the points to chars
            score1 = points % 10;
            score_remainder = points / 10;
            score2 = score_remainder % 10;
            score_remainder = score_remainder / 10;
            score3 = score_remainder % 10;
            score4 = score_remainder / 10;
            score_arr[0] = (char)score4 + 48;
            score_arr[1] = (char)score3 + 48;
            score_arr[2] = (char)score2 + 48;
            score_arr[3] = (char)score1 + 48;

            //draw the score as a string on the status bar
            drawString(950, 820, score_arr, 0x0f);

            //draw the timer as a string on the status bar
            drawString(1550, 820, timer, 0x0f);

            //drawing the booster.
            if(time_left < 40 && heart_drawn == 0){
                myDrawImage(blue_heart.pixel_data,blue_heart.width,blue_heart.height,1100,300);
                heart_drawn = 1;
            }

             //drawing the door
            if(points == 150 && door_drawn == 0){
                myDrawImage(door_c.pixel_data,door_c.width,door_c.height,1510, 520);
                door_drawn++;
            }

            //going to the next level.
            if (collision(character_x_loc, character_y_loc, 1510, 520, character_front.width, character_front.height, door_c.width, door_c.height) && door_drawn == 1){
                points += 100;
                int done = level2(health, points);

                //end game
                if (done == 0){
                    return 0;
                }
            }

            //controlling character movements on screen
            SNES(buttons);
            if (buttons[8] == 0 && character_x_loc + 5 < 1550 && !collision(character_x_loc + 5, character_y_loc, 900, 540, character_right.width, character_right.height, 70, 70) && !collision(character_x_loc + 5, character_y_loc, 1300, 300, character_right.width, character_right.height, 114, 62)){
                character_x_loc += 5;

                //right movement of the character
                move_right(0xffefdd6f, character_x_loc, character_y_loc);
            }
            if (buttons[6] == 0 && character_y_loc + 5 < 660 && !collision(character_x_loc, character_y_loc + 5, 900, 540, character_front.width, character_front.height, 70, 70) && !collision(character_x_loc, character_y_loc + 5, 1300, 300, character_front.width, character_front.height, 114, 62)){
                character_y_loc += 5;

                //downwards movement of the character
                move_down(0xffefdd6f, character_x_loc, character_y_loc);
            }
            if (buttons[7] == 0 && character_x_loc > 324 && !collision(character_x_loc - 5, character_y_loc, 900, 540, character_left.width, character_left.height, 70, 70) && !collision(character_x_loc - 5, character_y_loc, 1300, 300, character_left.width, character_left.height, 114, 62)){
                character_x_loc -= 5;

                //left movement of the character
                move_left(0xffefdd6f, character_x_loc, character_y_loc);
            }
            if (buttons[5] == 0 && character_y_loc > 180 && !collision(character_x_loc, character_y_loc - 5, 900, 540, character_up.width, character_up.height, 70, 70) && !collision(character_x_loc, character_y_loc - 5, 1300, 300, character_up.width, character_up.height, 114, 62)){
                character_y_loc -= 5;

                //upwards movement of the character
                move_up(0xffefdd6f, character_x_loc, character_y_loc);
            }

            //pause menu
            if(buttons[4] == 0){
                int quit = pause();

                //end game
                if (quit == 0){
                    return 0;
                }
            }
            
            //-------------------------------------------------//

            //ENEMY 1 MOVEMENT
            if (enemy1_side == 0){
                enemy1_loc -= 5;
                for (int i = enemy1_loc + 5; i < enemy1_loc; i--){
                    for (int j = 415; j < 415 + skeleton_left.height; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                myDrawImage(skeleton_left.pixel_data, skeleton_left.width, skeleton_left.height, enemy1_loc, 415);
            }
            else{
                enemy1_loc += 5;
                for (int i = enemy1_loc - 5; i < enemy1_loc; i++){
                    for (int j = 415; j < 415 + skeleton_right.height; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                myDrawImage(skeleton_right.pixel_data, skeleton_right.width, skeleton_right.height, enemy1_loc, 415);
            }
            //ENEMY 1 CHANGES SIDES
            if (enemy1_loc < 400){
                enemy1_side = 1;
            }
            else if (enemy1_loc == 1550){
                enemy1_side = 0;
            }

            //ENEMY 2 MOVEMENT
            if (enemy2_side == 0){
                enemy2_loc += 5;
                for (int i = 700; i < 700 + skeleton_down.width; i++){
                    for (int j = enemy2_loc - 5; j < enemy2_loc; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                myDrawImage(skeleton_down.pixel_data, skeleton_down.width, skeleton_down.height, 700, enemy2_loc);
            }
            else {
                enemy2_loc -= 5;
                for (int i = 700; i < 700 + skeleton_up.width; i++){
                    for (int j = enemy2_loc + 5 + skeleton_up.height; j < enemy2_loc + skeleton_up.height; j--){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                myDrawImage(skeleton_up.pixel_data, skeleton_up.width, skeleton_up.height, 700, enemy2_loc);
            }

            //ENEMY 2 CHANGE SIDES
            if (enemy2_loc > 660){
                enemy2_side = 1;
            }
            else if (enemy2_loc == 180){
                enemy2_side = 0;
            }

            //ENEMY 3 MOVEMENT
            if (enemy3_side == 0){
                enemy3_loc -= 5;
                for (int i = 1200; i < 1200 + skeleton_up.width; i++){
                    for (int j = enemy3_loc + 5 + skeleton_up.height; j < enemy3_loc + skeleton_up.height; j--){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                myDrawImage(skeleton_up.pixel_data, skeleton_up.width, skeleton_up.height, 1200, enemy3_loc);
            }
            else {
                enemy3_loc += 5;
                for (int i = 1200; i < 1200 + skeleton_down.width; i++){
                    for (int j = enemy3_loc - 5; j < enemy3_loc; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                myDrawImage(skeleton_down.pixel_data, skeleton_down.width, skeleton_down.height, 1200, enemy3_loc);
            }

            //ENEMY 3 CHANGE SIDES
            if (enemy3_loc < 190){
                enemy3_side = 1;
            }
            else if (enemy3_loc == 660){
                enemy3_side = 0;
            }

            //character collision with coin1
            
            if((character_x_loc + 55 > 830 && character_x_loc < 1020 && character_y_loc + 70 > 660 && character_y_loc < 724 && coin1_active == 1)){
                points += 50;
                coin1_active = 0;
                for(int i = 830; i< 830+100; i++ ){
                    for(int j = 660; j < 660+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
            }

            //charcater collision with coin2 
            if((character_x_loc + 55 > 550 && character_x_loc < 640 && character_y_loc + 70 > 320 && character_y_loc < 384 && coin2_active == 1)){
                points += 50;
                coin2_active = 0;
                for(int i = 550; i< 550+100; i++ ){
                    for(int j = 320; j < 320+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
            }

            //charcater collision with coin3 
            if((character_x_loc + 55 > 1330 && character_x_loc < 1420 && character_y_loc + 70 > 185 && character_y_loc < 250 && coin3_active == 1)){
                points += 50;
                coin3_active = 0;
                for(int i = 1330; i< 1330+100; i++ ){
                    for(int j = 185; j < 185+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
            }

            //character collision with booster
            if((character_x_loc + 55 > 1100 && character_x_loc < 1190 && character_y_loc + 70 > 300 && character_y_loc < 370 && heart1_active == 1)){
                heart1_active = 0;
                if (health < 6){

                    //gaining health
                    gainHealth(0xffefdd6f, health);
                    health += 1;
                }
                for(int i = 1100; i< 1100+70; i++ ){
                    for(int j = 300; j < 300+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
            }

            //character collision with cactus1(reduces health and sends the character back to start)
            if((character_x_loc + 55 > 900 && character_x_loc < 970 && character_y_loc + 70 > 350 && character_y_loc < 420)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_front.pixel_data, character_front.width, character_front.height, character_x_loc, character_y_loc);
            }

            //character collision with cactus2(reduces health and sends the charcater back to start)
            if((character_x_loc + 55 > 1300 && character_x_loc < 1370 && character_y_loc + 70 > 510 && character_y_loc < 580)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_front.pixel_data, character_front.width, character_front.height, character_x_loc, character_y_loc);
            }

            //character collision with Skeleton1(reduces health and send the character back to start)
            if (character_x_loc + 55 > enemy1_loc && character_x_loc < enemy1_loc + 52 && character_y_loc + 70 > 415 && character_y_loc < 480){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_front.pixel_data, character_front.width, character_front.height, character_x_loc, character_y_loc);
            }

            //character collision with Skeleton2(reduces health and send the character back to start)
            if (character_x_loc + 55 > 700 && character_x_loc < 700 + 61 && character_y_loc + 70 > enemy2_loc && character_y_loc < enemy2_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_front.pixel_data, character_front.width, character_front.height, character_x_loc, character_y_loc);
            }

            //character collision with Skeleton3(reduces health and send the character back to start)
            if (character_x_loc + 55 > 1200 && character_x_loc < 1200 + 61 && character_y_loc + 70 > enemy3_loc && character_y_loc < enemy3_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xffefdd6f);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_front.pixel_data, character_front.width, character_front.height, character_x_loc, character_y_loc);
            }

            //game lost
            if (health == 0 || time_left == 0){
                //displays the game lost screen
                int lost = lostGame();
                if (lost == 0){
                    //end game
                    return 0;
                }
            }

        }
    }


    //----------------------------------------------------------------------------------------//

    int level2(int health, int points){
        //level 2 of the game

        //clock
        unsigned *clo = (unsigned*)CLO_REG;
        unsigned int game_start_time = *clo;
        unsigned int game_end_time = game_start_time+(50)*1000000;

        //drawing the background 
        for(int i = 320; i < 1600; i++) {
            for (int j = 180; j < 730; j++){
                myDrawPixel(i, j, 0xff91d2ff);
            }
        }

        //drawing the Status bar
        for(int i = 320; i < 1600; i++) {
            for (int j = 730; j < 900; j++){
                myDrawPixel(i, j, 0xffc9c9c1);
            }
        }

        //drawing the score image on the status bar
        myDrawImage(score_c.pixel_data, score_c.width, score_c.height, 800, 790);

        //drawing the hearts on the status bar(depending on the health)
        if(health == 6){
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 550, 760);
        }
        else if (health == 5){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 550, 760);
        }
        else if (health == 4){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        }
        else if (health == 3){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 440, 760);
        }
        else if (health == 2){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        }
        else if (health == 1){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 330, 760);
        }

        //drawing the timer image on the status bar
        myDrawImage(timer_c.pixel_data, timer_c.width, timer_c.height, 1280, 790);

        //character and enemy coordinates
        character_x_loc = 325;
        character_y_loc = 420;
        int enemy1_loc, enemy2_loc, enemy3_loc;
        int enemy1_side = 0;
        int enemy2_side = 0;
        int enemy3_side = 0;

        enemy1_loc = 1505;
        enemy2_loc = 185;
        enemy3_loc = 635;

        //drawing shark 2 on the screen 
        myDrawImage(shark_down.pixel_data, shark_down.width, shark_down.height, 700, enemy2_loc);
        //drawing shark 3 on the screen
        myDrawImage(shark_up.pixel_data, shark_up.width, shark_up.height, 1200, enemy3_loc);

        //drawing shark 1 on the screen
        myDrawImage(shark_left.pixel_data, shark_left.width, shark_left.height, enemy1_loc, 415);
        
        //drawing the character on the screen
        myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, character_x_loc, character_y_loc);

        //drawing the 1st seaweed
        myDrawImage(sweed_2.pixel_data, sweed_2.width, sweed_2.height, 1300, 510);
        //drawing the 1st rock
        myDrawImage(srock_1.pixel_data, srock_1.width,srock_1.height, 900, 540);
        //drawing the 2nd rock
        myDrawImage(srock_2.pixel_data, srock_2.width,srock_2.height, 1300,300);
        //drawing the 2nd seaweed
        myDrawImage(sweed_1.pixel_data, sweed_1.width, sweed_1.height, 900, 350);
        //drawing the 1st coih
        myDrawImage(coin_sb.pixel_data,coin_sb.width,coin_sb.height, 550, 320);
        //drawing the 2nd coin
        myDrawImage(coin_sb.pixel_data,coin_sb.width,coin_sb.height,830,660);
        //drawing the 3rd coin
        myDrawImage(coin_sb.pixel_data,coin_sb.width,coin_sb.height,1330,185);
        
        //variables to keep tyrack of the score and health
        int digit1, digit2, digit3, remainder;
        int score1, score2, score3, score4, score_remainder;
        int heart_drawn = 0;
        char timer[3];
        char score_arr[4];

        //variables to keep track of the coins and the door
        int coin1_active = 1;
        int coin2_active = 1;
        int coin3_active = 1;
        int heart1_active = 1;
        int door_drawn = 0;

        while(1){

            //clock
            unsigned *clo = (unsigned*)CLO_REG;
            unsigned int current_time = *clo;
            unsigned int time_left = (game_end_time - current_time)/1000000;

            //converting the time to chars
            digit1 = time_left % 10;
            remainder = time_left / 10;
            digit2 = remainder % 10;
            remainder = remainder / 10;
            digit3 = remainder % 10;

            timer[2] = (char)digit1 + 48;
            timer[1] = (char)digit2 + 48;
            timer[0] = (char)digit3 + 48;

            //converting the score to chars
            score1 = points % 10;
            score_remainder = points / 10;
            score2 = score_remainder % 10;
            score_remainder = score_remainder / 10;
            score3 = score_remainder % 10;
            score4 = score_remainder / 10;
            score_arr[0] = (char)score4 + 48;
            score_arr[1] = (char)score3 + 48;
            score_arr[2] = (char)score2 + 48;
            score_arr[3] = (char)score1 + 48;

            //drawing the score on the status bar
            drawString(950, 820, score_arr, 0x0f);

            //drawing the timer on the status bar
            drawString(1550, 820, timer, 0x0f);

            //drawing the booster(appears after some time)
            if(time_left < 40 && heart_drawn == 0){
                myDrawImage(blue_heartb.pixel_data,blue_heartb.width,blue_heartb.height,1100,300);
                heart_drawn = 1;
            }

             //drawing the door(appears after collecting all the coins)
            if(points == 400 && door_drawn == 0){
                myDrawImage(door_cb.pixel_data,door_cb.width,door_cb.height,1510, 520);
                door_drawn++;
            }

            //moving to the next level through the door

            if (collision(character_x_loc, character_y_loc, 1510, 520, character_front.width, character_front.height, door_cb.width, door_cb.height) && door_drawn == 1){
                points += 100;
                int done = level3(health, points);
                if (done == 0){
                    //end game
                    return 0;
                }
            }


            //controlling the character movements on the screen using the snes controller
            SNES(buttons);
            if (buttons[8] == 0 && character_x_loc + 5 < 1550 && !collision(character_x_loc + 5, character_y_loc, 900, 540, character_rightb.width, character_rightb.height, 70, 70) && !collision(character_x_loc + 5, character_y_loc, 1300, 300, character_rightb.width, character_rightb.height, 114, 62)){
                character_x_loc += 5;
                move_right1(0xff91d2ff, character_x_loc, character_y_loc);
            }
            if (buttons[6] == 0 && character_y_loc + 5 < 660 && !collision(character_x_loc, character_y_loc + 5, 900, 540, character_frontb.width, character_frontb.height, 70, 70) && !collision(character_x_loc, character_y_loc + 5, 1300, 300, character_frontb.width, character_frontb.height, 114, 62)){
                character_y_loc += 5;
                move_down1(0xff91d2ff, character_x_loc, character_y_loc);
            }
            if (buttons[7] == 0 && character_x_loc > 324 && !collision(character_x_loc - 5, character_y_loc, 900, 540, character_leftb.width, character_leftb.height, 70, 70) && !collision(character_x_loc - 5, character_y_loc, 1300, 300, character_leftb.width, character_leftb.height, 114, 62)){
                character_x_loc -= 5;
                move_left1(0xff91d2ff, character_x_loc, character_y_loc);
            }
            if (buttons[5] == 0 && character_y_loc > 180 && !collision(character_x_loc, character_y_loc - 5, 900, 540, character_upb.width, character_upb.height, 70, 70) && !collision(character_x_loc, character_y_loc - 5, 1300, 300, character_upb.width, character_upb.height, 114, 62)){
                character_y_loc -= 5;
                move_up1(0xff91d2ff, character_x_loc, character_y_loc);
            }
            if(buttons[4] == 0){
                
                //pause menu
                int quit = pause();
                if (quit == 0){
                    //end game
                    return 0;
                }
            }
            
            //enemy movements

            //ENEMY 1 MOVEMENT
            if (enemy1_side == 0){
                enemy1_loc -= 7;
                for (int i = enemy1_loc + 7; i < enemy1_loc; i--){
                    for (int j = 415; j < 415 + shark_left.height; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                myDrawImage(shark_left.pixel_data, shark_left.width, shark_left.height, enemy1_loc, 415);
            }
            else{
                enemy1_loc += 7;
                for (int i = enemy1_loc - 7; i < enemy1_loc; i++){
                    for (int j = 415; j < 415 + shark_right.height; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                myDrawImage(shark_right.pixel_data, shark_right.width, shark_right.height, enemy1_loc, 415);
            }
            //ENEMY 1 CHANGE SIDES
            if (enemy1_loc < 400){
                enemy1_side = 1;
            }
            else if (enemy1_loc >= 1505){
                enemy1_side = 0;
            }

            //ENEMY 2 MOVEMENT
            if (enemy2_side == 0){
                enemy2_loc += 7;
                for (int i = 700; i < 700 + shark_down.width; i++){
                    for (int j = enemy2_loc - 7; j < enemy2_loc; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                myDrawImage(shark_down.pixel_data, shark_down.width, shark_down.height, 700, enemy2_loc);
            }
            else {
                enemy2_loc -= 7;
                for (int i = 700; i < 700 + shark_up.width; i++){
                    for (int j = enemy2_loc + 7 + shark_up.height; j < enemy2_loc + shark_up.height; j--){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                myDrawImage(shark_up.pixel_data, shark_up.width, shark_up.height, 700, enemy2_loc);
            }

            //ENEMY 2 CHANGE SIDES
            if (enemy2_loc >= 635){
                enemy2_side = 1;
            }
            else if (enemy2_loc <= 185){
                enemy2_side = 0;
            }

            //ENEMY 3 MOVEMENT
            if (enemy3_side == 0){
                enemy3_loc -= 7;
                for (int i = 1200; i < 1200 + shark_up.width; i++){
                    for (int j = enemy3_loc + 7 + shark_up.height; j < enemy3_loc + shark_up.height; j--){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                myDrawImage(shark_up.pixel_data, shark_up.width, shark_up.height, 1200, enemy3_loc);
            }
            else {
                enemy3_loc += 7;
                for (int i = 1200; i < 1200 + shark_down.width; i++){
                    for (int j = enemy3_loc - 7; j < enemy3_loc; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                myDrawImage(shark_down.pixel_data, shark_down.width, shark_down.height, 1200, enemy3_loc);
            }

            //ENEMY 3 CHANGE SIDES
            if (enemy3_loc < 190){
                enemy3_side = 1;
            }
            else if (enemy3_loc >= 635){
                enemy3_side = 0;
            }

            //character collision with coin 1(increases the score)
            
            if((character_x_loc + 55 > 830 && character_x_loc < 1020 && character_y_loc + 70 > 660 && character_y_loc < 724 && coin1_active == 1)){
                points += 50;
                coin1_active = 0;
                for(int i = 830; i< 830+100; i++ ){
                    for(int j = 660; j < 660+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
            }

            //character collision with coin 2(increases the score)
            if((character_x_loc + 55 > 550 && character_x_loc < 640 && character_y_loc + 70 > 320 && character_y_loc < 384 && coin2_active == 1)){
                points += 50;
                coin2_active = 0;
                for(int i = 550; i< 550+100; i++ ){
                    for(int j = 320; j < 320+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
            }

            //character collision with coin 3(increases the score)
            if((character_x_loc + 55 > 1330 && character_x_loc < 1420 && character_y_loc + 70 > 185 && character_y_loc < 250 && coin3_active == 1)){
                points += 50;
                coin3_active = 0;
                for(int i = 1330; i< 1330+100; i++ ){
                    for(int j = 185; j < 185+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
            }

            //character collison with booster(increases health)
            if((character_x_loc + 55 > 1100 && character_x_loc < 1190 && character_y_loc + 70 > 300 && character_y_loc < 370 && heart1_active == 1)){
                heart1_active = 0;
                if (health < 6){
                    gainHealth(0xff91d2ff, health);
                    health += 1;
                }
                for(int i = 1100; i< 1100+70; i++ ){
                    for(int j = 300; j < 300+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
            }

            //charactrer collision with seaweed1(reduces the health and sends the character back to the start)
            if((character_x_loc + 55 > 900 && character_x_loc < 970 && character_y_loc + 70 > 350 && character_y_loc < 420)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, character_x_loc, character_y_loc);
            }

            //charactrer collision with seaweed2(reduces the health and sends the character back to the start)
            if((character_x_loc + 55 > 1300 && character_x_loc < 1370 && character_y_loc + 70 > 510 && character_y_loc < 580)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, character_x_loc, character_y_loc);
            }

            //charactrer collision with shark 1(reduces the health and sends the character back to the start)
            if (character_x_loc + 55 > enemy1_loc && character_x_loc < enemy1_loc + 52 && character_y_loc + 70 > 415 && character_y_loc < 480){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, character_x_loc, character_y_loc);
            }

            //charactrer collision with shark 2(reduces the health and sends the character back to the start)
            if (character_x_loc + 55 > 700 && character_x_loc < 700 + 61 && character_y_loc + 70 > enemy2_loc && character_y_loc < enemy2_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, character_x_loc, character_y_loc);
            }

            //charactrer collision with shark 3(reduces the health and sends the character back to the start)
            if (character_x_loc + 55 > 1200 && character_x_loc < 1200 + 61 && character_y_loc + 70 > enemy3_loc && character_y_loc < enemy3_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff91d2ff);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, character_x_loc, character_y_loc);
            }
            //lose game
            if (health == 0 || time_left == 0){
                int lost = lostGame();
                if (lost == 0){
                    //end game
                    return 0;
                }
            }

        }
    }


    //------------------ level 3-----------------------------

    int level3(int health, int points){

        //stage 3 of the game
        //clock
        unsigned *clo = (unsigned*)CLO_REG;
        unsigned int game_start_time = *clo;
        unsigned int game_end_time = game_start_time+(65)*1000000;

        //drawing the background screen
        for(int i = 320; i < 1600; i++) {
            for (int j = 180; j < 730; j++){
                myDrawPixel(i, j, 0xff228c22);
            }
        }

        //drawing the status bar 
        for(int i = 320; i < 1600; i++) {
            for (int j = 730; j < 900; j++){
                myDrawPixel(i, j, 0xffc9c9c1);
            }
        }

        //drawing the score image on the status bar
        myDrawImage(score_c.pixel_data, score_c.width, score_c.height, 800, 790);

        //drawing the hearts on the staus bar(depends on the health)
        if(health == 6){
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 550, 760);
        }
        else if (health == 5){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 550, 760);
        }
        else if (health == 4){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        }
        else if (health == 3){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 440, 760);
        }
        else if (health == 2){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        }
        else if (health == 1){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 330, 760);
        }

        //drawing the timer image on the screen
        myDrawImage(timer_c.pixel_data, timer_c.width, timer_c.height, 1280, 790);

        //character and enemy coordinates
        character_x_loc = 325;
        character_y_loc = 420;
        int enemy1_loc, enemy2_loc, enemy3_loc;
        int enemy1_side = 0;
        int enemy2_side = 0;
        int enemy3_side = 0;

        enemy1_loc = 1480;
        enemy2_loc = 185;
        enemy3_loc = 610;

        //drawing wolf 2 on the screem
        myDrawImage(wolf_down.pixel_data, wolf_down.width, wolf_down.height, 700, enemy2_loc);
        //drawing wolf 3 on the screen
        myDrawImage(wolf_up.pixel_data, wolf_up.width, wolf_up.height, 1200, enemy3_loc);

        //drawing wolf 1 on the screen
        myDrawImage(wolf_left.pixel_data, wolf_left.width, wolf_left.height, enemy1_loc, 415);
        
        //drawing the character on the screen
        myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, character_x_loc, character_y_loc);

        //drawing the thorn on the screen
        myDrawImage(thorn_c.pixel_data, thorn_c.width, thorn_c.height, 1300, 510);
        //drawing the 1st tree on the screen
        myDrawImage(tree_c.pixel_data, tree_c.width,tree_c.height, 900, 540);
        //drawing the second tree on ther screen
        myDrawImage(tree2_c.pixel_data, tree2_c.width,tree2_c.height, 1300,300);
        //drawing the poison rock on the screen
        myDrawImage(prock_1.pixel_data, prock_1.width, prock_1.height, 900, 350);
        //drawing the 1st coin on the screen
        myDrawImage(coin_sg.pixel_data,coin_sg.width,coin_sg.height, 550, 320);
        //drawing the 2nd coin on the screen
        myDrawImage(coin_sg.pixel_data,coin_sg.width,coin_sg.height,830,660);
        //drawing the 3rd coin on the screen
        myDrawImage(coin_sg.pixel_data,coin_sg.width,coin_sg.height,1330,185);
        
        //varaibles to keep track of the score and the hearts
        int digit1, digit2, digit3, remainder;
        int score1, score2, score3, score4, score_remainder;
        int heart_drawn = 0;
        char timer[3];
        char score_arr[4];

        //variables to keep track of the coins and the door
        int coin1_active = 1;
        int coin2_active = 1;
        int coin3_active = 1;
        int heart1_active = 1;
        int door_drawn = 0;

        while(1){

            //clock
            unsigned *clo = (unsigned*)CLO_REG;
            unsigned int current_time = *clo;
            unsigned int time_left = (game_end_time - current_time)/1000000;

            //converting the timer to chars
            digit1 = time_left % 10;
            remainder = time_left / 10;
            digit2 = remainder % 10;
            remainder = remainder / 10;
            digit3 = remainder % 10;

            timer[2] = (char)digit1 + 48;
            timer[1] = (char)digit2 + 48;
            timer[0] = (char)digit3 + 48;

            //converting the score to chars
            score1 = points % 10;
            score_remainder = points / 10;
            score2 = score_remainder % 10;
            score_remainder = score_remainder / 10;
            score3 = score_remainder % 10;
            score4 = score_remainder / 10;
            score_arr[0] = (char)score4 + 48;
            score_arr[1] = (char)score3 + 48;
            score_arr[2] = (char)score2 + 48;
            score_arr[3] = (char)score1 + 48;
            //drawing the score on the status bar
            drawString(950, 820, score_arr, 0x0f);

            //drawing the timer on the status bar
            drawString(1550, 820, timer, 0x0f);

            //drawing the booster on the screen(displays after some time)
            if(time_left < 40 && heart_drawn == 0){
                myDrawImage(blue_heartg.pixel_data,blue_heartg.width,blue_heartg.height,1100,300);
                heart_drawn = 1;
            }

             //drawing the door on the screen
            if(points == 650 && door_drawn == 0){
                myDrawImage(door_cg.pixel_data,door_cg.width,door_cg.height,1510, 520);
                door_drawn++;
            }

            //going to the next level through the door

            if (collision(character_x_loc, character_y_loc, 1510, 520, character_front.width, character_front.height, door_cb.width, door_cb.height) && door_drawn == 1){
                points += 100;
                int done = level4(health, points);
                if (done == 0){
                    //end game
                    return 0;
                }
            }


            //controlling the character movements on the screen using the snes
            SNES(buttons);
            if (buttons[8] == 0 && character_x_loc + 5 < 1550 && !collision(character_x_loc + 5, character_y_loc, 900, 540, character_rightg.width, character_rightg.height, 70, 70) && !collision(character_x_loc + 5, character_y_loc, 1300, 300, character_rightg.width, character_rightg.height, 114, 62)){
                character_x_loc += 5;
                move_right2(0xff228c22, character_x_loc, character_y_loc);
            }
            if (buttons[6] == 0 && character_y_loc + 5 < 660 && !collision(character_x_loc, character_y_loc + 5, 900, 540, character_frontg.width, character_frontg.height, 70, 70) && !collision(character_x_loc, character_y_loc + 5, 1300, 300, character_frontg.width, character_frontg.height, 114, 62)){
                character_y_loc += 5;
                move_down2(0xff228c22, character_x_loc, character_y_loc);
            }
            if (buttons[7] == 0 && character_x_loc > 324 && !collision(character_x_loc - 5, character_y_loc, 900, 540, character_leftg.width, character_leftg.height, 70, 70) && !collision(character_x_loc - 5, character_y_loc, 1300, 300, character_leftg.width, character_leftg.height, 114, 62)){
                character_x_loc -= 5;
                move_left2(0xff228c22, character_x_loc, character_y_loc);
            }
            if (buttons[5] == 0 && character_y_loc > 180 && !collision(character_x_loc, character_y_loc - 5, 900, 540, character_upg.width, character_upg.height, 70, 70) && !collision(character_x_loc, character_y_loc - 5, 1300, 300, character_upg.width, character_upg.height, 114, 62)){
                character_y_loc -= 5;
                move_up2(0xff228c22, character_x_loc, character_y_loc);
            }
            if(buttons[4] == 0){
                //pause menu
                int quit = pause();
                if (quit == 0){
                    //end game
                    return 0;
                }
            }
            

            //ENEMY 1 MOVEMENT
            if (enemy1_side == 0){
                enemy1_loc -= 11;
                for (int i = enemy1_loc + 11; i < enemy1_loc; i--){
                    for (int j = 415; j < 415 + wolf_left.height; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                myDrawImage(wolf_left.pixel_data, wolf_left.width, wolf_left.height, enemy1_loc, 415);
            }
            else{
                enemy1_loc += 11;
                for (int i = enemy1_loc - 11; i < enemy1_loc; i++){
                    for (int j = 415; j < 415 + wolf_right.height; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                myDrawImage(wolf_right.pixel_data, wolf_right.width, wolf_right.height, enemy1_loc, 415);
            }
            //ENEMY 1 CHANGE SIDES
            if (enemy1_loc < 400){
                enemy1_side = 1;
            }
            else if (enemy1_loc >= 1480){
                enemy1_side = 0;
            }

            //ENEMY 2 MOVEMENT
            if (enemy2_side == 0){
                enemy2_loc += 11;
                for (int i = 700; i < 700 + wolf_down.width; i++){
                    for (int j = enemy2_loc - 11; j < enemy2_loc; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                myDrawImage(wolf_down.pixel_data, wolf_down.width, wolf_down.height, 700, enemy2_loc);
            }
            else {
                enemy2_loc -= 11;
                for (int i = 700; i < 700 + wolf_up.width; i++){
                    for (int j = enemy2_loc + 11 + wolf_up.height; j < enemy2_loc + wolf_up.height; j--){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                myDrawImage(wolf_up.pixel_data, wolf_up.width, wolf_up.height, 700, enemy2_loc);
            }

            //ENEMY 2 CHANGE SIDES
            if (enemy2_loc >= 605){
                enemy2_side = 1;
            }
            else if (enemy2_loc <= 185){
                enemy2_side = 0;
            }

            //ENEMY 3 MOVEMENT
            if (enemy3_side == 0){
                enemy3_loc -= 11;
                for (int i = 1200; i < 1200 + wolf_up.width; i++){
                    for (int j = enemy3_loc + 11 + wolf_up.height; j < enemy3_loc + wolf_up.height; j--){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                myDrawImage(wolf_up.pixel_data, wolf_up.width, wolf_up.height, 1200, enemy3_loc);
            }
            else {
                enemy3_loc += 11;
                for (int i = 1200; i < 1200 + wolf_down.width; i++){
                    for (int j = enemy3_loc - 11; j < enemy3_loc; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                myDrawImage(wolf_down.pixel_data, wolf_down.width, wolf_down.height, 1200, enemy3_loc);
            }

            //ENEMY 3 CHANGE SIDES
            if (enemy3_loc < 190){
                enemy3_side = 1;
            }
            else if (enemy3_loc >= 610){
                enemy3_side = 0;
            }

            //character collision with coin 1(increases the score)
            
            if((character_x_loc + 55 > 830 && character_x_loc < 1020 && character_y_loc + 70 > 660 && character_y_loc < 724 && coin1_active == 1)){
                points += 50;
                coin1_active = 0;
                for(int i = 830; i< 830+100; i++ ){
                    for(int j = 660; j < 660+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
            }

            //character collision with coin 2(increases the score)
            if((character_x_loc + 55 > 550 && character_x_loc < 640 && character_y_loc + 70 > 320 && character_y_loc < 384 && coin2_active == 1)){
                points += 50;
                coin2_active = 0;
                for(int i = 550; i< 550+100; i++ ){
                    for(int j = 320; j < 320+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
            }

            //character collision with coin 3(increases the score)
            if((character_x_loc + 55 > 1330 && character_x_loc < 1420 && character_y_loc + 70 > 185 && character_y_loc < 250 && coin3_active == 1)){
                points += 50;
                coin3_active = 0;
                for(int i = 1330; i< 1330+100; i++ ){
                    for(int j = 185; j < 185+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
            }

            //character collision with the booster(increases the health)
            if((character_x_loc + 55 > 1100 && character_x_loc < 1190 && character_y_loc + 70 > 300 && character_y_loc < 370 && heart1_active == 1)){
                heart1_active = 0;
                if (health < 6){
                    gainHealth(0xff91d2ff, health);
                    health += 1;
                }
                for(int i = 1100; i< 1100+70; i++ ){
                    for(int j = 300; j < 300+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
            }

            //character collision with the poison rock(decreases the health and sends the character back to the start)
            if((character_x_loc + 55 > 900 && character_x_loc < 970 && character_y_loc + 70 > 350 && character_y_loc < 420)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, character_x_loc, character_y_loc);
            }

            //character collision with the thorn(decreases the health and sends the character back to the start)
            if((character_x_loc + 55 > 1300 && character_x_loc < 1370 && character_y_loc + 70 > 510 && character_y_loc < 580)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, character_x_loc, character_y_loc);
            }

            //character collision with wolf 1(decreases the health and sends the character back to the start)
            if (character_x_loc + 55 > enemy1_loc && character_x_loc < enemy1_loc + 52 && character_y_loc + 70 > 415 && character_y_loc < 480){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, character_x_loc, character_y_loc);
            }

            //character collision with wolf 2(decreases the health and sends the character back to the start)
            if (character_x_loc + 55 > 700 && character_x_loc < 700 + 61 && character_y_loc + 70 > enemy2_loc && character_y_loc < enemy2_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, character_x_loc, character_y_loc);
            }

            //character collision with wolf 3(decreases the health and sends the character back to the start)
            if (character_x_loc + 55 > 1200 && character_x_loc < 1200 + 61 && character_y_loc + 70 > enemy3_loc && character_y_loc < enemy3_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff228c22);
                    }
                }
                character_x_loc = 325;
                character_y_loc = 420;
                myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, character_x_loc, character_y_loc);
            }
            //game lost
            if (health == 0 || time_left == 0){
                int lost = lostGame();
                if (lost == 0){
                    //end game
                    return 0;
                }
            }

        }
    }


    //-------------------------------------level4---------------------------------------------------
    int level4(int health, int points){
        //final stage of the game
        //clock
        unsigned *clo = (unsigned*)CLO_REG;
        unsigned int game_start_time = *clo;
        unsigned int game_end_time = game_start_time+(65)*1000000;

        //draw the borders
        //top border
        for(int i = 320; i<= 1600; i++){
            for(int j = 180; j< 180+15; j++){
                myDrawPixel(i,j,0xf0000ff);
            }
        }

        //bottom border
        for(int i = 320; i<= 1600; i++){
            for(int j = 730-15; j<= 730; j++){
                myDrawPixel(i,j,0xf0000ff);
            }
        }

        //left border
        for(int i = 320; i< 320+15; i++){
            for(int j = 180+15; j<= 730-15; j++){
                myDrawPixel(i,j,0xf0000ff);
            }
        }

        //right border
        for(int i = 1600-14; i<= 1600; i++){
            for(int j = 180+15; j<= 730-15; j++){
                myDrawPixel(i,j,0xf0000ff);
            }
        }

        //drawing the background
        for(int i = 320+15; i < 1600-15; i++) {
            for (int j = 180+15; j < 730-15; j++){
                myDrawPixel(i, j, 0xff000000);
            }
        }

        //drawing the status bar
        for(int i = 320; i < 1600; i++) {
            for (int j = 730; j < 900; j++){
                myDrawPixel(i, j, 0xffc9c9c1);
            }
        }

        //drawing the score image on the status bar
        myDrawImage(score_c.pixel_data, score_c.width, score_c.height, 800, 790);

        //drawing the hearts on the status bar(depends on the health)
        if(health == 6){
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 550, 760);
        }
        else if (health == 5){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 550, 760);
        }
        else if (health == 4){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        }
        else if (health == 3){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 440, 760);
        }
        else if (health == 2){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        }
        else if (health == 1){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 330, 760);
        }

        //drawing the timer image on the status bar
        myDrawImage(timer_c.pixel_data, timer_c.width, timer_c.height, 1280, 790);

        //character and enemy coordinates
        character_x_loc = 340;
        character_y_loc = 420;
        int enemy1_loc, enemy2_loc, enemy3_loc;
        int enemy1_side = 0;
        int enemy2_side = 0;
        int enemy3_side = 0;

        enemy1_loc = 1480;
        enemy2_loc = 195;
        enemy3_loc = 610;

        //drawing kong 2 on thew screen
        myDrawImage(dk_down.pixel_data, dk_down.width, dk_down.height, 700, enemy2_loc+15);
        //drawing kong 3 on the screen
        myDrawImage(dk_up.pixel_data, dk_up.width, dk_up.height, 1200, enemy3_loc);

        //drawing kong 1 on the screen
        myDrawImage(dk_left.pixel_data, dk_left.width, dk_left.height, enemy1_loc, 415);
        
        //drawing the character on the screen
        myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, character_x_loc, character_y_loc);

        //drawing explosive barrel 1 on screen
        myDrawImage(ebarrel_c.pixel_data, ebarrel_c.width, ebarrel_c.height, 1300, 510);
        //drawing barrel 1 on screen
        myDrawImage(barrel_c.pixel_data, barrel_c.width,barrel_c.height, 900, 540);
        //drawing barrel 2 on screen
        myDrawImage(barrel_c.pixel_data, barrel_c.width,barrel_c.height, 1300,300);
        //drawing explosive barrel 2 on screen
        myDrawImage(ebarrel_c.pixel_data, ebarrel_c.width, ebarrel_c.height, 900, 350);
        //drawing the 1st coin
        myDrawImage(coin_sbl.pixel_data,coin_sbl.width,coin_sbl.height, 550, 320);
        //drawing the 2nd coin
        myDrawImage(coin_sbl.pixel_data,coin_sbl.width,coin_sbl.height,830,660-15);
        //drawing the 3rd coin
        myDrawImage(coin_sbl.pixel_data,coin_sbl.width,coin_sbl.height,1330,185+15);
        
        //variables to keep track of the score and health
        int digit1, digit2, digit3, remainder;
        int score1, score2, score3, score4, score_remainder;
        int heart_drawn = 0;
        char timer[3];
        char score_arr[4];

        //variables to keep track of the coins and the door
        int coin1_active = 1;
        int coin2_active = 1;
        int coin3_active = 1;
        int heart1_active = 1;
        int door_drawn = 0;

        while(1){

            //clock
            unsigned *clo = (unsigned*)CLO_REG;
            unsigned int current_time = *clo;
            unsigned int time_left = (game_end_time - current_time)/1000000;
            //converting the time to chars
            digit1 = time_left % 10;
            remainder = time_left / 10;
            digit2 = remainder % 10;
            remainder = remainder / 10;
            digit3 = remainder % 10;

            timer[2] = (char)digit1 + 48;
            timer[1] = (char)digit2 + 48;
            timer[0] = (char)digit3 + 48;

            //converting the score to chars
            score1 = points % 10;
            score_remainder = points / 10;
            score2 = score_remainder % 10;
            score_remainder = score_remainder / 10;
            score3 = score_remainder % 10;
            score4 = score_remainder / 10;
            score_arr[0] = (char)score4 + 48;
            score_arr[1] = (char)score3 + 48;
            score_arr[2] = (char)score2 + 48;
            score_arr[3] = (char)score1 + 48;
            //draw the score on the status bar
            drawString(950, 820, score_arr, 0x0f);

            //draw the timer on the status bar
            drawString(1550, 820, timer, 0x0f);

            //drawing the booster on the screen(appears after some time)
            if(time_left < 40 && heart_drawn == 0){
                myDrawImage(blue_heartbl.pixel_data,blue_heartbl.width,blue_heartbl.height,1100,300);
                heart_drawn = 1;
            }

             //drawing the door on the screen(appears after collecting all the coins)
            if(points == 900 && door_drawn == 0){
                myDrawImage(door_cbl.pixel_data,door_cbl.width,door_cbl.height,1495, 520);
                door_drawn++;
            }

            //going through the door wins the game

            if (collision(character_x_loc, character_y_loc, 1510, 520, character_front.width, character_front.height, door_cb.width, door_cb.height) && door_drawn == 1){
                for(int i = 320; i < 1600; i++) {
                    for (int j = 180; j < 900; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                //game won
                int q = youWin(score_arr);
                if(q == 0){
                    //end gaame
                    return 0;
                }
            }

            //controlling the character movements on the screen using the snes controller
            SNES(buttons);
            if (buttons[8] == 0 && character_x_loc + 5 < 1535 && !collision(character_x_loc + 5, character_y_loc, 900, 540, character_rightbl.width, character_rightbl.height, 70, 70) && !collision(character_x_loc + 5, character_y_loc, 1300, 300, character_rightbl.width, character_rightbl.height, 114, 62)){
                character_x_loc += 5;
                move_right3(0xff000000, character_x_loc, character_y_loc);
            }
            if (buttons[6] == 0 && character_y_loc + 5 < 645 && !collision(character_x_loc, character_y_loc + 5, 900, 540, character_frontbl.width, character_frontbl.height, 70, 70) && !collision(character_x_loc, character_y_loc + 5, 1300, 300, character_frontbl.width, character_frontbl.height, 114, 62)){
                character_y_loc += 5;
                move_down3(0xff000000, character_x_loc, character_y_loc);
            }
            if (buttons[7] == 0 && character_x_loc > 339 && !collision(character_x_loc - 5, character_y_loc, 900, 540, character_leftbl.width, character_leftbl.height, 70, 70) && !collision(character_x_loc - 5, character_y_loc, 1300, 300, character_leftbl.width, character_leftbl.height, 114, 62)){
                character_x_loc -= 5;
                move_left3(0xff000000, character_x_loc, character_y_loc);
            }
            if (buttons[5] == 0 && character_y_loc > 195 && !collision(character_x_loc, character_y_loc - 5, 900, 540, character_upbl.width, character_upbl.height, 70, 70) && !collision(character_x_loc, character_y_loc - 5, 1300, 300, character_upbl.width, character_upbl.height, 114, 62)){
                character_y_loc -= 5;
                move_up3(0xff000000, character_x_loc, character_y_loc);
            }
            if(buttons[4] == 0){
                //pause menu
                int quit = pause();
                if (quit == 0){
                    //end game
                    return 0;
                }
            }
        

            //ENEMY 1 MOVEMENT
            if (enemy1_side == 0){
                enemy1_loc -= 11;
                for (int i = enemy1_loc + 11; i < enemy1_loc; i--){
                    for (int j = 415; j < 415 + dk_left.height; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                myDrawImage(dk_left.pixel_data, dk_left.width, dk_left.height, enemy1_loc, 415);
            }
            else{
                enemy1_loc += 11;
                for (int i = enemy1_loc - 11; i < enemy1_loc; i++){
                    for (int j = 415; j < 415 + dk_right.height; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                myDrawImage(dk_right.pixel_data, dk_right.width, dk_right.height, enemy1_loc, 415);
            }
            //ENEMY 1 CHANGE SIDES
            if (enemy1_loc < 400){
                enemy1_side = 1;
            }
            else if (enemy1_loc >= 1480){
                enemy1_side = 0;
            }

            //ENEMY 2 MOVEMENT
            if (enemy2_side == 0){
                enemy2_loc += 11;
                for (int i = 700; i < 700 + dk_down.width; i++){
                    for (int j = enemy2_loc - 11; j < enemy2_loc; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                myDrawImage(dk_down.pixel_data, dk_down.width, dk_down.height, 700, enemy2_loc);
            }
            else {
                enemy2_loc -= 11;
                for (int i = 700; i < 700 + dk_up.width; i++){
                    for (int j = enemy2_loc + 11 + dk_up.height; j < enemy2_loc + dk_up.height; j--){
                        myDrawPixel(i, j, 0xfff000000);
                    }
                }
                myDrawImage(dk_up.pixel_data, dk_up.width, dk_up.height, 700, enemy2_loc);
            }

            //ENEMY 2 CHANGE SIDES
            if (enemy2_loc >= 605){
                enemy2_side = 1;
            }
            else if (enemy2_loc <= 200){
                enemy2_side = 0;
            }

            //ENEMY 3 MOVEMENT
            if (enemy3_side == 0){
                enemy3_loc -= 11;
                for (int i = 1200; i < 1200 + dk_up.width; i++){
                    for (int j = enemy3_loc + 11 + dk_up.height; j < enemy3_loc + dk_up.height; j--){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                myDrawImage(dk_up.pixel_data, dk_up.width, dk_up.height, 1200, enemy3_loc);
            }
            else {
                enemy3_loc += 11;
                for (int i = 1200; i < 1200 + dk_down.width; i++){
                    for (int j = enemy3_loc - 11; j < enemy3_loc; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                myDrawImage(dk_down.pixel_data, dk_down.width, dk_down.height, 1200, enemy3_loc);
            }

            //ENEMY 3 CHANGE SIDES
            if (enemy3_loc < 205){
                enemy3_side = 1;
            }
            else if (enemy3_loc >= 605){
                enemy3_side = 0;
            }

            //character collision with coin1(increases the score)  
            if((character_x_loc + 55 > 830 && character_x_loc < 1020 && character_y_loc + 70 > 660 && character_y_loc < 724 && coin1_active == 1)){
                points += 50;
                coin1_active = 0;
                for(int i = 830; i< 830+100; i++ ){
                    for(int j = 640; j < 640+62; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
            }

            //character collision with coin2(increases the score)
            if((character_x_loc + 55 > 550 && character_x_loc < 640 && character_y_loc + 70 > 320 && character_y_loc < 384 && coin2_active == 1)){
                points += 50;
                coin2_active = 0;
                for(int i = 550; i< 550+100; i++ ){
                    for(int j = 320; j < 320+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
            }

            //character collision with coin3(increases the score)
            if((character_x_loc + 55 > 1330 && character_x_loc < 1420 && character_y_loc + 70 > 185 && character_y_loc < 250 && coin3_active == 1)){
                points += 50;
                coin3_active = 0;
                for(int i = 1330; i< 1330+85; i++ ){
                    for(int j = 195; j < 195+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
            }

            //character collision with the booster(increases the health)
            if((character_x_loc + 55 > 1100 && character_x_loc < 1190 && character_y_loc + 70 > 300 && character_y_loc < 370 && heart1_active == 1)){
                heart1_active = 0;
                if (health < 6){
                    //gains health
                    gainHealth(0xff91d2ff, health);
                    health += 1;
                }
                for(int i = 1100; i< 1100+70; i++ ){
                    for(int j = 300; j < 300+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
            }

            //character collision with explosive barrel1(decreases the health and sends the character back to the start)
            if((character_x_loc + 55 > 900 && character_x_loc < 970 && character_y_loc + 70 > 350 && character_y_loc < 420)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                character_x_loc = 340;
                character_y_loc = 420;
                myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, character_x_loc, character_y_loc);
            }

            //character collision with explosive barrel2(decreases the health and sends the character back to the start)
            if((character_x_loc + 55 > 1300 && character_x_loc < 1370 && character_y_loc + 70 > 510 && character_y_loc < 580)){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                character_x_loc = 340;
                character_y_loc = 420;
                myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, character_x_loc, character_y_loc);
            }

            //character collision with kong 1(decreases the health and sends the character back to the start)
            if (character_x_loc + 55 > enemy1_loc && character_x_loc < enemy1_loc + 52 && character_y_loc + 70 > 415 && character_y_loc < 480){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                character_x_loc = 340;
                character_y_loc = 420;
                myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, character_x_loc, character_y_loc);
            }

            //character collision with explosive kong 2(decreases the health and sends the character back to the start)
            if (character_x_loc + 55 > 700 && character_x_loc < 700 + 61 && character_y_loc + 70 > enemy2_loc && character_y_loc < enemy2_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                character_x_loc = 340;
                character_y_loc = 420;
                myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, character_x_loc, character_y_loc);
            }

            //character collision with explosive kong 3(decreases the health and sends the character back to the start)
            if (character_x_loc + 55 > 1200 && character_x_loc < 1200 + 61 && character_y_loc + 70 > enemy3_loc && character_y_loc < enemy3_loc + 64){
                loseHealth(0xffc9c9c1, health, &game_on);
                health -= 1;
                for(int i = character_x_loc; i< character_x_loc+50; i++ ){
                    for(int j = character_y_loc; j < character_y_loc+70; j++){
                        myDrawPixel(i, j, 0xff000000);
                    }
                }
                character_x_loc = 340;
                character_y_loc = 420;
                myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, character_x_loc, character_y_loc);
            }
            if (health == 0 || time_left == 0){
                //game lost
                int lost = lostGame();
                if (lost == 0){
                    //end game
                    return 0;
                }
            }

        }
    }


    //method for collisions with objects that the character cant pass by
    int collision(int x_loc, int y_loc, int obj_x, int obj_y, int character_width, int character_height, int obj_width, int obj_height){
        if (x_loc + character_width > obj_x && x_loc < obj_x + obj_width && y_loc + character_height > obj_y && y_loc < obj_y + obj_height){
            return 1;
        }
            return 0;
    }


    //character move right method(stage 1)
    void move_right(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc - 5; i < x_loc; i++){
            for (int j = y_loc; j < y_loc + character_right.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_right.pixel_data, character_right.width, character_right.height, x_loc, y_loc);
    }

    //character move down method(stage 1)
    void move_down(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_front.width; i++){
            for (int j = y_loc - 5; j < y_loc ; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_front.pixel_data, character_front.width, character_front.height, x_loc, y_loc);
        
    }
    //character move left method(stage 1)
    void move_left(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc + 5; i < x_loc; i--){
            for (int j = y_loc; j < y_loc + character_left.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_left.pixel_data, character_left.width, character_left.height, x_loc, y_loc);
    }

    //character move up method(stage 1)
    void move_up(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_up.width; i++){
            for (int j = y_loc + 5 + character_up.height; j < y_loc + character_up.height; j--){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_up.pixel_data, character_up.width, character_up.height, x_loc, y_loc);
    }

    //---------------------------------------------------------------------------------------------------//

    //character move right method(stage 2)
    void move_right1(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc - 5; i < x_loc; i++){
            for (int j = y_loc; j < y_loc + character_right.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_rightb.pixel_data, character_rightb.width, character_rightb.height, x_loc, y_loc);
    }

    //character move down method(stage 2)
    void move_down1(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_front.width; i++){
            for (int j = y_loc - 5; j < y_loc ; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_frontb.pixel_data, character_frontb.width, character_frontb.height, x_loc, y_loc);
        
    }

    //character move left method(stage 2)
    void move_left1(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc + 5; i < x_loc; i--){
            for (int j = y_loc; j < y_loc + character_left.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_leftb.pixel_data, character_leftb.width, character_leftb.height, x_loc, y_loc);
    }

    //character move up method(stage 2)
    void move_up1(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_up.width; i++){
            for (int j = y_loc + 5 + character_up.height; j < y_loc + character_up.height; j--){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_upb.pixel_data, character_upb.width, character_upb.height, x_loc, y_loc);
    }

//-----------------------------------------------------------------------------

    //character move right method(stage 3)
    void move_right2(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc - 5; i < x_loc; i++){
            for (int j = y_loc; j < y_loc + character_right.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_rightg.pixel_data, character_rightg.width, character_rightg.height, x_loc, y_loc);
    }

    //character move down method(stage 3)
    void move_down2(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_front.width; i++){
            for (int j = y_loc - 5; j < y_loc ; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_frontg.pixel_data, character_frontg.width, character_frontg.height, x_loc, y_loc);
        
    }

    //character move left method(stage 3)
    void move_left2(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc + 5; i < x_loc; i--){
            for (int j = y_loc; j < y_loc + character_left.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_leftg.pixel_data, character_leftg.width, character_leftg.height, x_loc, y_loc);
    }

    //character move up method(stage 3)
    void move_up2(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_up.width; i++){
            for (int j = y_loc + 5 + character_up.height; j < y_loc + character_up.height; j--){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_upg.pixel_data, character_upg.width, character_upg.height, x_loc, y_loc);
    }


    //------------------------------------------------------------------------------------------------

    //character move right method(stage 4)
    void move_right3(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc - 5; i < x_loc; i++){
            for (int j = y_loc; j < y_loc + character_right.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_rightbl.pixel_data, character_rightbl.width, character_rightbl.height, x_loc, y_loc);
    }

    //character move down method(stage 4)
    void move_down3(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_front.width; i++){
            for (int j = y_loc - 5; j < y_loc ; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_frontbl.pixel_data, character_frontbl.width, character_frontbl.height, x_loc, y_loc);
        
    }

    //character move left method(stage 4)
    void move_left3(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc + 5; i < x_loc; i--){
            for (int j = y_loc; j < y_loc + character_left.height; j++){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_leftbl.pixel_data, character_leftbl.width, character_leftbl.height, x_loc, y_loc);
    }

    //character move up method(stage 4)
    void move_up3(int bgcolor, int x_loc, int y_loc){
        for (int i = x_loc; i < x_loc + character_up.width; i++){
            for (int j = y_loc + 5 + character_up.height; j < y_loc + character_up.height; j--){
                myDrawPixel(i, j, bgcolor);
            }
        }
        myDrawImage(character_upbl.pixel_data, character_upbl.width, character_upbl.height, x_loc, y_loc);
    }

    //lose health method(makes the character lose health)
    void loseHealth(int bgcolor, int health, int* game_on){
        if (health == 6){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 550, 760);
        }
        else if (health == 5){
            for (int i = 550; i < 550 + half_heart.width; i++){
                for (int j = 760; j < 760 + half_heart.height; j++){
                    myDrawPixel(i, j, bgcolor);
                }
            }
        }
        else if (health == 4){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 440, 760);
        }
        else if (health == 3){
            for (int i = 440; i < 440 + half_heart.width; i++){
                for (int j = 760; j < 760 + half_heart.height; j++){
                    myDrawPixel(i, j, bgcolor);
                }
            }
        }
        else if (health == 2){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 330, 760);
        }
        else if (health == 1){
            for (int i = 330; i < 330 + half_heart.width; i++){
                for (int j = 760; j < 760 + half_heart.height; j++){
                    myDrawPixel(i, j, bgcolor);
                }
            }
            //GAME OVER
            game_on = 0;
        }
    }
    
    //gain health method(makes the character gain health)
    void gainHealth(int bgcolor, int health){
        if (health == 5){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 550, 760);
        }
        else if (health == 4){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 550, 760);
        }
        else if (health == 3){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 440, 760);
        }
        else if (health == 2){
            myDrawImage(half_heart.pixel_data, half_heart.width, half_heart.height, 440, 760);
        }
        else if (health == 1){
            myDrawImage(full_heart.pixel_data, full_heart.width, full_heart.height, 330, 760);
        }
    }

    //pause method(pauses the game and draws the pause screen)
    int pause(){
        int pause_choice = 1;
        game_on = 0;
        myDrawImage(pause_c.pixel_data, pause_c.width, pause_c.height, 630, 250);
        //496, 620,
        drawString(910,450, "PLAY AGAIN",0x5f);
        drawString(910,500, "QUIT",0x0f);
        
        while (1){
            SNES(buttons);
            if ((buttons[6] == 0) && (pause_choice == 1)){
                drawString(910, 450, "PLAY AGAIN", 0x0f);
                drawString(910, 500, "QUIT", 0x5f);
                pause_choice = 2;
            }
            else if((buttons[5] == 0) && (pause_choice == 2)){
                drawString(910, 450, "PLAY AGAIN", 0x5f);
                drawString(910, 500, "QUIT", 0x0f);
                pause_choice = 1;
            }

            if ((buttons[9] == 0) && (pause_choice == 1)){
                //START
                for(int i = 0; i < 1920; i++) {
                    for (int j = 0; j < 1080; j++){
                        myDrawPixel(i, j, 0);
                    }
                }
                game_on = 1;
                int q = level1();
                if (q == 0){
                    return 0;
                }
            }
            else if ((buttons[9] == 0) && (pause_choice == 2)){
                //QUIT
                for(int i = 0; i < 1920; i++) {
                    for (int j = 0; j < 1080; j++){
                        myDrawPixel(i, j, 0);
                    }
                }
                int q = startScreen();
                //Exiting game if quitting in main menu
                if (q == 0){
                    return 0;
                }
            }
        }
    }

    //game lost(draws the game over scrren)
    int lostGame(){
        for(int i = 0; i < 1920; i++) {
            for (int j = 0; j < 1080; j++){
                myDrawPixel(i, j, 0);
            }
        }
        myDrawImage(lose_c.pixel_data, lose_c.width, lose_c.height, 500, 180);
        int lose_choice = 1;
        drawString(580,350, "PLAY AGAIN",0x5f);
        drawString(580,375, "QUIT",0x0f);
        while (1){
            //using snes to toggle between the options and select one
            SNES(buttons);
            if ((buttons[6] == 0) && (lose_choice == 1)){
                drawString(580, 350, "PLAY AGAIN", 0x0f);
                drawString(580, 375, "QUIT", 0x5f);
                lose_choice = 2;
            }
            else if((buttons[5] == 0) && (lose_choice == 2)){
                drawString(580, 350, "PLAY AGAIN", 0x5f);
                drawString(580, 375, "QUIT", 0x0f);
                lose_choice = 1;
            }

            if ((buttons[9] == 0) && (lose_choice == 1)){
                //START
                for(int i = 0; i < 1920; i++) {
                    for (int j = 0; j < 1080; j++){
                        myDrawPixel(i, j, 0);
                    }
                }
                game_on = 1;
                level1();
            }
            else if ((buttons[9] == 0) && (lose_choice == 2)){
                //QUIT
                for(int i = 0; i < 1920; i++) {
                    for (int j = 0; j < 1080; j++){
                        myDrawPixel(i, j, 0);
                    }
                }
                return 0;
            }
        }
    }

    int startScreen(){
        //title screen o the game

    //------ Title screen-------
    //drawing teh background
    for(int i = 0; i < 1920; i++) {
        for (int j = 0; j < 1080; j++){
            myDrawPixel(i, j, 0);
        }
    }
    //draws the donkey kong title image
    myDrawImage(DonkeyKongTitle.pixel_data, DonkeyKongTitle.width, DonkeyKongTitle.height, 700, 200);
    drawString(700, 476, "Created By Arian Safari & Aishan Irfan", 0x0f);

    drawString(700, 576, "START", 0x5f);
    drawString(700, 600, "QUIT", 0x0f);
       Init_GPIO();
    int choice = 1;

    
    while (1){
        //using snes to toggle between the options and select one
        SNES(buttons);
        if ((buttons[6] == 0) && (choice == 1)){
            drawString(700, 576, "START", 0x0f);
            drawString(700, 600, "QUIT", 0x5f);
            choice = 2;
        }
        else if((buttons[5] == 0) && (choice == 2)){
            drawString(700, 576, "START", 0x5f);
            drawString(700, 600, "QUIT", 0x0f);
            choice = 1;
        }

        if ((buttons[9] == 0) && (choice == 1)){
            //START
            for(int i = 0; i < 1920; i++) {
                for (int j = 0; j < 1080; j++){
                    myDrawPixel(i, j, 0);
                }
            }
            game_on = 1;
            int quit = level1();
            if (quit == 0){
                return 0;
            }
        }
        else if ((buttons[9] == 0) && (choice == 2)){
            //QUIT
            for(int i = 0; i < 1920; i++) {
                for (int j = 0; j < 1080; j++){
                    myDrawPixel(i, j, 0);
                }
            }
            return 0;
        }
    }
    }

   int youWin(char score_arr[]){
    //you win screen

    //draws the you win image on the scrren
    myDrawImage(youwin_c.pixel_data, youwin_c.width, youwin_c.height,660,180);
    while(1){
                //displays the final score
                myDrawImage(score_cb.pixel_data,score_cb.width,score_cb.height,700, 520);
                drawString(820, 545, score_arr, 0x0f);
                wait(6);
                //pressing any button the snes takes the game to the start screen
                SNES(buttons);
                for(int i = 1; i<= 12; i++){
                    if(buttons[i] == 0){
                        int q = startScreen();
                        if (q == 0){
                            //end game
                            return 0;

                        }
                    }
                }
    }
   }