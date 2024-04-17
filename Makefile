main_w: src/*
	gcc -nostdlib -ggdb src/* -o main
main: src/*
	gcc -w -nostdlib -ggdb src/* -o main
run:
	@./main
	@echo ===========================================
clean:
	rm main 
