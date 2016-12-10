#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

int
main (int argc, char *argv[])
{
	int		retval = EXIT_SUCCESS;
	struct character character;
	char           *filepath;

  if (argc != 2) {
		retval = EXIT_FAILURE;
		printf ("Yo, you forgot to tell me what file to load!\n");
		printf ("usage: %s path-to-file\n", argv[0]);
	} else {
		filepath = calloc (strlen (argv[1]), sizeof (char) + 1);

		if (NULL != filepath) {
			strcpy (filepath, argv[1]);
			read_character_sheet (argv[1], &character);
		} else {
			retval = EXIT_FAILURE;
		}
	}

	return retval;
}
