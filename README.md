# nolibc

My poor attempt of rewritting a small portion of libc without libc but syscalls

this is not intended for any use

purely written out of fun

--- 

# Compile 
edit `src/main` 

```sh
    make
    make run
```
### To test all 

```sh
    make make_check
```

### Targets

- `make_check` = run all ( for testing )
- `static` = creats a static lib in `static_lib` and links to `src/main.c`
- `static_lib_` = creates static lib `no_libc.a` in `static_lib/`
- `shared` = creates shared objects in `lib/` ( it is the default )
- `main` = uses raw c files in `include/src/` 

---

## Note
- compiles to so files which are then used 

---

# DIR

- `src/` = source files 
- `include/` = header files & source files for the header files
- `include/src/` = source files for the header files
- `iib/` = compiled shared object files
- `scripts/` = scripts to compile shared files and check shared files
- `static_lib/` = contains `no_libc.a` for static linking
- `bin` = binary is placed

---

### Available Functions

-  _read     
-  _write    
-  _print    
-  _println  
-  _scanline 
-  _scan     
-  _printf   
-  _scanf    
-  _exit   
-  _malloc 
-  _memset 
-  _brk    
-  sbrk    
- _strlen  
- _reverse
- _itoa 
- _stoa
- _memcpy
- _memcmp
- _format
- _sprintf
- _snprintf
- _open
- _creat
- _close 
