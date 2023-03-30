DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

CC = gcc
LD = $(CC)

NAME1 = zadanie2
NAME2 = procesy

SRC1 = $(NAME1).c
SRC2 = $(NAME2).c


EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC2): $(SRC2)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@


all: $(EXEC1) $(EXEC2)

runzadanie2: $(EXEC1)
	./$(EXEC1)
	
runprocesy: $(EXEC2)
	./$(EXEC2)


clean:
	rm -f *.x
# Archiwizacja i kompresja
tar: clean
	(tar -cvzf $(DIR).tar.gz *.c )
