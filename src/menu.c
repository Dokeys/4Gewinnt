/*
 * menu.c
 *
 * Created on: 14.12.22
 * Author: Dominik Knoll
 *
 * Description:
 * Source file for the main menu of the 4Wins game.
 *
 */
#include "menu.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "functionlib.h"
#ifdef __linux__     /* Linux includes */
#include <termios.h> /* termios, TCSANOW, ECHO, ICANON */
#include <unistd.h>  /* STDIN_FILENO */
#endif
#ifdef _WIN32 /* Windows includes */
#include <conio.h>
#endif

/* Defines ********************************************************************/
#define MENU_ENTRIES 3

/* Prototypes *****************************************************************/

static void show_menu(const menu_selection_t selection_position);
static bool handle_key_input(menu_selection_t *selection_position);

/* Public Functions ***********************************************************/

extern menu_selection_t menu() {
    menu_selection_t selection_position = PLAY;
    bool is_return_pressed = false;

    disable_wait_for_return();

    clear_window();
    show_menu(selection_position);

    do {
        is_return_pressed = handle_key_input(&selection_position);
        clear_window();
        show_menu(selection_position);
    } while (!is_return_pressed);

    clear_window();
    reenable_wait_for_return();
    return selection_position;
}

/* Private Functions **********************************************************/

/**
 * Shows the menu with the arrow depending on the \p selection_position.
 *
 * @param[in] selection_position The selection position where the arrow shout
 * appear.
 */
static void show_menu(const menu_selection_t selection_position) {
    gotoxy(0, 0);
    printf(
        " ╔═════════════════════════════════╗\n"
        " ║ 4 Gewinnt - by Double Dynominik ║\n"
        " ╚═════════════════════════════════╝\n");
    gotoxy(0, 6);
    printf(
        "\t\tPlay\n"
        "\t\tOptions\n"
        "\t\tExit\n");

    gotoxy(13, 6 + selection_position);
    printf("->");
}

/**
 * Reads key input and changes the menu selection position.
 * This function blocks the blocks the program until a key is pressed.
 *
 * @param[in, out] selection_position Input the current selection position in
 * the menu. \p selection_position will be changed from this function depending
 * on the key input.
 *
 * @return true when return is pressed and false when not.
 */
static bool handle_key_input(menu_selection_t *selection_position) {
    bool is_return_pressed = false;
    key_selection_t key_selection = UNKNOWN_KEY;

    key_selection = get_key_input();
    switch (key_selection) {
        case ARROW_UP:
            if (*selection_position > 0)
                *selection_position = *selection_position - 1;
            break;
        case ARROW_DOWN:
            if (*selection_position < MENU_ENTRIES - 1)
                *selection_position = *selection_position + 1;
            break;
        case RETURN_KEY:
            is_return_pressed = true;
            break;
        default:
            printf("Unhanded input!\n");
            break;
    }

    return is_return_pressed;
}
