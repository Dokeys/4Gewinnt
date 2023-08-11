#include <stdio.h>
#include <stdlib.h>

#include "functionlib.h"
#include "game.h"
#include "menu.h"

int main() {
    switch (menu()) {
        case PLAY:
            start_game();
            break;
        case OPTIONS:

            break;
        case QUIT_GAME:
            clear_window();
            exit(0);
            break;
        default:
            printf("Error:\tUnknown menu output.\n");
            break;
    }

    return 0;
}
