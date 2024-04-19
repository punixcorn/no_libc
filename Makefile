FLAGS= -std=c11 -ggdb -w
args=


# uses shared files 
shared: lib src/main.c
	@./scripts/check_bin.sh
	@./scripts/check_lib.sh
	gcc $(FLAGS) -w lib/*  src/main.c -o bin/main

# uses nothing
main: include/**/*
	@./scripts/check_bin.sh
	gcc $(FLAGS) -nostdlib src/* -o bin/main 

run:
	@echo ===========================================
	@./bin/main $(args)

# runs every check
make_check:
	@./scripts/check_bin.sh
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
	rm bin/*  2>/dev/null
	rm lib/* 2>/dev/null
