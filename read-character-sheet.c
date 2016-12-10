#include "character.h"
#include <ctype.h>

char           *get_character_name (FILE * fp);
int		get_character_hp (FILE * fp);


int
read_character_sheet (char *filepath, struct character *character)
{
	FILE           *fp;
	int		retval = 1;
	printf ("Reading %s...\n", filepath);

	if ((fp = fopen (filepath, "r")) == NULL)
		retval = 0;

	/* Fill character struct */
	if ((character->name = get_character_name (fp)) == NULL)
		retval = 0;
	character->hp = get_character_hp (fp);

	fclose (fp);
	return retval;
}

struct lineinfo {
	int		len;
	char           *text;
};

struct lineinfo
seek_to_line_starting_with (char *prefix, FILE * fp)
{
	char           *line = NULL;
	size_t		buflen = 0;
	ssize_t		len;
	size_t		prefixlen;
	/* prep line info struct */
	struct lineinfo	lineinfo = {0, NULL};
	/* how big is the prefix? */
	if ((prefixlen = strlen (prefix)) > 0) {
		/* reset file position */
		rewind (fp);

		/* search for prefix */
		while ((len = getline (&line, &buflen, fp)) > 0) {
			if (0 == strncmp (line, prefix, prefixlen)) {
				lineinfo.len = len;
				lineinfo.text = line;
				break;
			}
		}
	}
	return lineinfo;
}


char           *
get_character_name (FILE * fp)
{
	struct lineinfo	lineinfo;
	char           *name = NULL;
	int		i = 0,	j = 0;
	char		prefix    [3] = "# \0";
	/* find name line */
	lineinfo = seek_to_line_starting_with (prefix, fp);

	if (lineinfo.len > 0) {
		/* make space for name */
		name = calloc (lineinfo.len, sizeof (char));
		/* start copy after prefix */
		for (i = strlen (prefix); i < lineinfo.len; i++) {
                        /* ignore non-printing characters */
			if (isprint (lineinfo.text[i])) {
				name[j] = lineinfo.text[i];
				j++;
			}
		}

		/* text was allocated in seek_to_line_starting_with's getline */
		free (lineinfo.text);
	}
	return name;
}


int
get_character_hp (FILE * fp)
{
	struct lineinfo	lineinfo;
	int		hp = 0;
	char		prefix    [5] = "HP: \0";
	/* seek to hp line */
	lineinfo = seek_to_line_starting_with (prefix, fp);

	/* if we found the line */
	if (lineinfo.len > 0) {
		sscanf (lineinfo.text, "HP: %d", &hp);
		/* text was allocated in seek_to_line_starting_with's getline */
		free (lineinfo.text);
	}
	return hp;
}
