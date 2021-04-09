hw1 : Disk.o fat.o testcase.o validate.o
	gcc -o hw1 Disk.o fat.o testcase.o validate.o
	rm Disk.o fat.o testcase.o

Disk.o:
	gcc -c Disk.c
	
fat.o:
	gcc -c fat.c
	
testcase.o:
	gcc -c testcase.c

clean :
	rm Disk.o fat.o testcase.o