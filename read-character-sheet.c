#include "character.h"
#include <ctype.h>

char           *getCharacterName (FILE * fp);
int seekToLineAndReturnIntValue (FILE * fp, char *prefix);

int
readCharacterSheet (char *filepath, struct character *character)
{
	FILE           *fp;
	int		retval = 1;
	printf ("Reading %s...\n", filepath);

	if ((fp = fopen (filepath, "r")) == NULL)
		retval = 0;

	/* Fill character struct */
	if ((character->name = getCharacterName (fp)) == NULL)
		retval = 0;
	character->hp = seekToLineAndReturnIntValue(fp, "HP:");
	character->maxhp = seekToLineAndReturnIntValue(fp, "MAXHP:");
	character->strength =seekToLineAndReturnIntValue(fp, "Strength:");
        character->dexterity = seekToLineAndReturnIntValue(fp, "Dexterity:");
	character->constitution = seekToLineAndReturnIntValue(fp, "Constitution:");
        character->intelligence = seekToLineAndReturnIntValue(fp, "Intelligence:");
        character->wisdom = seekToLineAndReturnIntValue(fp, "Wisdom:");
        character->charisma = seekToLineAndReturnIntValue(fp, "Charisma:");

	fclose (fp);
	return retval;
}

struct lineinfo {
	int		len;
	char           *text;
};

struct lineinfo
seekToLineStartingWith (char *prefix, FILE * fp)
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
getCharacterName (FILE * fp)
{
	struct lineinfo	lineinfo;
	char           *name = NULL;
	int		i = 0,	j = 0;
	char		prefix    [3] = "# \0";
	/* find name line */
	lineinfo = seekToLineStartingWith (prefix, fp);

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
seekToLineAndReturnIntValue (FILE * fp, char *prefix)
{
	struct lineinfo	lineinfo;
	int		value = 0;
	int		prefixlen;
	prefixlen = strlen (prefix);
	/* seek to line */
	lineinfo = seekToLineStartingWith (prefix, fp);
	/* if we found the line */
	if (lineinfo.len > 0) {
		value = getIntValue (prefix, lineinfo.text);
		free (lineinfo.text);
	}
	return value;
}


int
getIntValue (char *prefix, char *line)
{
	int		value = 0;
	char           *intstr = " %d";
	char           *format = calloc (strlen (prefix) + strlen (intstr), sizeof (char));
	format[0] = '\0';	/* make format string appear 0 length */
	strcat (format, prefix);/* format = prefix */
	strcat (format, intstr);/* format = prefix + valuestr */
	sscanf (line, format, &value);	/* pull value */
	free (format);		/* release memory */
	return value;
}
