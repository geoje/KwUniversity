CC = gcc
CFAGS = -W -Wall
TARGET = hw1
OBJ = Disk.o fat.o testcase.o

$(TARGET) : $(OBJ) validate.o
	$(CC) -o $@ $^
	rm $(OBJ)

.c.o: 
	$(CC) -c ${CFLAGS} $<

clean :
	rm $(OBJ)