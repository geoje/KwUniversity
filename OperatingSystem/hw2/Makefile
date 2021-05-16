CC = gcc
CFAGS = -W -Wall
TARGET = main
OBJ = Disk.o buf.o main.o

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^
	rm $(OBJ)

.c.o: 
	$(CC) -c ${CFLAGS} $<

clean :
	rm $(OBJ)