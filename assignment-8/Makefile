DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic -O -lrt
LFLAGS = -Wall -std=c99 -pedantic -O -lrt

CC = gcc
LD = $(CC)

NAME1 = serwer
NAME2 = klient
LIB1 = kolejki


SRC1 = $(NAME1).c
SRC2 = $(NAME2).c
LIB1 = $(LIB1).c

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x


$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@
	
$(EXEC2): $(SRC2)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@


all: $(EXEC1) $(EXEC2)


run:  $(EXEC1) $(EXEC2)
	xterm -hold -title serwer -bg Thistle3 -e ./$(EXEC1) &
	xterm -hold -title klient -bg Silver -e ./$(EXEC2) &
	xterm -hold -title klient -bg Silver -e ./$(EXEC2)
	
	


clean:
	rm -f *.x
# Archiwizacja i kompresja
tar: clean
	(tar -cvzf $(DIR).tar.gz *.c )
