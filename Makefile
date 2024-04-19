FLAGS= -std=c11 -ggdb -w
args=


# uses shared files 
shared: lib src/main.c
	@./scripts/check_bin.sh
	@./scripts/check_lib.sh
	gcc $(FLAGS) -w lib/*  src/main.c -o bin/main

static: static_lib/* src/main.c
	make static_lib 
	@./scripts/check_bin.sh
	gcc -static -w -nostdlib src/main.c static_lib/no_libc.a -o bin/main

# uses .c files
main: include/**/* src/main.c
	@./scripts/check_bin.sh
	gcc $(FLAGS) -nostdlib include/src/* src/* -o bin/main 

# runs every check
make_check:
	make shared 
	@echo "=============================================="
	make main 
	@echo "=============================================="
	make static_lib_

# creates a static lib
static_lib_:
	cd static_lib && make all 
	
run:
	@echo "=============================================="
	@./bin/main $(args)
	@echo "=============================================="
	make clean

clean:
	@echo "Cleaning..."
	@touch a.txt 
	@rm *.txt 2>/dev/null
	@rm bin/*  2>/dev/null
	@rm lib/* 2>/dev/null
	@echo "Done"
