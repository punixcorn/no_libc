# nolibc

My poor attempt of rewritting a small portion of libc without libc but syscalls

this is not intended for any use

purely written out of fun

--- 

# Compile 
edit `src/main` 

```sh
    make
```
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
