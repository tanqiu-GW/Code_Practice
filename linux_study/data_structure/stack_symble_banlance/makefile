#Makefile start

#files
TARGET = symbol_balance
OBJ = stack.o main.o
SRC = stack.c main.c
HEAD = stack.h common_type.h


#specifies the search path
vpath %.h ../common
VPATH = ../common/stack


#parameter
CC=gcc
CFLAGS=-Wall -g
CPPFLAGS=
LDFLAGS=


#target and depend
EXE:$(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $^

OBJ:$(SRC) $(HEAD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(OBJ) -c $^


#clean .o file
.PHONY:clean
clean:
	-$(RM) $(OBJ) $(EXE)




#Makefile end
