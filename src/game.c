/*
 * game.c
 *
 * Created on: 14.12.22
 * Author: Dominik Knoll
 *
 * Description:
 * Source file for the main game of the 4Wins game.
 *
 */
#include "game.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functionlib.h"

/* Defines ********************************************************************/

// TODO Check with different sizes
// TODO Make thins configurable
#define BOARD_SIZE_X 7
#define BOARD_SIZE_Y 6
#define CHIP_NUMBER_TO_WIN 4

/* Types **********************************************************************/

typedef enum field_placement_t {
    EMPTY,
    CHIP_PLAYER_1,
    CHIP_PLAYER_2
} field_placement_t;

/* Variables ******************************************************************/

field_placement_t board[BOARD_SIZE_X][BOARD_SIZE_Y] = {
    0};  // TODO set the array at the start of start_game() to zero.

/* Prototypes *****************************************************************/

static void show_title();
static void show_board();
static void show_placement_arrow(const uint8_t arrow_position,
                                 field_placement_t player);
static bool handle_key_input(uint8_t *arrow_position);
static bool set_chip(field_placement_t current_player,
                     const uint8_t arrow_position);
static void switch_player(field_placement_t *current_player);
static void check_field();
static void check_field_horizontal();
static void check_field_vertical();
static void check_field_diagonal();
static void show_winning_message(field_placement_t winner);

/* Public Functions ***********************************************************/

extern void start_game() {
    /* In this variable the chip positions is saved. Zero on the Y field is the
    lowes and zero on the X field is the left one.*/
    uint8_t selection_position = 0;
    field_placement_t current_player = CHIP_PLAYER_1;

    disable_wait_for_return();

    while (1) { /* main game loop */
        clear_window();
        show_title();
        show_placement_arrow(selection_position, current_player);
        show_board();
        check_field();
        if (handle_key_input(&selection_position)) {
            if (set_chip(current_player, selection_position)) {
                switch_player(&current_player);
            }
        }
    }
}

/* Private Functions **********************************************************/

static void show_title() {
    printf(
        " ╔═════════════════════════════════╗\n"
        " ║   4Wins - by Double Dynominik   ║\n"
        " ╚═════════════════════════════════╝\n");
}

static void show_board() {
    uint8_t x, y;

    gotoxy(0, 8);
    printf("\t__");
    for (x = 0; x < BOARD_SIZE_X; x++) printf("__");
    printf("__\n");

    for (y = BOARD_SIZE_Y - 1; y != 255; y--) {
        printf("\t _|");
        for (x = 0; x < BOARD_SIZE_X; x++) {
            switch (board[x][y]) {
                case EMPTY:
                    printf(" ");
                    break;
                case CHIP_PLAYER_1:
                    printf("O");
                    break;
                case CHIP_PLAYER_2:
                    printf("X");
                    break;
                default:
                    printf("Error:\tUnknown field placement!\n");
                    exit(1);
                    break;
            }
            printf("|");
        }
        printf("_\n");
    }
}

static void show_placement_arrow(const uint8_t arrow_position,
                                 field_placement_t player) {
    if (arrow_position >= BOARD_SIZE_X) {
        printf("Error:\twrong position!\n");
        exit(1);
    }

    gotoxy(0, 6);
    printf("           ");

    for (uint8_t i = 0; i < arrow_position; i++) printf("  ");

    switch (player) {
        case CHIP_PLAYER_1:
            printf("O\n");
            break;
        case CHIP_PLAYER_2:
            printf("X\n");
            break;
        default:
            break;
    }

    printf("           ");
    for (uint8_t i = 0; i < arrow_position; i++) printf("  ");
    printf("V\n");
}

// TODO add vim keybindings
static bool handle_key_input(uint8_t *arrow_position) {
    bool is_return_pressed = false;
    key_selection_t key_selection = UNKNOWN_KEY;

    key_selection = get_key_input();
    switch (key_selection) {
        case ARROW_LEFT:
            if (*arrow_position > 0) *arrow_position = *arrow_position - 1;
            break;
        case ARROW_RIGHT:
            if (*arrow_position < BOARD_SIZE_X - 1)
                *arrow_position = *arrow_position + 1;
            break;
        case RETURN_KEY:
            is_return_pressed = true;
            break;
        default:
            break;
    }
    return is_return_pressed;
}

