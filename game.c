#include <stdio.h>
#include "game.h"
#include <conio.h>  // baraye tabe getch va kbhit
#include <unistd.h> // baraye tabe sleep va usleep
#include <time.h> //baraye tabe random estefade mishavad
#include <stdlib.h> // baraye tabe malloc estefade kardam


void start_game(struct user* ptemp, struct user* phead, struct game information_game){
    
    char choise;
    int i, j, *random_move_ghost, ghost_number = 0 , *flag, temp, pill_number = 0, pac_man_flag = 1; // flag baraye in bekar rafe ke agar roohi roye ghors bere ghors az bey nare ve betoonim dobare baresh gardoonim
    // baraye harkat rooh ha
    for(i = 0; i < information_game.line; i++){
        for(j = 0; j < information_game.column; j++){
            if(information_game.map[i][j] == GHOST){
                ghost_number++;
            }
        }
    }   
    random_move_ghost = (int*) malloc(ghost_number * sizeof(int));
    flag = (int*) malloc(ghost_number * sizeof(int));
    for(temp = 0; temp < ghost_number; temp++){
        flag[temp] = 0;
    }

    //baraye harkat pacman va pill ha
    for(i = 0; i < information_game.line; i++){
        for(j = 0; j < information_game.column; j++){
            if(information_game.map[i][j] == PILL){
                pill_number++;
            }
        }
    }   

    while(1){
        system("cls || clear");
        printf(YELLOW"* * * * * * * * * * * * * * * * * * * *"RESET"\n");
        printf(YELLOW"          "MAGENTA"User information"RESET"           "RESET"\n\n");
        printf("          "GREEN"User id > %d \n"RESET, ptemp->user_id);
        printf("        "GREEN"User name > %s \n"RESET, ptemp->user_name);
        printf("       "GREEN"User level > %d \n"RESET, ptemp->level);
        printf("       "BLUE"User score > %d \n\n"RESET, information_game.score);
        for(i = 0; i < information_game.line; i++){
            printf("\n");
            for(j = 0; j < information_game.column; j++){
                switch(information_game.map[i][j]){
                    case GHOST_MOVED:
                    case GHOST:
                        information_game.map[i][j] = GHOST;
                        printf(MAGENTA"G"RESET);
                        break;
                    case EMPTY:
                        printf(" ");
                        break;
                    case VERTICAL_WALL:
                        printf(YELLOW"|"RESET);
                        break;
                    case HORIZONTAL_WALL:
                        printf(YELLOW"-"RESET);
                        break;
                    case PILL:
                        printf(RED"P"RESET);
                        break;
                    case PAC_MAN:
                        printf(GREEN"@"RESET);
                        break;
                    default:
                        system("cls || clear");
                        printf(RED"The map has not been loaded successfully."RESET);
                        usleep(3000000);

                }
            }
        }
        usleep(1000000);
        ghost_number = temp;
        for(i = 0; i < information_game.line; i++){
            for(j = 0; j < information_game.column; j++){
                if(information_game.map[i][j] == GHOST){
                    random_move_ghost[ghost_number] = rand() % 4;
                    switch(random_move_ghost[ghost_number]){
                        case UP:
                            switch(information_game.map[i-1][j]){
                                case GHOST:
                                case GHOST_MOVED:
                                case HORIZONTAL_WALL:
                                case VERTICAL_WALL:
                                    break;
                                case PAC_MAN:
                                    ptemp->level --;
                                    system("cls || clear");
                                    printf(RED"game over."RESET);  
                                    usleep(3000000);
                                    free(random_move_ghost);
                                    free(flag);
                                    user_menu(ptemp, phead);   
                                case EMPTY:
                                    information_game.map[i-1][j] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 0;
                                    break;
                                case PILL:
                                    information_game.map[i-1][j] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 1;
                                    break;                      
                            }
                            break;
                        case DOWN:
                            switch(information_game.map[i+1][j]){
                                case GHOST:
                                case GHOST_MOVED:
                                case HORIZONTAL_WALL:
                                case VERTICAL_WALL:
                                    break;
                                case PAC_MAN:
                                    ptemp->level --;
                                    system("cls || clear");
                                    printf(RED"game over."RESET);  
                                    usleep(3000000);
                                    free(random_move_ghost);
                                    free(flag);
                                    user_menu(ptemp, phead);   
                                case EMPTY:
                                    information_game.map[i+1][j] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 0;
                                    break;
                                case PILL:
                                    information_game.map[i+1][j] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 1;
                                    break;                      
                            }
                            break;
                        case LEFT:
                            switch(information_game.map[i][j-1]){
                                case GHOST:
                                case GHOST_MOVED:
                                case HORIZONTAL_WALL:
                                case VERTICAL_WALL:
                                    break;
                                case PAC_MAN:
                                    ptemp->level --;
                                    system("cls || clear");
                                    printf(RED"game over."RESET);  
                                    usleep(3000000);
                                    free(random_move_ghost);
                                    free(flag);
                                    user_menu(ptemp, phead);   
                                case EMPTY:
                                    information_game.map[i][j-1] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 0;
                                    break;
                                case PILL:
                                    information_game.map[i][j-1] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 1;
                                    break;                      
                            }
                            break;
                        case RHITE:
                            switch(information_game.map[i][j+1]){
                                case GHOST:
                                case GHOST_MOVED:
                                case HORIZONTAL_WALL:
                                case VERTICAL_WALL:
                                    break;
                                case PAC_MAN:
                                    ptemp->level --;
                                    system("cls || clear");
                                    printf(RED"game over."RESET);  
                                    usleep(3000000);
                                    free(random_move_ghost);
                                    free(flag);
                                    user_menu(ptemp, phead);   
                                case EMPTY:
                                    information_game.map[i][j+1] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 0;
                                    break;
                                case PILL:
                                    information_game.map[i][j+1] = GHOST_MOVED;
                                    if(flag[ghost_number] == 1){
                                        information_game.map[i][j] = PILL;
                                    } 
                                    else{
                                        information_game.map[i][j] = EMPTY;
                                    }    
                                    flag[ghost_number] = 1;
                                    break;                      
                            }
                            break;
                        default:
                            system("cls || clear");
                            printf(RED"The map has not been loaded successfully."RESET);
                            usleep(3000000);

                    }
                    ghost_number --;
                }
            }
        } 
        for(i = 0; i < information_game.line && pac_man_flag; i++){
            for(j = 0; j < information_game.column; j++){
                if(information_game.map[i][j] == PAC_MAN){
                    pac_man_flag = 0;
                    break;
                }
            }
        }
        pac_man_flag = 1;
        i--;
        if(_kbhit()){
            choise = getch();
            if(choise == 's'){ //DOWN
                switch(information_game.map[i+1][j]){
                    case HORIZONTAL_WALL:
                    case VERTICAL_WALL:
                        break;
                    case GHOST:
                    case GHOST_MOVED:
                        ptemp->level --;
                        system("cls || clear");
                        printf(RED"game over."RESET);  
                        usleep(3000000);
                        user_menu(ptemp, phead); 
                        break;
                    case EMPTY:
                        information_game.map[i+1][j] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        break;
                    case PILL:
                        information_game.map[i+1][j] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        information_game.score ++;
                        if(information_game.score == pill_number){
                            ptemp->level += 3;
                            system("cls || clear");
                            printf(GREEN"game is win."RESET);  
                            usleep(3000000);
                            user_menu(ptemp, phead); 
                        }
                        break;
                }
            }
            else if(choise == 'w'){ //UP
                switch(information_game.map[i-1][j]){
                    case HORIZONTAL_WALL:
                    case VERTICAL_WALL:
                        break;
                    case GHOST:
                    case GHOST_MOVED:
                        ptemp->level --;
                        system("cls || clear");
                        printf(RED"game over."RESET);  
                        usleep(3000000);
                        user_menu(ptemp, phead); 
                        break;
                    case EMPTY:
                        information_game.map[i-1][j] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        break;
                    case PILL:
                        information_game.map[i-1][j] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        information_game.score ++;
                        if(information_game.score == pill_number){
                            ptemp->level += 3;
                            system("cls || clear");
                            printf(GREEN"game is win."RESET);  
                            usleep(3000000);
                            user_menu(ptemp, phead); 
                        }
                        break;
                }
            }
            else if(choise == 'a'){ //LEFT
                switch(information_game.map[i][j-1]){
                    case HORIZONTAL_WALL:
                    case VERTICAL_WALL:
                        break;
                    case GHOST:
                    case GHOST_MOVED:
                        ptemp->level --;
                        system("cls || clear");
                        printf(RED"game over."RESET);  
                        usleep(3000000);
                        user_menu(ptemp, phead); 
                        break;
                    case EMPTY:
                        information_game.map[i][j-1] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        break;
                    case PILL:
                        information_game.map[i][j-1] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        information_game.score ++;
                        if(information_game.score == pill_number){
                            ptemp->level += 3;
                            system("cls || clear");
                            printf(GREEN"game is win."RESET);  
                            usleep(3000000);
                            user_menu(ptemp, phead); 
                        }
                        break;
                }
            }
            else if(choise == 'd'){ //RIGHT
                switch(information_game.map[i][j+1]){
                    case HORIZONTAL_WALL:
                    case VERTICAL_WALL:
                        break;
                    case GHOST:
                    case GHOST_MOVED:
                        ptemp->level --;
                        system("cls || clear");
                        printf(RED"game over."RESET);  
                        usleep(3000000);
                        user_menu(ptemp, phead); 
                        break;
                    case EMPTY:
                        information_game.map[i][j+1] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        break;
                    case PILL:
                        information_game.map[i][j+1] = PAC_MAN;
                        information_game.map[i][j] = EMPTY;
                        information_game.score ++;
                        if(information_game.score == pill_number){
                            ptemp->level += 3;
                            system("cls || clear");
                            printf(GREEN"game is win."RESET);  
                            usleep(3000000);
                            user_menu(ptemp, phead); 
                        }
                        break;
                }
            }
        }
    }
}
