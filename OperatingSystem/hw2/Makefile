CC = gcc
CFAGS = -W -Wall
TARGET = hw2
OBJ = Disk.o buf.o testcase.o

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^
	rm $(OBJ)

.c.o: 
	$(CC) -c ${CFLAGS} $<

clean :
	rm $(OBJ)
