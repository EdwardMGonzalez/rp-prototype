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
printMaxHp (struct character *character, char *line)
{
	printf ("MaxHP: %d\n", character->maxhp);
}


void
takeDmg (struct character *character, char *line)
{
	int		reduction = getIntValue ("dmg", line);

	character->hp = character->hp - reduction;
	if (character->hp < 0)
		character->hp = 0;
	printf ("HP: %d\n", character->hp);
}

void
heal (struct character *character, char *line)
{
	int		increase = getIntValue ("heal", line);

	/* update hp value as long as we're not over max */
	character->hp = character->hp + increase;
	if (character->hp > character->maxhp)
		character->hp = character->maxhp;
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
	if (0 == strncmp ("maxhp", line, 2))
		return &printMaxHp;
	else if (0 == strncmp ("dmg", line, 3))
		return &takeDmg;
	else if (0 == strncmp ("heal", line, 4))
		return &heal;
	else if (0 == strncmp ("exit", line, 4))
		exit (EXIT_SUCCESS);
	return &defaultCommand;
}
