#Makefile start

#files
TARGET = tree_binary_search
OBJ = tree.o main.o
SRC = tree.c main.c
HEAD = tree.h common_type.h


#specifies the search path
vpath %.h ../common
VPATH = ../common/tree


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
