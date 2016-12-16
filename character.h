#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Ensure we don't redefine things */
#ifndef CHARACTER_H
#define CHARACTER_H

struct character {
  char *name;
  int hp;
  int maxhp;
};


/* read-character-sheet */
int readCharacterSheet(char *filepath, struct character *character);
int getIntValue(char *prefix, char* line);


#endif
