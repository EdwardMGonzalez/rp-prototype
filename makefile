# compiler
CC = gcc

# compiler flags
# -g :adds debugging
# -std=c89 -pedantic :ask gcc to be strict with me
# -Wall :turn on a lot of warnings
# -Werror :make warnings errors, because I like pain
CFLAGS = -Wall -g -std=c89 -pedantic -Werror

INDENT = indent -bap -lp -pcs -sob -bad -bbb -v

default: load-character

load-character: main.o character.h read-character-sheet.o character-command.o
	$(CC) $(CFLAGS) -o load-character main.o read-character-sheet.o character-command.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

read-character-sheet.o: read-character-sheet.c character.h
	$(CC) $(CFLAGS) -c read-character-sheet.c

character-command.o: character-command.c character.h character-command.h
	$(CC) $(CFLAGS) -c character-command.c

test: load-character characters/vaughn-dacey-walker.md
	clear
	./load-character ./characters/vaughn-dacey-walker.md

clean:
	ls *.o && rm *.o || true
	for f in *.c; do $(INDENT) $$f; done;
