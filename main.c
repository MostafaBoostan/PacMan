#include <stdio.h>
#include <unistd.h> // baraye tabe sleep va usleep
#include <conio.h> // baraye tabe getch va kbhit
#include <stdlib.h> // baraye tabe malloc estefade kardam
#include <string.h>
#include "game.h"

struct user* load_user();
void first_menu(struct user*);
void sign_in(struct user*);
struct user* sign_up(struct user*);
void delete_acc(struct user*, struct user*);
void load_map_new(struct user*, struct user*);
void load_map_restore(struct user*, struct user*);

int main(){
    struct user *phead;
    phead = load_user();
    first_menu(phead);
}

//load kardan user haye mojood dar bazi dar link list baraye estefade dar endame
struct user* load_user(){
    struct user *phead = NULL, *ptemp, *pnew;
    FILE *user_file;
    user_file = fopen("user.bin", "rb");
    if(user_file == NULL){
        //NULL ra be onfan phead bar migardoone
        return NULL;
    }
    pnew = (struct user*) malloc(sizeof(struct user));
    while(fread(pnew, sizeof(struct user), 1, user_file) > 0){
        pnew->pnext = NULL;
        if(phead == NULL){
            phead = ptemp = pnew;
        }
        ptemp = pnew;
        pnew = (struct user*) malloc(sizeof(struct user));
        ptemp->pnext = pnew;
    }
    ptemp->pnext = NULL;
    free(pnew);
    fclose(user_file);
    return phead;
}

//neshun dadan menu avalie baraye vorod va sapt nam va edame barname
void first_menu(struct user* phead){
    struct user *ptemp;
    int choise;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"   "MAGENTA"Welcome to pac man game"RESET"   "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Sign in (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Register (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"             "GREEN"Exit (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your choise: "RESET);
    scanf("%d",& choise);
    switch(choise){
        case 1:
            sign_in(phead);
            break;
        case 2:
            phead = sign_up(phead);
            for(ptemp = phead; ptemp->pnext != NULL; ptemp = ptemp->pnext);
            user_menu(ptemp, phead);
            break;
        case 3:
            exit(0);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            first_menu(phead);
    }
}

//register kardan dar game
struct user* sign_up(struct user *phead){
    FILE *user_file;
    char user_name[200], password[200];
    struct user *ptemp, *pnew;
    int choise, user_id = 2;

    //kamel kardan user name
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"           "MAGENTA"Sing up"RESET"           "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "RED"User name <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Password <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your user name: "RESET);
    scanf("%s", user_name);

    //shart tekrari naboodan user name
    for(ptemp = phead; ptemp != NULL; ptemp = ptemp->pnext){
        if(strcmp(ptemp->user_name, user_name) == 0){
            break;
        }
    }
    if(ptemp != NULL){
        system("cls || clear");
        printf("\n"RED"Username has already been entered."RESET);
        usleep(3000000);
        sign_up(phead);
    }

    //kamel kardan password
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"           "MAGENTA"Sing up"RESET"           "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"User name <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "RED"Password <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your password: "RESET);
    scanf("%s", password);

    //entekhab gozine
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"           "MAGENTA"Sing up"RESET"           "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"        "GREEN"Register (1"RESET"          "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"            "GREEN"Back (2"RESET"          "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your password: "RESET);
    scanf("%d",& choise);

    switch(choise){
        case 1:
            user_file = fopen("user.bin", "wb");
            pnew = (struct user*) malloc(sizeof(struct user));
            strcpy(pnew->user_name, user_name);
            strcpy(pnew->password, password);
            pnew->level = 0;
            pnew->last_game = 0;
            pnew->pnext = NULL;
            if(phead == NULL){
                pnew->user_id = 1;
                phead = pnew;
                fwrite(phead, sizeof(struct user), 1, user_file);
                fclose(user_file);

                system("cls || clear");
                printf("\n"GREEN"Your registration was successful."RESET);
                usleep(3000000);

                return phead;
            }
            for(ptemp = phead; ptemp->pnext != NULL; ptemp = ptemp->pnext){
                user_id ++;
            }
            pnew->user_id = user_id;
            ptemp->pnext = pnew;
            for(ptemp = phead; ptemp != NULL ; ptemp = ptemp->pnext){
                fwrite(ptemp, sizeof(struct user), 1, user_file);
            }
            fclose(user_file);
            system("cls || clear");
            printf("\n"GREEN"Your registration was successful."RESET);
            usleep(3000000);


            return phead;
            break;
        case 2:
            first_menu(phead);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            first_menu(phead);
    }


}

//sing in kardan dar game
void sign_in(struct user *phead){
    char user_name[200], password[200];
    struct user *ptemp;

    //kamel kardan user name
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"           "MAGENTA"Sing in"RESET"           "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "RED"User name <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Password <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your user name: "RESET);
    scanf("%s", user_name);

    //kamel kardan password
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"           "MAGENTA"Sing in"RESET"           "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"User name <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "RED"Password <"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your password: "RESET);
    scanf("%s", password);

    for(ptemp = phead; ptemp != NULL; ptemp = ptemp->pnext){
        if(strcmp(ptemp->user_name, user_name) == 0){
            if(strcmp(ptemp->password, password) == 0){
                break;
            }
        }
    }
    if(ptemp == NULL){
        system("cls || clear");
        printf("\n"RED"The username or password is incorrect."RESET);
        usleep(3000000);
        first_menu(phead);
    }
    else{
        user_menu(ptemp, phead);
    }
}

