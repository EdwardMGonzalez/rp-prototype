
#include "character-command.h"

void		enterLoop (struct character *character);

int
main (int argc, char *argv[])
{
	int		retval;
	char           *filepath;
	struct character *character;
	retval = EXIT_SUCCESS;
	character = malloc (sizeof (struct character));

	if (argc != 2) {
		retval = EXIT_FAILURE;
		printf ("Yo, you forgot to tell me what file to load!\n");
		printf ("usage: %s path-to-file\n", argv[0]);
	} else {
		filepath = calloc (strlen (argv[1]), sizeof (char) + 1);
		assert (NULL != filepath);
		strcpy (filepath, argv[1]);
		if (0 == readCharacterSheet (filepath, character))
			printf ("Sorry, I could't load the character sheet.");
		else
			enterLoop (character);
		free (filepath);
	}

	return retval;
}

void
enterLoop (struct character *character)
{
	char           *line = NULL;
	size_t		linecap = 0;
	ssize_t		linelen;
	characterCommand command;
	/* Report character sheet is loaded */
	printf ("%s loaded.\n", character->name);

	/* main command loop */
	while ((linelen = getline (&line, &linecap, stdin)) > 0) {
		command = commandFactory (line);
		command (character, line);
	}

	free (line);		/* preven memory leak */
}
