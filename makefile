SOURCES=./sources
HEADERS=./headers
OBJS=./objs
BIN=./bin
COMP=gcc -Wall -I $(HEADERS)

$(BIN)/FnafTerminal:	$(SOURCES)/main.c $(OBJS)/animatronic.o $(OBJS)/threadFunc.o
						$(COMP) $(SOURCES)/main.c $(OBJS)/animatronic.o $(OBJS)/threadFunc.o -o $(BIN)/FnafTerminal

$(OBJS)/threadFunc.o:	$(SOURCES)/threadFunc.c
						$(COMP) $(SOURCES)/threadFunc.c -c -o $(OBJS)/threadFunc.o

$(OBJS)/animatronic.o:	$(SOURCES)/animatronic.c
						$(COMP) $(SOURCES)/animatronic.c -c -o $(OBJS)/animatronic.o

clean:
		rm -f $(OBJS)/*

clobber:	clean
			rm -f $(BIN)/*