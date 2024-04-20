all: *.o
	ar rvs no_libc.a *.o 
	rm *.o

*.o:
	gcc -c ../include/src/*

clean:
	@touch a.o a.a
	@rm *.o
	rm *.a