//menu user ghabl az shoro bazi
void user_menu(struct user* ptemp, struct user* phead){
    int choise;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"          "MAGENTA"User information"RESET"           "RESET"\n\n");
    printf("          "GREEN"User id > %d \n"RESET, ptemp->user_id);
    printf("        "GREEN"User name > %s \n"RESET, ptemp->user_name);
    printf("       "GREEN"User level > %d \n"RESET, ptemp->level);
    if(ptemp->last_game == 1){
        printf("        "GREEN"Last game > Incompleted \n"RESET);
    }
    else{
        printf("        "GREEN"Last game > Finished \n\n"RESET);
    }
    printf("             "RED"New game (1\n"RESET);
    printf("              "RED"Restore (2\n"RESET);
    printf("              "RED"Log out (3\n"RESET);
    printf("       "RED"Delete account (4\n"RESET);
    printf(YELLOW"* * * * * * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your password: "RESET);
    scanf("%d",& choise);

    switch(choise){
        case 1:
            ptemp->last_game = 0;
            load_map_new(ptemp, phead);
            break;
        case 2:
            if(ptemp->last_game == 0){
                system("cls || clear");
                printf("\n"RED"You have no unfinished game."RESET);
                usleep(3000000);
                user_menu(ptemp, phead);
            }
            load_map_restore(ptemp, phead);
            break;
        case 3:
            system("cls || clear");
            printf("\n"GREEN"You are logged out."RESET);
            usleep(3000000);
            first_menu(phead);
            break;
        case 4:
            delete_acc(ptemp, phead);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            user_menu(ptemp, phead);

    }
    
}

//delete account from linklist
void delete_acc(struct user* pdelete, struct user* phead){
    FILE *user_file;
    struct user* ptemp;
    user_file = fopen("user.bin", "wb");
    if(pdelete == phead){
        phead = phead->pnext;
        free(pdelete);
        for(ptemp = phead; ptemp != NULL ; ptemp = ptemp->pnext){
            fwrite(ptemp, sizeof(struct user), 1, user_file);
        }
        fclose(user_file);
        system("cls || clear");
        printf("\n"GREEN"Your account has been successfully deleted."RESET);
        usleep(3000000);
        first_menu(phead);
    }
    for(ptemp = phead; ptemp->pnext != pdelete; ptemp = ptemp->pnext);
    ptemp->pnext = pdelete->pnext;
    free(pdelete);
    for(ptemp = phead; ptemp != NULL ; ptemp = ptemp->pnext){
        fwrite(ptemp, sizeof(struct user), 1, user_file);
    }
    fclose(user_file);
    system("cls || clear");
    printf("\n"GREEN"Your account has been successfully deleted."RESET);
    usleep(3000000);
    first_menu(phead);
}

//load kardan map baraye new game
void load_map_new(struct user* ptemp, struct user* phead){
    struct game new_game;
    int choise, i, j;
    FILE *map_file;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"    "MAGENTA"Choose your game level"RESET"   "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"             "GREEN"Easy (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"           "GREEN"Medium (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"             "GREEN"Hard (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"             "GREEN"Back (4"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your choise: "RESET);
    scanf("%d",& choise);
    switch(choise){
        case 1:
            map_file = fopen("PAC-MAN-MAPS\\mapA.txt", "r");
            break;
        case 2:
            map_file = fopen("PAC-MAN-MAPS\\mapB.txt", "r");
            break;
        case 3:
            map_file = fopen("PAC-MAN-MAPS\\mapC.txt", "r");
            break;
        case 4:
            user_menu(ptemp, phead);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            load_map_new(ptemp, phead);
    }
    new_game.user_id = ptemp->user_id;
    new_game.score = 0;
    fscanf(map_file, "%d %d",& new_game.line,& new_game.column);
    new_game.map = (char **) malloc(new_game.line * sizeof(char*));
    for(i = 0; i < new_game.line; i++){
        fscanf(map_file,"\n");
        new_game.map[i] = (char*) malloc(new_game.column * sizeof(char));
        for(j = 0; j < new_game.column; j++){
            fscanf(map_file, "%c",& new_game.map[i][j]);
            new_game.map[i][j] -= '0';
        }
    }
    fclose(map_file);
    start_game(ptemp, phead, new_game);
}

//load kardan map baraye restore
void load_map_restore(struct user* ptemp, struct user* phead){
    struct game restore_game;
    // temp va mghloob baraye tabdil add id be character hast ke sakhte beshe baraye esm file
    int i , j;
    char file_name[200];
    FILE *map_file;

    //tolid esm file
    strcpy(file_name, ptemp->user_name);
    strcat(file_name, ".txt");

    map_file = fopen(file_name, "r");

    restore_game.user_id = ptemp->user_id;
    fscanf(map_file, "%d %d",& restore_game.line,& restore_game.column);
    restore_game.map = (char **) malloc(restore_game.line * sizeof(char*));
    for(i = 0; i < restore_game.line; i++){
        fscanf(map_file,"\n");
        restore_game.map[i] = (char*) malloc(restore_game.column * sizeof(char));
        for(j = 0; j < restore_game.column; j++){
            fscanf(map_file, "%c",& restore_game.map[i][j]);
            restore_game.map[i][j] -= '0';
        }
    }
    fscanf(map_file,"\n%d",& restore_game.score);
    fclose(map_file);
    start_game(ptemp, phead, restore_game);
}