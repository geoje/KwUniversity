obj = Disk.o fat.o testcase.o

hw1 : $(obj) validate.o
	gcc -o $@ $^
	make clean

.c.o: 
	gcc -c ${CFLAGS} $<

clean :
	rm $(obj)
