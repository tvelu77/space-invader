###### VARIABLES #######
LDFLAGS 				= `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV`
RM 							= rm -f
MKDIR 					= mkdir -p
EXTENSION				= exe

CC 							= gcc
CFLAGS     			= -Wall -ansi -I include
RM 							= rm -f

SRC             = ./src
OBJ             = ./obj
BIN             = ./bin

sources         = $(wildcard $(SRC)/*.c)
objects         = $(sources:$(SRC)/%.c=$(OBJ)/%.o)

MAIN = spaceinvader.$(EXTENSION)
TEST = test.$(EXTENSION)

###### RULES #######

all: $(MAIN) #$(TEST)

$(MAIN): $(objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ):
	mkdir $@

$(objects): $(OBJ)/%.o : $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(MAIN)

re: clean all

clean:
	$(RM) -r $(OBJ)
	$(RM) $(MAIN)
	$(RM) $(TEST)

.PHONY: all clean run test
