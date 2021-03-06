#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Ensure we don't redefine things */
#ifndef CHARACTER_H
#define CHARACTER_H

struct character {
  char *name;
  int hp; /* current hp */
  int maxhp; /* max hp */
  int strength, dexterity, constitution,
  intelligence, wisdom, charisma; /* attriutes */

};


/* read-character-sheet */
int readCharacterSheet(char *filepath, struct character *character);
int getIntValue(char *prefix, char* line);


#endif
