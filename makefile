SOURCES=./sources
HEADERS=./headers
OBJS=./objs
BIN=./bin
COMP=gcc -Wall -I $(HEADERS)

$(BIN)/FnafTerminal:	$(SOURCES)/main.c $(OBJS)/room.o $(OBJS)/animatronic.o $(OBJS)/threadFunc.o $(OBJS)/room.o
						$(COMP) $(SOURCES)/main.c $(OBJS)/animatronic.o $(OBJS)/threadFunc.o $(OBJS)/room.o -o $(BIN)/FnafTerminal

$(OBJS)/threadFunc.o:	$(SOURCES)/threadFunc.c
						$(COMP) $(SOURCES)/threadFunc.c -c -o $(OBJS)/threadFunc.o

$(OBJS)/animatronic.o:	$(SOURCES)/animatronic.c 
						$(COMP) $(SOURCES)/animatronic.c -c -o $(OBJS)/animatronic.o

$(OBJS)/room.o:			$(SOURCES)/room.c
						$(COMP) $(SOURCES)/room.c -c -o $(OBJS)/room.o

clean:
			rm -f $(OBJS)/*

clobber:	clean
			mv $(BIN)/gamedata .; rm -f $(BIN)/*; mv gamedata $(BIN)