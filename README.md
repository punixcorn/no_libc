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
make test
```

### Targets in Makefile

- `test` = compile lib in all formats (**.so**,**.a**,**.c**) for testing 
- `static_lib` = creates static lib `no_libc.a` in `static_lib/` dir
- `shared_lib` = creates shared objects (**.so**) in `shared_lib/` ( it is the default target )
- `all` = uses raw c files in `include/src/` and links them to `src/main.c`

---

## Note

- The default **make** compiles the header files to `.so` files in `lib/` which are then used to link `src/main.c`
- compiled binary is located in `bin/`

---

# DIRECTORIES
## libc source codes 
- `include/` = header include files 
- `include/src/` = source include files for the header include files
- `src/` = source file(s), that's where `main.c` is located ( Program Entry )

## Compiled source codes
- `shared_iib/` = compiled shared object files ( `.so` files )
- `static_lib/` = contains `no_libc.a` for static linking
- `bin` = ouput binary is placed

## others
- `scripts/` ( no longer in use ) = scripts to compile shared files and check shared files ( used in old makefile )

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
- _malloc
- _memset
- _brk
- sbrk
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
