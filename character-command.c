/*
 * Defines commands and utils for character inspection and manipulation
 */
#include "character-command.h"

void dmg (struct character *character, char *line);
void heal (struct character *character, char *line);
void hp (struct character *character, char *line);
void maxhp (struct character *character, char *line);
void quit (struct character *character, char *line);

void strength (struct character *character, char *line);
void dexterity (struct character *character, char *line);
void constitution (struct character *character, char *line);
void intelligence (struct character *character, char *line);
void wisdom (struct character *character, char *line);
void charisma (struct character *character, char *line);

#define NUMCOMMANDS  18
namedCommand	COMMANDS[NUMCOMMANDS] = {
	{"dmg", dmg},
	{"heal", heal},
	{"hp", hp},
	{"maxhp", maxhp},
	{"quit", quit},
	{"q", quit},
	{"strength", strength},
	{"str", strength},
        {"dexterity", dexterity},
        {"dex", dexterity},
	{"constitution", constitution},
	{"con", constitution},
        {"intelligence", intelligence},
        {"int", intelligence},
        {"wisdom", wisdom},
        {"wis", wisdom},
        {"charaisma", charisma},
        {"cha", charisma}
};



void
bonus (int score)
{
	int		bonus = 0;
	if (10 <= score) {
		bonus = (score - 10) / 2;
	} else {
		bonus = (score - 11) / 2;
	}

	printf ("Bonus: %d\n", bonus);
}

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

void
strength (struct character *character, char *line)
{
	printf ("Strength: %d\n", character->strength);
	bonus (character->strength);
}

void
dexterity (struct character *character, char *line)
{
	printf ("Dexterity: %d\n", character->dexterity);
	bonus (character->dexterity);
}

void
constitution (struct character *character, char *line)
{
	printf ("Constitution: %d\n", character->constitution);
	bonus (character->constitution);
}

void
intelligence (struct character *character, char *line)
{
	printf ("Intelligence: %d\n", character->intelligence);
	bonus (character->intelligence);
}

void
wisdom (struct character *character, char *line)
{
	printf ("Wisdom: %d\n", character->wisdom);
	bonus (character->wisdom);
}

void
charisma (struct character *character, char *line)
{
	printf ("Charisma: %d\n", character->charisma);
	bonus (character->charisma);
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
