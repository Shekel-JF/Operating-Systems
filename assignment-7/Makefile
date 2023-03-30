DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O -lrt -lpthread

CC = gcc
LD = $(CC)

NAME1s = 7s
NAME1d = 7d
NAME2 = producent
NAME3 = konsument
NAME4 = semafory
NAME5 = obsluga

OBJS1s = $(NAME1s).o
OBJS1d = $(NAME1d).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o


SRC1 = $(NAME1).c
SRC2 = $(NAME2).c
SRC3 = $(NAME3).c

EXEC1s = $(NAME1s).x
EXEC2s = $(NAME2)s.x
EXEC3s = $(NAME3)s.x

EXEC1d = $(NAME1d).x
EXEC2d = $(NAME2)d.x
EXEC3d = $(NAME3)d.x


LIB_OBJS = $(OBJS4) $(OBJS5)

LIB_NAME = MojaBiblioteka
LIB_DIR = ./lib
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so

%.o: %.c
	$(CC) $(CFLAGS) -c $< 


# Tworzenie biblioteki statycznej

$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

# Tworzenie biblioteki dynamicznej
$(LIB_SHAR): $(LIB_OBJS) 
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

# Reguły zależności dla programów korzystających z biblioteki statycznej

$(EXEC1s): $(OBJS1s) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS1s) -L$(LIB_DIR) -l$(LIB_NAME)
	
$(EXEC2s): $(OBJS2) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME)
	
$(EXEC3s): $(OBJS3) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME)

# Reguły zależności dla programów korzystających z biblioteki dynamicznej

$(EXEC1d): $(OBJS1d) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1d) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)
	
$(EXEC2d): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)
	
$(EXEC3d): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)	
	
	
runs: $(EXEC1s) $(EXEC2s) $(EXEC3s)
	./$(EXEC1s)
	
rund: $(EXEC1d) $(EXEC2d) $(EXEC3d)
	./$(EXEC1d)
	
clean:
	rm -f *.x
# Archiwizacja i kompresja
tar: clean
	(tar -cvzf $(DIR).tar.gz *.c *.h)
