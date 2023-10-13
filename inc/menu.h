/*
 * menu.h
 *
 * Created on: 14.12.22
 * Author: Dominik Knoll
 *
 * Description:
 * Header file for the main menu of 4Wins game.
 *
 */
#ifndef __MENU_H_
#define __MENU_H_

/* Types **********************************************************************/

typedef enum menu_selection_t {
    PLAY,
    OPTIONS,
    QUIT_GAME,
} menu_selection_t;

/* Prototypes *****************************************************************/

/**
 * Shows the start menu and handles the key inputs until a menu entry is chosen.
 *
 * @return The chosen menu entry.
 */
extern menu_selection_t menu();

#endif
