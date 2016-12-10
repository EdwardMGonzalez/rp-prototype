#include "character.h"
#include <ctype.h>

char           *get_character_name (FILE * fp);


int
read_character_sheet (char *filepath, struct character *character)
{
	FILE           *fp;
	int		retval = 1;
	printf ("Reading %s...\n", filepath);

	if ((fp = fopen (filepath, "r")) == NULL)
		retval = 0;

	if ((character->name = get_character_name (fp)) == NULL)
		retval = 0;


	fclose (fp);
	return retval;
}


char           *
get_character_name (FILE * fp)
{
	char           *line = NULL;
	char           *name;
	size_t		linecap = 0;
	ssize_t		linelen;
	int		i = 2,	j = 0;
	linelen = getline (&line, &linecap, fp);
	/* Name must be smaller than the line */
	name = calloc (linelen, sizeof (char));

	/* check the prefix '# ' exists */
	if (linelen < 2 || '#' != line[0] || ' ' != line[1]) {
		free (name);
		free (line);
		printf ("First line should begin with '# '\n");
		return NULL;
	}
	/* skip any additoinal spaces */
	while (i <= linelen && (isspace (line[i])))
		i++;

	/* copy the name */
	while (i < linelen) {
		name[j] = line[i];
		j++;
		i++;
	}

	free (line);		/* don't leak! */
	return name;
}
