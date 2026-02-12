SOURCES=./sources
HEADERS=./headers
OBJS=./objs
BIN=./bin
COMP=gcc -Wall -I $(HEADERS)

$(BIN)/FnafTerminal:	$(SOURCES)/main.c $(OBJS)/animatronic.o $(OBJS)/threadFunc.o $(OBJS)/room.o
						$(COMP) $(SOURCES)/main.c $(OBJS)/animatronic.o $(OBJS)/threadFunc.o -o $(BIN)/FnafTerminal

$(OBJS)/threadFunc.o:	$(SOURCES)/threadFunc.c $(OBJS)/room.o
						$(COMP) $(SOURCES)/threadFunc.c $(OBJS)/room.o -c -o $(OBJS)/threadFunc.o

$(OBJS)/animatronic.o:	$(SOURCES)/animatronic.c $(OBJS)/room.o
						$(COMP) $(SOURCES)/animatronic.c $(OBJS)/room.o -c -o $(OBJS)/animatronic.o

$(OBJS)/room.o:			$(SOURCES)/room.c
						$(COMP) $(SOURCES)/room.c -c -o $(OBJS)/room.o

clean:
		rm -f $(OBJS)/*

clobber:	clean
			rm -f $(BIN)/*