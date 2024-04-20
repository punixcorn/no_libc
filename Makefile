FLAGS= -std=c11 -ggdb -w
args=


# uses shared files 
shared: lib src/main.c
	@./scripts/check_bin.sh
	@./scripts/check_lib.sh
	gcc $(FLAGS) -nostdlib lib/* include/src/_lib.c src/main.c -o bin/main  
	@# adding _lib.c because undefined refernce to _start();

static: static_lib/* src/main.c
	make static_lib 
	@./scripts/check_bin.sh
	gcc -static -w -nostdlib $(FLAGS) src/main.c static_lib/no_libc.a -o bin/main 

# uses .c files
main: include/**/* src/main.c
	@./scripts/check_bin.sh
	gcc $(FLAGS) -nostdlib include/src/* src/* -o bin/main 

# runs every check
make_check:
	@echo "=============================================="
	make main 

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
	@touch bin/t lib/a
	@rm bin/*  2>/dev/null
	@rm lib/* 2>/dev/null
	@echo "Done"
