FLAGS= -std=c11 -ggdb
args=


main_lib: lib src/main.c
	@./scripts/check_lib.sh
	gcc $(FLAGS) -w lib/*  src/main.c -o bin/main

main: include/**/*
	gcc $(FLAGS) -nostdlib src/* -o bin/main 

main_w: include/**/*
	gcc $(FLAGS) -nostdlib src/* -o bin/main

run:
	@echo ===========================================
	@./bin/main $(args)

clean:
	rm bin/main  2>/dev/null
	rm lib/* 2>/dev/null
