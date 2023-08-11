#include "functionlib.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__     /* Linux includes */
#include <termios.h> /* termios, TCSANOW, ECHO, ICANON */
#include <unistd.h>  /* STDIN_FILENO */
#endif
#ifdef _WIN32 /* Windows includes */
#include <conio.h>
#endif

/* Public Functions ***********************************************************/

extern void disable_wait_for_return() {
  static struct termios oldt, newt;

  printf("\e[?25l"); /* hide the cursor */

  /*tcgetattr gets the parameters of the current terminal STDIN_FILENO will tell
   * tcgetattr that it should write the settings of stdin to oldt*/
  tcgetattr(STDIN_FILENO, &oldt);
  /*now the settings will be copied*/
  newt = oldt;

  /*ICANON normally takes care that one line at a time will be processed that
   * means it will return if it sees a "\n" or an EOF or an EOL*/
  newt.c_lflag &= ~(ICANON);

  /*Those new settings will be set to STDIN TCSANOW tells tcsetattr to change
   * attributes immediately. */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

extern void reenable_wait_for_return() {
  static struct termios oldt;

  printf("\e[?25h"); /* re-enable the cursor */
  /*restore the old settings*/
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

extern void clear_window() {
  clear(); /* cursor to zero position */
#ifdef __linux__
  system("clear");
#endif
}

/* This function handles the key inputs. It blocks the program until a key is
 * pressed. */
extern key_selection_t get_key_input() {
  int s;
  if (getchar() == '\033') { // if the first value is esc
    getchar();               // skip the [
    s = getchar();
    switch (s) { // the real value
    case 'A':    /* code for arrow up */
      printf("Info:\tarrow up pressed\n");
      return ARROW_UP;
      break;
    case 'B': /* code for arrow down */
      printf("Info:\tarrow down pressed\n");
      return ARROW_DOWN;
      break;
    case 'C': /* code for arrow right */
      printf("Info:\tarrow right pressed\n");
      return ARROW_RIGHT;
      break;
    case 'D': /* code for arrow left */
      printf("Info:\tarrow left pressed\n");
      return ARROW_LEFT;
      break;
    default:
      printf("Info:\tUnknown key input: %c\n", s);
      break;
    }
  } else { /* when return key is pressed */
    printf("Info:\treturn key pressed\n");
    return RETURN_KEY;
  }
  return UNKNOWN_KEY;
}
