# Define the machine object files for your program
OBJECTS = main.o Stack.o
# Define your include file
INCLUDES = Stack.h

# make for the executable
project1: main.o Stack.o
	gcc -g -o project1 main.o Stack.o

# Simple suffix rules for the .o
main.o: main.c Stack.h
	gcc -g -c main.c

Stack.o: Stack.c Stack.h
	gcc -g -c Stack.c

# Clean the .o files
clean:
	rm -f *.o project1