static bool set_chip(field_placement_t current_player,
                     const uint8_t arrow_position) {
	bool is_chip_set = false; 
    uint8_t y, empty_field_y;

    for (y = 0; board[arrow_position][y] != EMPTY; y++)
	;
	empty_field_y = y;

   	if (empty_field_y < BOARD_SIZE_Y) {
		board[arrow_position][empty_field_y] = current_player;
       	is_chip_set = true;
   	}
	
    return is_chip_set;
}

static void switch_player(field_placement_t *current_player) {
    if (*current_player == CHIP_PLAYER_1)
        *current_player = CHIP_PLAYER_2;
    else
        *current_player = CHIP_PLAYER_1;
}

static void check_field() {
    check_field_horizontal();
    check_field_vertical();
    check_field_diagonal();
}

static void check_field_horizontal() {
    uint8_t chips_in_a_row = 0;
    field_placement_t chip_in_last_field = EMPTY, chip_in_current_field;

    for (uint8_t y = 0; y < BOARD_SIZE_Y; y++) {
        for (uint8_t x = 0; x < BOARD_SIZE_X; x++) {
            chip_in_current_field = *(*(board + x) + y);
            if ((chip_in_last_field == chip_in_current_field) &&
                (chip_in_current_field != EMPTY)) {
                chips_in_a_row++;
                if (chips_in_a_row >= CHIP_NUMBER_TO_WIN - 1)
                    show_winning_message(chip_in_current_field);
            } else {
                chips_in_a_row = 0;
            }
            chip_in_last_field = chip_in_current_field;
        }
    }
}

static void check_field_vertical() {
    uint8_t chips_in_a_row = 0;
    field_placement_t chip_in_last_field = EMPTY, chip_in_current_field;

    for (uint8_t x = 0; x < BOARD_SIZE_X; x++) {
        for (uint8_t y = 0; y < BOARD_SIZE_Y; y++) {
            chip_in_current_field = *(*(board + x) + y);
            if ((chip_in_last_field == chip_in_current_field) &&
                (chip_in_current_field != EMPTY)) {
                chips_in_a_row++;
                if (chips_in_a_row >= CHIP_NUMBER_TO_WIN - 1)
                    show_winning_message(chip_in_current_field);
            } else {
                chips_in_a_row = 0;
            }
            chip_in_last_field = chip_in_current_field;
        }
    }
}

static void check_field_diagonal() {
    uint8_t chips_in_a_row = 0;
    field_placement_t chip_in_current_field;

    for (uint8_t x = 0; x < BOARD_SIZE_X; x++) {
        for (uint8_t y = 0; y <= BOARD_SIZE_Y - CHIP_NUMBER_TO_WIN; y++) {
            if (*(*(board + x) + y) != EMPTY) {
                /* look for a winning row */
                chips_in_a_row = 1;
                chip_in_current_field = *(*(board + x) + y);
                for (uint8_t i = 0; i < CHIP_NUMBER_TO_WIN;
                     i++) {                         /* up and right */
                    if ((x + i + 1 <= BOARD_SIZE_X) /* check if placement check
                                                       is still in the field */
                        && (*(*(board + x + i + 1) + y + i + 1) ==
                            chip_in_current_field)) {
                        chips_in_a_row++;
                    } else {
                        break; /*leave for loop if there is a different chip */
                    }
                    if (chips_in_a_row == CHIP_NUMBER_TO_WIN)
                        show_winning_message(chip_in_current_field);
                }
                for (uint8_t i = 0; i < CHIP_NUMBER_TO_WIN;
                     i++) {                         /* up and left */
                    if ((x - i - 1 <= BOARD_SIZE_X) /* check if placement check
                                                       is still in the field */
                        && (*(*(board + x - i - 1) + y + i + 1) ==
                            chip_in_current_field)) {
                        chips_in_a_row++;
                    } else {
                        break; /*leave for loop if there is a different chip */
                    }
                    if (chips_in_a_row == CHIP_NUMBER_TO_WIN)
                        show_winning_message(chip_in_current_field);
                }
            }
        }
    }
}

static void show_winning_message(field_placement_t winner) {
    printf("\n\nPlayer %d wins!\n\n", winner);
    reenable_wait_for_return();
    exit(0);
}
