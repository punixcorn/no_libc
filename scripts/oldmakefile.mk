c_include_source_files := $(shell find include/* -name "*.c")
c_include_header_files := $(shell find include/* -name "*.h")
c_source_files := $(shell find src/* -name "*.c")
c_header_files := $(shell find src/* -name "*.h")

shared_libs = $(shell find shared_lib/* -name "*.so")

shared_libs_output_files := $(patsubst include/src/%.c, shared_lib/%.so, $(c_include_source_files))
FLAGS= -std=c11 -ggdb -w -nostdlib -nostartfiles
args=

koo:
	@echo $(shared_libs_output_files)
	
loop: 
	$(foreach file ,$(c_include_source_files),gcc -shared $(file) -o $(patsubst include/src/%.c, shared_lib/%.so, $(file)) && ) true
echo:
	
	@echo $(output_shared_object_files_name:_=lib_)
	@echo ${c_include_source_files}
	@echo ${c_include_header_files}
	@echo ${c_source_files}
	@echo ${c_header_files}
	@echo ${shared_libs}


# uses shared files 
shared:  src/main.c
	@mkdir -p build lib
	@./scripts/check_lib.sh
	gcc $(FLAGS) -nostdlib lib/* include/src/_lib.c src/main.c -o build/main  
	@# adding _lib.c because undefined refernce to _start();

shared_2: $(c_include_source_files) $(c_source_files) $(shared_libs)
	@mkdir -p build shared_lib 
	@$(foreach file ,$(c_include_source_files),gcc -shared $(file) -o  $(patsubst include/src/%.c, shared_lib/%.so, $(file)) && ) true
	gcc ${FLAGS} ${shared_libs} include/src/_lib.c ${c_source_files} -o build/main


static: static_lib/* src/main.c
	make static_lib 
	@mkdir -p build/
	gcc -static -w -nostdlib $(FLAGS) src/main.c static_lib/no_libc.a -o build/main 

# uses .c files
main: include/**/* src/main.c
	@mkdir -p build/
	gcc $(FLAGS) -nostdlib include/src/* src/* -o build/main 

# runs every check
make_check:
	$(info "==============================================")
	make main 

# creates a static lib
static_lib_:
	cd static_lib && make all 
	
run:
	@echo "=============================================="
	@./build/main $(args)
	@echo "=============================================="
	make clean

clean:
	@echo "Cleaning..."
	@rm -rf build/  2>/dev/null
	@rm -rf lib/ 2>/dev/null
	@echo "Done"
