CC = gcc
CFAGS = -W -Wall
TARGET = hw3
OBJ = Disk.o buf.o fat.o main.o

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^
	rm $(OBJ)

.c.o: 
	$(CC) -c ${CFLAGS} $<

clean :
	rm $(OBJ)
