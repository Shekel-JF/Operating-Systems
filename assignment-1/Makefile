DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

CC = gcc
LD = $(CC)

NAME1 = 1a
NAME2 = 1b
NAME3 = 1c
NAME4 = 1d
NAME5 = 1e

SRC1 = $(NAME1).c
SRC2 = $(NAME2).c
SRC3 = $(NAME3).c
SRC4 = $(NAME4).c
SRC5 = $(NAME5).c

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x

$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC2): $(SRC2)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC3): $(SRC3)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC4): $(SRC4)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

$(EXEC5): $(SRC5)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

run1a: $(EXEC1)
	./$(EXEC1)
	
run1b: $(EXEC2)
	./$(EXEC2)
	
run1c: $(EXEC3)
	./$(EXEC3)
	
run1d: $(EXEC4)
	./$(EXEC4)
	
run1e: $(EXEC5)
	./$(EXEC5)

clean:
	rm -f *.x
# Archiwizacja i kompresja
tar: clean
	(tar -cvzf $(DIR).tar.gz *.c )
