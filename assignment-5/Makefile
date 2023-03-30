DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

CC = gcc
LD = $(CC)

NAME1 = 5a
NAME2 = 5-kons
NAME3 = 5-prod


SRC1 = $(NAME1).c
SRC2 = $(NAME2).c
SRC3 = $(NAME3).c


EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x


$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC2): $(SRC2)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC3): $(SRC3)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

all: $(EXEC1) $(EXEC2) $(EXEC3)
	
run5a: $(EXEC1) $(EXEC2) $(EXEC3)
	./${EXEC1}

run5b: $(EXEC2) $(EXEC3)
	mkfifo -m 0644 potok
	./$(EXEC3) &
	./$(EXEC2) &

clean:
	rm -f *.x
	rm -f potok
# Archiwizacja i kompresja
tar: clean
	(tar -cvzf $(DIR).tar.gz *.c )
