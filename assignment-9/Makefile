DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic -O3 -fPIC -pthread
LFLAGS = -Wall -std=c99 -pedantic -O

CC = gcc
LD = $(CC)

NAME1 = 9


SRC1 = $(NAME1).c


EXEC1 = $(NAME1).x


$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) $? $(LFLAGS) -o $@


all: $(EXEC1)
    
run:  $(EXEC1)
	./$(EXEC1)
    

clean:
	rm -f *.x
# Archiwizacja i kompresja
tar: clean
	(tar -cvzf $(DIR).tar.gz *.c )
