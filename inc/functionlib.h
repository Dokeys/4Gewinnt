#ifndef _FUNCTIONLIB_H_
#define __FUNCTIONLIB_H_

#include <stdio.h>
#include <inttypes.h>

/* definitions */
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))


enum key_selection_t{
	UNKNOWN_KEY, ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT, RETURN_KEY 
};
typedef enum key_selection_t key_selection_t;


/* prototypes */
void disable_wait_for_return(); 
void reenable_wait_for_return(); 
void clear_window(); 
enum key_selection_t get_key_input();


#endif

