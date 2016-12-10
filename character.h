/*
Holding spot for character data.
*/

/* Ensure we don't redefine things */
#ifndef CHARACTER_STRUCT
#define CHARACTER_STRUCT

struct character {
  char *name;
};

int read_character_sheet();

#endif
