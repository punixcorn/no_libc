<h1 align="center">
    nolibc
</h1>

> [!WARNING]
> Still a work in progress


My poor attempt of re-writting a small portion of libc without libc but syscalls </br>
This is not intended for any use. </br>
Purely written out of fun and for demo purposes. </br>

---

# Compile

### Edit `src/main.c`

### Install dependencies 

```sh
sudo pacman -S make gcc     # Archlinux
sudo apt install make gcc   # Debian based 
sudo dnf install make gcc   # Red Hat based
```
### Compile 

```sh
make        # compiles binary
make run    # run's binary
```

### Run tests 

```sh
make make_check
```

### Targets in Makefile

- `make_check` = compile lib in all formats (**.so**,**.a**,**.c**) for testing 
- `static` = creats a static lib in `static_lib/` dir and links to `src/main.c` 
- `static_lib_` = creates static lib `no_libc.a` in `static_lib/` dir
- `shared` = creates shared objects (**.so**) in `lib/` ( it is the default target )
- `main` = uses raw c files in `include/src/` and links them to `src/main.c`

---

## Note

- The default **make** compiles the header files to `.so` files in `lib/` which are then used to link `src/main.c`
- compiled binary is located in `bin/`

---

# DIRECTORIES

- `src/` = source file(s), that's where `main.c` is located
- `include/` = header files & source files dir, all used for the header files
- `include/src/` = source files for the header files
- `iib/` = compiled shared object files ( `.so` files )
- `scripts/` = scripts to compile shared files and check shared files ( used in makefile )
- `static_lib/` = contains `no_libc.a` for static linking
- `bin` = ouput binary is placed

---

### Available Functions

- _read
- _write
- _print
- _println
- _scanline
- _scan
- _printf
- _scanf
- _exit
- _free
- _malloc
- _memset
- _brk
- _sbrk
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
- _mmap
- _munmap
