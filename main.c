#include "character.h"

void		enter_loop ();

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
		if (0 == read_character_sheet (filepath, character))
			printf ("Sorry, I could't load the character sheet.");
		else
			enter_loop (character);
		free (filepath);
	}

	return retval;
}

void
enter_loop (struct character *character)
{
	char           *line = NULL;
	size_t		linecap = 0;
	ssize_t		linelen;
        printf ("%s loaded.\n", character->name);

	while ((linelen = getline (&line, &linecap, stdin)) > 0) {
                if(0 == strncmp("hp", line, 2)) printf("hp: %d\n", character->hp);
	}

	free (line);		/* preven memory leak */
}
