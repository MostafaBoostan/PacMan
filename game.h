#include <stdio.h>

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

struct game{
    int user_id;
    int line, column;
    char **map;
    int score;
};

enum situation{
    GHOST,
    EMPTY,
    VERTICAL_WALL,
    HORIZONTAL_WALL,
    PILL,
    PAC_MAN,
    GHOST_MOVED // in ro gozashtam ta har harkat rooh ro yebar hesab konam va vaghti chandta rooh hast bug nakhore
};

enum move{
    UP,
    DOWN,
    LEFT,
    RHITE
};

void user_menu(struct user*, struct user*);
void start_game(struct user*, struct user*, struct game);