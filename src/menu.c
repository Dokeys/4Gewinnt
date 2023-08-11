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

/* Prototypes
 * *****************************************************************/

static void show_menu(uint8_t selection);
static bool handle_key_input(uint8_t *selection_position);

/* Public Functions
 * ***********************************************************/

enum menu_selection_t menu() {
    uint8_t selection_position = 0;

    disable_wait_for_return();
    while (1) {
        clear_window();
        show_menu(selection_position);
        if (handle_key_input(&selection_position)) {
            switch (selection_position) {
                case 0:
                    return PLAY;
                    break;
                case 1:
                    return OPTIONS;
                    break;
                case 2:
                    return QUIT_GAME;
                    break;
            }
        }
    }

    reenable_wait_for_return();
    clear_window();
}

/* Private Functions
 * **********************************************************/

static void show_menu(uint8_t selection) {
    printf(
        " ╔═════════════════════════════════╗\n"
        " ║ 4 Gewinnt - by Double Dynominik ║\n"
        " ╚═════════════════════════════════╝\n");
    gotoxy(0, 6);
    printf(
        "\t\tPlay\n"
        "\t\tOptions\n"
        "\t\tExit\n");

    gotoxy(13, 6 + selection);
    printf("->");
}

static bool handle_key_input(uint8_t *selection_position) {
    switch (get_key_input()) {
        case ARROW_UP:
            if (*selection_position > 0) (*selection_position)--;
            break;
        case ARROW_DOWN:
            if (*selection_position < 2) (*selection_position)++;
            break;
        case RETURN_KEY:
            return true;
            break;
        default:
            break;
    }
    return false;
}
