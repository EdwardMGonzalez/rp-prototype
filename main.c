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
	character->hp = 22;

	if (argc != 2) {
		retval = EXIT_FAILURE;
		printf ("Yo, you forgot to tell me what file to load!\n");
		printf ("usage: %s path-to-file\n", argv[0]);
	} else {
		filepath = calloc (strlen (argv[1]), sizeof (char) + 1);
		assert (NULL != filepath);
		strcpy (filepath, argv[1]);
		if (0 == read_character_sheet (filepath, character))
			printf ("Sorry, I could't load the character.");
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
	while ((linelen = getline (&line, &linecap, stdin)) > 0) {
		printf ("%s", line);
	}

	free (line);		/* preven memory leak */
}
