#include "character.h"

int
main (int argc, char *argv[])
{
	int		retval;
	char           *filepath;
  struct character *character;

  retval = EXIT_SUCCESS;
  character = malloc(sizeof(struct character));
  character->hp = 22;
  
  if (argc != 2) {
		retval = EXIT_FAILURE;
		printf ("Yo, you forgot to tell me what file to load!\n");
		printf ("usage: %s path-to-file\n", argv[0]);
	} else {
		filepath = calloc (strlen (argv[1]), sizeof (char) + 1);
    assert (NULL != filepath);
		strcpy (filepath, argv[1]);
		if (read_character_sheet (filepath, character))
      printf("yay");
    else
      printf("boo");
    free(filepath);
	}

	return retval;
}
