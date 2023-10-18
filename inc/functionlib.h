#ifndef __FUNCTIONLIB_H_
#define __FUNCTIONLIB_H_

#include <inttypes.h>
#include <stdio.h>

/* Defines ********************************************************************/

#define clear() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* Types **********************************************************************/

typedef enum key_selection_t {
    UNKNOWN_KEY,
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,
    RETURN_KEY
} key_selection_t;

/* Prototypes *****************************************************************/

extern void disable_wait_for_return();
extern void reenable_wait_for_return();
extern void clear_window();
extern key_selection_t get_key_input();

#endif
