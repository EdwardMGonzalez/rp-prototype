#include "character.h"

FILE *fp;
int retval = 1;
char c = EOF;

int read_character_sheet(char *filepath, struct character *character) {
  printf("Reading %s...\n", filepath);

  if((fp = fopen(filepath, "r")) == NULL) retval = 0;

  while ((c = getc(fp)) != EOF)
  {
    printf("%c", c);
  }

  fclose(fp);
  return retval;
}
