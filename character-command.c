/*
 * Defines commands and utils for character inspection and manipulation
 */
#include "character-command.h"


#define NUMCOMMANDS  5

namedCommand	COMMANDS[NUMCOMMANDS] = {
	{"dmg", dmg},
	{"heal", heal},
	{"hp", hp},
	{"maxhp", maxhp},
	{"quit", quit}
};

void
dmg (struct character *character, char *line)
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

void
hp (struct character *character, char *line)
{
	printf ("HP: %d\n", character->hp);
}

void
maxhp (struct character *character, char *line)
{
	printf ("MaxHP: %d\n", character->maxhp);
}

void
quit (struct character *character, char *line)
{
	exit (EXIT_SUCCESS);
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
	int		i = NUMCOMMANDS;
	while (i--) {
		namedCommand	cmd = COMMANDS[i];
		if (0 == strncmp (cmd.name, line, strlen (cmd.name))) {
			return cmd.command;
		}
	}

	return &defaultCommand;
}
