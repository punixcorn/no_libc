FLAGS= -std=c11 -ggdb -w
args=


# uses shared files 
shared: lib src/main.c
	[[ -d bin ]] || mkdir bin
	@./scripts/check_lib.sh
	gcc $(FLAGS) -w lib/*  src/main.c -o bin/main

# uses nothing
main: include/**/*
	[[ -d bin ]] || mkdir bin
	gcc $(FLAGS) -nostdlib src/* -o bin/main 

run:
	@echo ===========================================
	@./bin/main $(args)

# runs every check
make_check:
	@echo "Runing checks"
	@echo "[@] compiling rawfiles"
	gcc $(FLAGS) src/main.c include/**/* -nostdlib -w -o bin/main 
	@echo "===== DONE ====="
	@echo "[@]compiling shared files"
	[[ -d bin ]] || mkdir bin
	@./scripts/check_lib.sh
	gcc $(FLAGS) -w lib/*  src/main.c -o bin/main
	@echo "===== DONE ====="

clean:
	rm bin/main  2>/dev/null
	rm lib/* 2>/dev/null
