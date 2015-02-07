INC=inc
SRC=src
BIN=bin
GCC=gcc
OPT=-O3

all: muncher

muncher:
	gcc $(OPT) -o $(BIN)/muncher -I $(INC) $(SRC)/muncher.c

clean:
	rm $(BIN)/muncher

