OBJS = Main.o Scanner.o Parser.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Interpreter : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Interpreter

Main.o : Main.cpp Scanner.h
	$(CC) $(CFLAGS) Main.cpp

Scanner.o : Scanner.cpp Scanner.h
	$(CC) $(CFLAGS) Scanner.cpp

Parser.o : Parser.cpp Parser.h
	$(CC) $(CFLAGS) Parser.cpp

clean:
	rm *.o *~ Interpreter out.txt
