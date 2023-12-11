# eenvoudige makefile
all: hoofd.o gobord.o stapel.o
	g++ -Wall -o hetspel hoofd.o gobord.o stapel.o

gobord.o: gobord.cc gobord.h
	g++ -Wall -c gobord.cc

hoofd.o: hoofd.cc gobord.h stapel.h
	g++ -Wall -c hoofd.cc

stapel.o: stapel.cc stapel.h
	g++ -Wall -c stapel.cc
