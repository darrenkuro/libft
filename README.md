<h1 align="center">Libft</h1>

<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-blue?style=flat-square&logo=opensourceinitiative&logoColor=white" alt="License"/>
    <img src="https://img.shields.io/badge/status-stable-brightgreen?style=flat-square&logo=git&logoColor=white" alt="Status">
    <img src="https://img.shields.io/badge/score-125%2F100-3CB371?style=flat-square&logo=42&logoColor=white" alt="Score"/>
</p>

> A comprehensive C standard library reimplementation — memory, strings, I/O, linked lists, and a full printf.

---

## Overview

**Libft** is the foundational project of 42's core curriculum: rebuilding standard C library functions from scratch. This version extends the base project with integrated **get\_next\_line** and **ft\_printf** implementations, providing a single static library (`libft.a`) ready to link into any C project.

## Function Reference

### Character Classification
| Function | Description |
|----------|-------------|
| `ft_isalpha` | Check if alphabetic |
| `ft_isdigit` | Check if digit |
| `ft_isalnum` | Check if alphanumeric |
| `ft_isascii` | Check if ASCII |
| `ft_isprint` | Check if printable |
| `ft_toupper` | Convert to uppercase |
| `ft_tolower` | Convert to lowercase |

### Memory
| Function | Description |
|----------|-------------|
| `ft_memset` | Fill memory with byte |
| `ft_memcpy` | Copy memory |
| `ft_memmove` | Copy memory (overlap-safe) |
| `ft_memcmp` | Compare memory |
| `ft_memchr` | Find byte in memory |
| `ft_bzero` | Zero out memory |
| `ft_calloc` | Allocate and zero memory |

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

### String Arrays
| Function | Description |
|----------|-------------|
| `ft_strarrlen` | Array length |
| `ft_strarrcpy` | Deep copy string array |

### Number Conversion
| Function | Description |
|----------|-------------|
| `ft_atoi` | String to integer |
| `ft_itoa` | Integer to string |

### I/O
| Function | Description |
|----------|-------------|
| `ft_putchar_fd` | Write char to fd |
| `ft_putstr_fd` | Write string to fd |
| `ft_putendl_fd` | Write string + newline to fd |
| `ft_putnbr_fd` | Write number to fd |
| `ft_read_file` | Read entire file to string |
| `get_next_line` | Read next line from fd |

### Linked List
| Function | Description |
|----------|-------------|
| `ft_lstnew` | Create node |
| `ft_lstadd_front` | Add to front |
| `ft_lstadd_back` | Add to back |
| `ft_lstsize` | List length |
| `ft_lstlast` | Get last node |
| `ft_lstiter` | Iterate over list |
| `ft_lstmap` | Map function over list |
| `ft_lstdelone` | Delete one node |
| `ft_lstclear` | Delete all nodes |

### Printf
| Function | Description |
|----------|-------------|
| `ft_printf` | Formatted output to stdout |
| `ft_dprintf` | Formatted output to fd |
| `ft_snprintf` | Formatted output to buffer |
| `ft_vsnprintf` | `va_list` variant of snprintf |
| `ft_asprintf` | Formatted output with malloc |
| `ft_vasprintf` | `va_list` variant of asprintf |

Supported specifiers: `c` `s` `p` `d` `i` `x` `X` `u` `%` `m` (memory hex) `b` (binary)
Supported flags: `#` `-` `+` `0` `(space)` with width and precision

### Debug
| Function | Description |
|----------|-------------|
| `ft_printb` | Print binary representation |
| `ft_printh` | Print hex representation |
| `ft_printc` | Print char representation |

## Branches

| Branch | Description |
|--------|-------------|
| `main` | Active development — consolidated source files, extended printf (`dprintf`, `snprintf`, `asprintf`, etc.), debug utilities, and additional helpers. Does not follow 42 Norm. |
| `norm-comply` | Norm-compliant version with one-function-per-file layout. Use this branch if you need code that passes `norminette`. |
| `archive` | Original submission snapshot — includes the separately structured get\_next\_line and printf as they were at evaluation time. |

## Project Structure

```
libft/
├── src/
│   ├── ft_char.c       # Character classification
│   ├── ft_mem.c        # Memory operations
│   ├── ft_str.c        # String manipulation
│   ├── ft_strarr.c     # String array utilities
│   ├── ft_num.c        # Number conversion
│   ├── ft_io.c         # I/O and get_next_line
│   ├── ft_printf.c     # Full printf implementation
│   ├── ft_lst.c        # Linked list
│   └── ft_debug.c      # Debug printing
├── include/
│   ├── libft.h         # Main header
│   ├── ft_list.h       # Linked list types
│   └── ft_printf.h     # Printf types and flags
├── Makefile
└── LICENSE
```

## Usage

```bash
# Build
git clone https://github.com/darrenkuro/libft.git
cd libft
make

# Link to your project
cc main.c -Iinclude -L. -lft -o main
```

```c
#include "libft.h"

int main(void) {
    char *msg = ft_strdup("Hello, Libft!");
    ft_printf("msg: %s (len: %d)\n", msg, ft_strlen(msg));
    free(msg);
    return 0;
}
```

### As a Git Submodule

```bash
git submodule add https://github.com/darrenkuro/libft.git libft
git submodule update --init --recursive
```

See [push-swap](https://github.com/darrenkuro/push-swap) for an example of linking libft in a project Makefile.

---

<details>
<summary><strong>Notes & Lessons</strong></summary>

### Makefile: Order-only prerequisite

```Makefile
# Ensure OBJDIR exists before compiling each .c file into a .o file.
# The dependency after '|' is an order-only prerequisite: it must exist,
# but won't cause a rebuild if its timestamp changes.
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
    $(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
```

### Makefile: Dependency tracking

```Makefile
# -MMD and -MP flags automatically generate dependency files.
# MMD tells the compiler to generate .d files containing header dependencies.
# MP adds dummy rules for each header file to prevent errors if headers are later deleted.
# This ensures object files are rebuilt when relevant headers change.
CFLAGS := ... -MMD -MP

# '-' indicates optional, so that make doesn't error if these files are missing.
# It is at the end of the Makefile to avoid overwrite for conflicting targets.
-include $(OBJ:.o=.d)
```

</details>

---

## License

[MIT](LICENSE) - Darren Kuro
