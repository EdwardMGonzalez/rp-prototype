/*
 * Defines commands and utils for character inspection and manipulation
 */
#include "character.h"


void
printHp (struct character *character, char *line)
{
	printf ("HP: %d\n", character->hp);
}


void
takeDmg (struct character *character, char *line)
{
	int		reduction = getIntValue ("dmg", line);
	character->hp = character->hp - reduction;
	printf ("HP: %d\n", character->hp);
}

void
heal (struct character *character, char *line)
{
	int		increase = getIntValue ("heal", line);
	character->hp = character->hp + increase;
	printf ("HP: %d\n", character->hp);
}
/* what we do when we don't understand the input */
void
defaultCommand (struct character *character, char *line)
{
	int		i = 0;
	for (i = strlen (line) - 1; i >= 0; i--) {
		if (line[i] == '\n')
			line[i] = '\0';
	}
	printf ("I don't know how to '%s'\n", line);
}
/*
 * Decides which command to run based on the input, returns a function
 * pointer.
 */
characterCommand
commandFactory (char *line)
{
	if (0 == strncmp ("hp", line, 2))
		return &printHp;
	else if (0 == strncmp ("dmg", line, 3))
		return &takeDmg;
	else if (0 == strncmp ("heal", line, 4))
		return &heal;
	else if (0 == strncmp ("exit", line, 4))
		exit (EXIT_SUCCESS);
	return &defaultCommand;
}
