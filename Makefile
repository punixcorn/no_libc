# source files from include/
c_include_source_files := $(shell find include/* -name "*.c")
c_include_header_files := $(shell find include/* -name "*.h")
# source files from src/
c_source_files := $(shell find src/* -name "*.c")
c_header_files := $(shell find src/* -name "*.h")
# shared so files
shared_libs = $(shell find shared_lib/* -name "*.so")
# Compile flags
FLAGS= -std=c11 -ggdb -w -nostdlib -nostartfiles
# input args to main ( set at runtime )
args=


# make all so files and build main binary with it
.PHONY: shared_lib
shared_lib: $(c_include_source_files) $(c_source_files) $(shared_libs) $(c_header_files)
	@mkdir -p build shared_lib 
	@echo -e "[\e[42m Building so files... \e[0m]"
	@$(foreach file ,$(c_include_source_files),gcc -shared $(file) -o  $(patsubst include/src/%.c, shared_lib/%.so, $(file)) && ) true
	gcc ${FLAGS} ${shared_libs} include/src/_lib.c ${c_source_files} -o build/main
	@echo -e "\e[32m[+]\e[0m Done."
	@echo -e "\e[32m[+]\e[0m Linking File..."
	@$(foreach file ,$(c_include_source_files),gcc -shared $(file) -o  $(patsubst include/src/%.c, shared_lib/%.so, $(file)) && ) true
	@echo -e "\e[32m[?]\e[0m [\e[33m ${shared_libs} include/src/_lib.c \e[0m] + [\e[33m ${c_source_files} \e[0m]  -> [[ build/main ]]"
	@echo -e "\e[32m[+]\e[0m Done."


.PHONY: static_lib
static_lib:  $(c_include_source_files) $(c_include_header_files) $(c_source_files) $(c_include_files)
	@mkdir -p build/
	@echo -e "[\e[42m Building Static lib... \e[0m]"
	cd static_lib && make 
	@echo -e "\e[32m[+]\e[0m Linking File..."
	gcc -static ${FLAGS} ${c_source_files} static_lib/no_libc.a -o build/main 
	@echo -e "\e[32m[+]\e[0m Done."

test:
	@echo -e "\e[43m[ TESTING BUILDS \e[0m]"
	@echo -e "\e[33m[#]\e[0m TESTING : LINKING C FILES" 
	make all
	@echo -e "\e[33m[#]\e[0m TESTING : CREATING SO LIBS"
	make shared_lib
	@echo -e "\e[33m[#]\e[0m TESTING : CREATING STATIC LIBS"
	make static_lib
	@echo -e "\e[32m[+]\e[0m Done."

# uses .c files
.PHONY: all
all: $(c_include_source_files) $(c_include_header_files) $(c_source_files) $(c_include_files)
	@echo -e "[\e[42m Building Binary file... \e[0m]"
	@mkdir -p build/
	gcc $(FLAGS) ${c_include_source_files} ${c_source_files} -o build/main 
	@echo -e "\e[32m[+]\e[0m Done."

.PHONY: run
run:
	@echo "=============================================="
	@./build/main $(args)
	@echo "=============================================="
	make clean
	
clean:
	rm -rf build/* 2>/dev/null
