#ifndef __MENU_H_
#define __MENU_H_

/* Types
 * **********************************************************************/

typedef enum menu_selection_t {
    PLAY,
    OPTIONS,
    QUIT_GAME,
    MOVE_CURSOR
} menu_selection_t;

/* Prototypes
 * *****************************************************************/

menu_selection_t menu();

#endif
