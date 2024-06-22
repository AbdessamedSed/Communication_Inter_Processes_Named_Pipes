CC = gcc
CFLAGS = -Iinclude -Wall
OBJ = src/gui.o src/calcul.o src/trace.o
TARGET = communication

all: \$(TARGET)

\$(TARGET): \$(OBJ)
	\$(CC) -o \$(TARGET) \$(OBJ)

src/gui.o: src/gui.c include/calcul.h
	\$(CC) \$(CFLAGS) -c src/gui.c -o src/gui.o

src/calcul.o: src/calcul.c include/calcul.h
	\$(CC) \$(CFLAGS) -c src/calcul.c -o src/calcul.o

src/trace.o: src/trace.c include/trace.h
	\$(CC) \$(CFLAGS) -c src/trace.c -o src/trace.o

clean:
	rm -f src/*.o \$(TARGET)
