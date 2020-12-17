.PHONY: clean
CC = gcc
APP = terminal
SRC2 = pseudo_terminal
SRC = $(APP).c
CFLAGS = $(shell pkg-config gtk+-3.0 --libs --cflags )
DEP = ../disk/disk
DEP1 = ../structure/structure
DEP2 = ../structure/tree_parser
DEP3 = ../directory_view/gtktreeview


$(APP):$(SRC) $(DEP).h $(DEP1).h $(DEP2).h $(DEP3).h
				$(CC) -o $(APP) $(SRC) $(DEP).c $(DEP1).c $(SRC2).c $(DEP2).c $(DEP3).c -I$(DEP) -I$(DEP1) -I$(DEP2) -I$(DEP3) $(CFLAGS)
 

clean:
				rm $(APP)

