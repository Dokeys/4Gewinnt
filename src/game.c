#include "game.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functionlib.h"

/* Defines
 * ********************************************************+***********/

// TODO Check with different sizes
#define BOARD_SIZE_X 7
#define BOARD_SIZE_Y 6
#define CHIP_NUMBER_TO_WIN 4

/* Types
 * **********************************************************************/

typedef enum field_placement_t {
    EMPTY,
    CHIP_PLAYER_1,
    CHIP_PLAYER_2
} field_placement_t;

/* Prototypes
 * *****************************************************************/

static void show_title();
static void show_board(); /* ToDo why no typecast? */
static void show_placement_arrow(uint8_t position, field_placement_t player);
static bool handle_key_input(uint8_t *selection_position);
static bool set_chip(field_placement_t (*board)[BOARD_SIZE_Y],
                     field_placement_t current_player,
                     uint8_t selection_position);
static void switch_player(field_placement_t *current_player);
static void check_field(field_placement_t (*board)[BOARD_SIZE_Y]);
static void check_field_horizontal(field_placement_t (*board)[BOARD_SIZE_Y]);
static void check_field_vertical(field_placement_t (*board)[BOARD_SIZE_Y]);
static void check_field_diagonal(field_placement_t (*board)[BOARD_SIZE_Y]);
static void show_winning_message(field_placement_t winner);

/* Public Functions
 * ***********************************************************/

extern void start_game() {
    /* In this variable the chip positions is saved. Zero on the Y field is the
    lowes and zero on the X field is the left one.*/
    field_placement_t board[BOARD_SIZE_X][BOARD_SIZE_Y];
    memset(board, 0x00, sizeof(board));
    uint8_t selection_position = 0;
    field_placement_t current_player = CHIP_PLAYER_1;

    while (1) { /* main game loop */
        clear_window();
        show_title();
        show_placement_arrow(selection_position, current_player);
        show_board(&board);
        check_field(board);
        if (handle_key_input(&selection_position)) {
            if (set_chip(board, current_player, selection_position)) {
                switch_player(&current_player);
            }
        }
    }
}

/* Private Functions
 * **********************************************************/

static void show_title() {
    printf(
        " ╔═════════════════════════════════╗\n"
        " ║ 4 Gewinnt - by Double Dynominik ║\n"
        " ╚═════════════════════════════════╝\n");
}

static void show_board(field_placement_t (*board)[BOARD_SIZE_Y]) {
    gotoxy(0, 8);
    printf("\t_________________\n");
    for (uint8_t y = BOARD_SIZE_Y - 1; y != 255; y--) {
        printf("\t _|");
        for (uint8_t x = 0; x != BOARD_SIZE_X - 1; x++) {
            switch ((uint8_t) * (*(board + x) + y)) {
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
                    break;
            }
            printf("|");
        }
        printf("_\n");
    }
}

static void show_placement_arrow(uint8_t position, field_placement_t player) {
    if (position >= BOARD_SIZE_X) printf("Error:\twrong position!\n");

    gotoxy(0, 6);
    printf("           ");

    for (uint8_t i = 0; i < position; i++) printf("  ");

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

    for (uint8_t i = 0; i < position; i++) printf("  ");

    printf("V\n");
}

static bool handle_key_input(uint8_t *selection_position) {
    switch (get_key_input()) {
        case ARROW_LEFT:
            if (*selection_position > 0) (*selection_position)--;
            break;
        case ARROW_RIGHT:
            if (*selection_position < 5) (*selection_position)++;
            break;
        case RETURN_KEY:
            return true;
            break;
        default:
            break;
    }
    return false;
}

static bool set_chip(field_placement_t (*board)[BOARD_SIZE_Y],
                     field_placement_t current_player,
                     uint8_t selection_position) {
    uint8_t y;
    for (y = 0; *(*(board + selection_position /*x*/) + y) != EMPTY; y++)
        ;
    if (y < BOARD_SIZE_Y) {
        *(*(board + selection_position /*x*/) + y) = current_player;
        return true;
    }
    return false;
}

static void switch_player(field_placement_t *current_player) {
    if (*current_player == CHIP_PLAYER_1)
        *current_player = CHIP_PLAYER_2;
    else
        *current_player = CHIP_PLAYER_1;
}

static void check_field(field_placement_t (*board)[BOARD_SIZE_Y]) {
    check_field_horizontal(board);
    check_field_vertical(board);
    check_field_diagonal(board);
}

static void check_field_horizontal(field_placement_t (*board)[BOARD_SIZE_Y]) {
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

static void check_field_vertical(field_placement_t (*board)[BOARD_SIZE_Y]) {
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

static void check_field_diagonal(field_placement_t (*board)[BOARD_SIZE_Y]) {
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
    exit(1);
}
