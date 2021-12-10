all: interface.o processor.o
	gcc -o interface interface.o ; gcc -o processor processor.o

interface.o: interface.c constants.h 
	gcc -c interface.c

processor.o: processor.c constants.h
	gcc -c processor.c

run: 
	./main

