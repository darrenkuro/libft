<h1 align="center">
  <br>
  Libft
  <br>
</h1>

<h4 align="center">A comprehensive C standard library reimplementation</h4>

<p align="center">
  <a href="#overview">Overview</a> •
  <a href="#features">Features</a> •
  <a href="#getting-started">Getting Started</a> •
  <a href="#api-reference">API Reference</a> •
  <a href="#usage">Usage</a> •
  <a href="#license">License</a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C-99-blue?style=flat-square&logo=c&logoColor=white" alt="C99"/>
  <img src="https://img.shields.io/badge/Make-GNU-orange?style=flat-square&logo=gnu&logoColor=white" alt="Make"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=flat-square" alt="License"/>
  <img src="https://img.shields.io/badge/42-125%2F100-brightgreen?style=flat-square" alt="Score"/>
</p>

---

## Overview

**Libft** is a portable, lightweight C library that reimplements essential standard library functions from scratch. Originally developed as a foundational project at 42, it has evolved into a fully-featured utility library suitable for any C project.

The library provides:
- **String manipulation** — safe, null-checked string operations
- **Memory management** — allocation, copying, and comparison utilities
- **Linked lists** — generic singly-linked list implementation
- **Formatted output** — feature-complete `printf` family with extensions
- **File I/O** — file reading and line-by-line parsing (get_next_line)
- **Debug utilities** — binary and hex memory inspection

## Features

- Zero external dependencies (only libc)
- Strict compilation with `-Wall -Wextra -Werror`
- Incremental builds with automatic dependency tracking
- Modular architecture — include only what you need
- Extensively tested against edge cases

### Strings
| Function | Description |
|----------|-------------|
| `ft_strlen` | String length |
| `ft_strchr` | Find char in string |
| `ft_strrchr` | Find char from end |
| `ft_strncmp` | Compare n bytes |
| `ft_strlcpy` | Safe string copy |
| `ft_strlcat` | Safe string concatenate |
| `ft_strdup` | Duplicate string |
| `ft_substr` | Extract substring |
| `ft_strjoin` | Concatenate two strings |
| `ft_strtrim` | Trim characters from ends |
| `ft_strnstr` | Find substring |
| `ft_split` | Split string by delimiter |
| `ft_strmapi` | Map function over string |
| `ft_striteri` | Iterate with function |

## Getting Started

### Number Conversion
| Function | Description |
|----------|-------------|
| `ft_atoi` | String to integer |
| `ft_itoa` | Integer to string |

- A C compiler (`gcc` or `clang`)
- GNU Make

### Installation

```bash
git clone https://github.com/darrenkuro/libft.git
cd libft
make
```

This produces `libft.a`, a static library ready to link.

### Quick Start

```c
#include "libft.h"

int main(void)
{
    char *str = ft_strdup("Hello, Libft!");
    ft_printf("%s\n", str);
    free(str);
    return 0;
}
```

Compile with:

```bash
gcc main.c -L. -lft -I include -o main
```

### Using as a Git Submodule

```bash
git submodule add https://github.com/darrenkuro/libft.git libft
git submodule update --init --recursive
```

Then in your Makefile:

```makefile
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $@
```

---

## API Reference

### Character Functions

| Function | Description |
|----------|-------------|
| `ft_isalpha(c)` | Check if character is alphabetic |
| `ft_isdigit(c)` | Check if character is a digit |
| `ft_isalnum(c)` | Check if character is alphanumeric |
| `ft_isascii(c)` | Check if character is ASCII |
| `ft_isprint(c)` | Check if character is printable |
| `ft_toupper(c)` | Convert to uppercase |
| `ft_tolower(c)` | Convert to lowercase |

### String Functions

| Function | Description |
|----------|-------------|
| `ft_strlen(s)` | Get string length |
| `ft_strchr(s, c)` | Find first occurrence of character |
| `ft_strrchr(s, c)` | Find last occurrence of character |
| `ft_strncmp(s1, s2, n)` | Compare strings up to n bytes |
| `ft_strnstr(big, lit, n)` | Find substring within length limit |
| `ft_strlcpy(dst, src, n)` | Safe string copy |
| `ft_strlcat(dst, src, n)` | Safe string concatenation |
| `ft_strdup(s)` | Duplicate string |
| `ft_substr(s, start, len)` | Extract substring |
| `ft_strjoin(s1, s2)` | Concatenate two strings |
| `ft_strtrim(s, set)` | Trim characters from both ends |
| `ft_split(s, c)` | Split string by delimiter |
| `ft_strmapi(s, f)` | Apply function to each character (new string) |
| `ft_striteri(s, f)` | Apply function to each character (in place) |

### Memory Functions

| Function | Description |
|----------|-------------|
| `ft_memset(b, c, n)` | Fill memory with byte |
| `ft_bzero(s, n)` | Zero-fill memory |
| `ft_memcpy(dst, src, n)` | Copy memory (non-overlapping) |
| `ft_memmove(dst, src, n)` | Copy memory (overlap-safe) |
| `ft_memchr(s, c, n)` | Find byte in memory |
| `ft_memcmp(s1, s2, n)` | Compare memory blocks |
| `ft_calloc(count, size)` | Allocate and zero-initialize |

