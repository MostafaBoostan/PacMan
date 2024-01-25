#include <stdio.h>
#include "game.h"
#include <conio.h>  // baraye tabe getch va kbhit
#include <unistd.h> // baraye tabe sleep va usleep
#include <time.h> //baraye tabe random estefade mishavad
#include <stdlib.h> // baraye tabe malloc estefade kardam
#include <string.h>

void start_game(struct user* ptemp, struct user* phead, struct game information_game){
    struct user* ptemp_write;
    FILE *map_file, *user_file;
    char choise;
    int i, j, *random_move_ghost, ghost_number = 0 , *flag, temp, pill_number = 0, pac_man_flag = 1; // flag baraye in bekar rafe ke agar roohi roye ghors bere ghors az bey nare ve betoonim dobare baresh gardoonim
    char file_name[200];
    
    user_file = fopen("user.bin", "wb");

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
        printf(BLUE"\n\nClick the Escape button to exit.");
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
                                    for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                        fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                    }
                                    fclose(user_file);
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
                                    for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                        fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                    }
                                    fclose(user_file);
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
                                    for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                        fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                    }
                                    fclose(user_file);
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
                                    for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                        fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                    }
                                    fclose(user_file);
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
            if(choise == -32){ // dekme vizhe niaze yani ba zadan jahat aval -32 vared mishe ke test kardam addadesho badesh jahat
                choise = getch();
                if(choise == 80){ //DOWN
                    switch(information_game.map[i+1][j]){
                        case HORIZONTAL_WALL:
                        case VERTICAL_WALL:
                            break;
                        case GHOST:
                        case GHOST_MOVED:
                            ptemp->level --;
                            for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                            }
                            fclose(user_file);
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
                                for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                    fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                }
                                fclose(user_file);
                                system("cls || clear");
                                printf(GREEN"game is win."RESET);  
                                usleep(3000000);
                                user_menu(ptemp, phead); 
                            }
                            break;
                    }
                }
                else if(choise == 72){ //UP
                    switch(information_game.map[i-1][j]){
                        case HORIZONTAL_WALL:
                        case VERTICAL_WALL:
                            break;
                        case GHOST:
                        case GHOST_MOVED:
                            ptemp->level --;
                            for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                            }
                            fclose(user_file);
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
                                for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                    fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                }
                                fclose(user_file);
                                system("cls || clear");
                                printf(GREEN"game is win."RESET);  
                                usleep(3000000);
                                user_menu(ptemp, phead); 
                            }
                            break;
                    }
                }
                else if(choise == 75){ //LEFT
                    switch(information_game.map[i][j-1]){
                        case HORIZONTAL_WALL:
                        case VERTICAL_WALL:
                            break;
                        case GHOST:
                        case GHOST_MOVED:
                            ptemp->level --;
                            for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                            }
                            fclose(user_file);
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
                                for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                    fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                }
                                fclose(user_file);
                                system("cls || clear");
                                printf(GREEN"game is win."RESET);  
                                usleep(3000000);
                                user_menu(ptemp, phead); 
                            }
                            break;
                    }
                }
                else if(choise == 77){ //RIGHT
                    switch(information_game.map[i][j+1]){
                        case HORIZONTAL_WALL:
                        case VERTICAL_WALL:
                            break;
                        case GHOST:
                        case GHOST_MOVED:
                            ptemp->level --;
                            for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                            }
                            fclose(user_file);
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
                                for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                                    fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                                }
                                fclose(user_file);
                                system("cls || clear");
                                printf(GREEN"game is win."RESET);  
                                usleep(3000000);
                                user_menu(ptemp, phead); 
                            }
                            break;
                    }
                }
            }
            else if(choise == 27){

                //tolid esm file
                strcpy(file_name, ptemp->user_name);
                strcat(file_name, ".txt");
    
                map_file = fopen(file_name, "w");
                fprintf(map_file, "%d %d", information_game.line, information_game.column);
                for(i = 0; i < information_game.line; i++){
                    fprintf(map_file,"\n");
                    for(j = 0; j < information_game.column; j++){
                        fprintf(map_file, "%d", information_game.map[i][j]);
                    }
                }
                fprintf(map_file, "\n%d", information_game.score);
                fclose(map_file);
                ptemp->last_game = 1;
                for(ptemp_write = phead; ptemp_write != NULL ; ptemp_write = ptemp_write->pnext){
                    fwrite(ptemp_write, sizeof(struct user), 1, user_file);
                }
                fclose(user_file);
                system("cls || clear");
                printf(GREEN"Your game has been successfully saved."RESET);  
                usleep(3000000);
                user_menu(ptemp, phead);
            }
        }
    }
}
