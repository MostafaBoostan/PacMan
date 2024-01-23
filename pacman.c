#include <stdio.h>
#include <unistd.h> // baraye tabe sleep va usleep
#include <conio.h> // baraye tabe getch va kbhit
#include <stdlib.h> // baraye tabe malloc estefade kardam
#include <string.h>

//tarif tamam rang ha baraye estefade dar barname
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"

struct user{
    int user_id;
    char user_name[200];
    char password[200];
    int level;
    int last_game;
    struct user *pnext;
};

struct user* load_user();
void first_menu(struct user*);
void sign_in(struct user*);
struct user* sign_up(struct user*);
void user_menu(struct user*, struct user*);
void delete_acc(struct user*, struct user*);

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
////////////////////////////////////////////////////////////////////////////////////////////////////////
            break;
        case 2:
            if(ptemp->last_game == 0){
                system("cls || clear");
                printf("\n"RED"You have no unfinished game."RESET);
                usleep(3000000);
                user_menu(ptemp, phead);
            }
////////////////////////////////////////////////////////////////////////////////////////////////////////
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

