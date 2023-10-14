/*
 * main.c
 *
 * Created on: 14.12.22
 * Author: Dominik Knoll
 *
 * Description:
 * Main file for the 4Wins game.
 *
 */
#include "functionlib.h"
#include "game.h"
#include "menu.h"

#include <stdio.h>

int main() {
    menu_selection_t menu_selection;

    menu_selection = menu();

    switch (menu_selection) {
        case PLAY:
            start_game();
            break;
        case OPTIONS:
            printf("Options not implemented jet :-(\n");
            break;
        case QUIT_GAME:
            // TODO Implement random funny bye sentences feature.
            printf("See you soon, raccoon :-)\n");
            break;
        default:
            printf("Error:\tUnknown menu output.\n");
            return 1;
            break;
    }
    return 0;
}