### Conversion Functions

| Function | Description |
|----------|-------------|
| `ft_atoi(s)` | String to integer |
| `ft_itoa(n)` | Integer to string |

### Output Functions

| Function | Description |
|----------|-------------|
| `ft_putchar_fd(c, fd)` | Write character to file descriptor |
| `ft_putstr_fd(s, fd)` | Write string to file descriptor |
| `ft_putendl_fd(s, fd)` | Write string with newline |
| `ft_putnbr_fd(n, fd)` | Write number to file descriptor |

### Printf Family

| Function | Description |
|----------|-------------|
| `ft_printf(fmt, ...)` | Formatted output to stdout |
| `ft_dprintf(fd, fmt, ...)` | Formatted output to file descriptor |
| `ft_snprintf(buf, n, fmt, ...)` | Formatted output to sized buffer |
| `ft_vsnprintf(buf, n, fmt, args)` | `snprintf` with va_list |
| `ft_asprintf(out, fmt, ...)` | Formatted output to allocated string |
| `ft_vasprintf(out, fmt, args)` | `asprintf` with va_list |

**Supported specifiers:** `c` `s` `p` `d` `i` `u` `x` `X` `%`

**Extensions:** `%m` (memory hex dump), `%b` (binary)

**Supported flags:** `-` `0` `+` `(space)` `#` `.` `*`

### Linked List Functions

```c
typedef struct s_list {
    void          *content;
    struct s_list *next;
} t_list;
```

| Function | Description |
|----------|-------------|
| `ft_lstnew(content)` | Create new node |
| `ft_lstsize(lst)` | Count nodes |
| `ft_lstlast(lst)` | Get last node |
| `ft_lstadd_front(lst, node)` | Add node at beginning |
| `ft_lstadd_back(lst, node)` | Add node at end |
| `ft_lstdelone(node, del)` | Delete single node |
| `ft_lstclear(lst, del)` | Delete all nodes |
| `ft_lstiter(lst, f)` | Apply function to each node |
| `ft_lstmap(lst, f, del)` | Create new list by mapping |

### File I/O Functions

| Function | Description |
|----------|-------------|
| `get_next_line(fd)` | Read next line from file descriptor |
| `ft_read_file(path)` | Read entire file into string |

### String Array Functions

| Function | Description |
|----------|-------------|
| `ft_strarrlen(arr)` | Get length of NULL-terminated string array |
| `ft_strarrcpy(arr)` | Deep copy string array |

### Debug Functions

| Function | Description |
|----------|-------------|
| `ft_printb(ptr, len)` | Print memory as binary |
| `ft_printh(ptr, len)` | Print memory as hexadecimal |
| `ft_printc(ptr, len)` | Print memory as characters |

---

## Usage

### Example: String Processing

```c
#include "libft.h"
#include <stdlib.h>

int main(void)
{
    char **words = ft_split("hello,world,libft", ',');

    for (int i = 0; words[i]; i++)
    {
        ft_printf("Word %d: %s\n", i, words[i]);
        free(words[i]);
    }
    free(words);
    return 0;
}
```

### Example: Linked List

```c
#include "libft.h"
#include <stdlib.h>

void print_content(void *content)
{
    ft_printf("%s\n", (char *)content);
}

int main(void)
{
    t_list *head = ft_lstnew(ft_strdup("first"));
    ft_lstadd_back(&head, ft_lstnew(ft_strdup("second")));
    ft_lstadd_back(&head, ft_lstnew(ft_strdup("third")));

    ft_lstiter(head, print_content);
    ft_lstclear(&head, free);
    return 0;
}
```

### Example: Reading Files

```c
#include "libft.h"
#include <stdlib.h>

int main(void)
{
    char *line;
    int fd = open("file.txt", O_RDONLY);

    while ((line = get_next_line(fd)) != NULL)
    {
        ft_printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## Project Structure

```
libft/
├── include/
│   ├── libft.h          # Main header
│   ├── ft_printf.h      # Printf declarations
│   └── ft_list.h        # Linked list types
├── src/
│   ├── ft_char.c        # Character functions
│   ├── ft_str.c         # String functions
│   ├── ft_mem.c         # Memory functions
│   ├── ft_num.c         # Number conversions
│   ├── ft_io.c          # I/O and get_next_line
│   ├── ft_lst.c         # Linked list
│   ├── ft_strarr.c      # String arrays
│   ├── ft_printf.c      # Printf implementation
│   └── ft_debug.c       # Debug utilities
├── Makefile
├── LICENSE
└── README.md
```

---

## Build Options

```bash
make          # Build libft.a
make clean    # Remove object files
make fclean   # Remove all build artifacts
make re       # Full rebuild
make DEBUG=1  # Build with debug symbols (-g)
```

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

<p align="center">
  <sub>Built with care at <a href="https://42.fr">42</a></sub>
</p>
