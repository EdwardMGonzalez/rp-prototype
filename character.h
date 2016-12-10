#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Ensure we don't redefine things */
#ifndef CHARACTER_STRUCT
#define CHARACTER_STRUCT

struct character {
  char *name;
  int hp;
};

int read_character_sheet(char *filepath, struct character *character);

#endif
