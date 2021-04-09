CC = g++
CFAGS = -W -Wall
TARGET = main.out
OBJ = main.o

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	rm $(OBJ)

clean :
	rm $(OBJ)