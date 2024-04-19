all: *.o
	ar rvs no_libc.a *.o 
	rm *.o

*.o:
	gcc -c ../include/src/*

clean:
	rm no_libc.a

