c_include_source_files := $(shell find ../include/ -name "*.c")

no_libc.a: *.o
	@echo -e "[\e[42m Archiving... \e[0m]"
	ar rvs $@ $?
	rm $?

*.o: ${c_include_source_files}
	@echo -e "[\e[42m Building... \e[0m]"
	gcc -c $?

clean:
	@touch a.o a.a
	@rm *.o
	rm *.a

