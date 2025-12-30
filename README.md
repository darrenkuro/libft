<h1 align="center">Libft</h1>

<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-blue?style=flat-square&logo=opensourceinitiative&logoColor=white" alt="License"/>
    <img src="https://img.shields.io/badge/status-stable-brightgreen?style=flat-square&logo=git&logoColor=white" alt="Status">
    <img src="https://img.shields.io/badge/score-125%2F100-3CB371?style=flat-square&logo=42&logoColor=white" alt="Score"/>
    <img src="https://img.shields.io/badge/date-May%202nd%2C%202023-ff6984?style=flat-square&logo=Cachet&logoColor=white" alt="Date"/>
</p>

> A reimplementation of essential C standard library functions.

---

## 🚀 Overview

**Libft** is the first foundational project of 42’s core curriculum. It focuses on rebuilding standard C library functions from scratch—string manipulation, memory management, linked lists, and other utilities. The project emphasizes clean, minimal C design and practical understanding of how the standard library works internally.

## 🧰 Tech Stack: ![C](https://img.shields.io/badge/-C-A8B9CC?style=flat-square&logo=C&logoColor=black) ![Make](https://img.shields.io/badge/-Make-000000?style=flat-square&logo=gnu&logoColor=white)

## 📦 Features

- Re-implemented common libc functions such as `memcpy`, `strchr`, and `atoi`
- Built custom linked list utilities (`ft_lstnew`, `ft_lstmap`, etc.)
- Includes robust Makefile with dependency tracking (`-MMD`, `-MP`)
- Fully modular architecture — ready to link with any C project
- Extended with [get-next-line](https://github.com/darrenkuro/get-next-line) and [printf](https://github.com/darrenkuro/printf) for file I/O and formatted output
- Archive branches with norm-comply version; updated to have better repo structure and more comprehensive function catalog

---

## 🛠️ Configuration

### Prerequisites

- **Compiler:** `gcc` or `clang`
- **Build tool:** `make`

### Installation & Usage

```bash
# Clone the repository
git clone https://github.com/darrenkuro/libft.git
cd libft

# Build static library
make

# Link it to your project
gcc main.c libft.a -o main
```

### Examples & Demo

```c
#include "libft.h"

int main(void) {
    char *msg = ft_strdup("Hello, Libft!");
    ft_putendl_fd(msg, 1);
    free(msg);
    return 0;
}
```

### Development

#### Using Libft as a Git Submodule

To include libft in another C project:

```bash
# Add libft as a submodule inside your project
git submodule add https://github.com/darrenkuro/libft.git libft
git submodule update --init --recursive
```

Then, in your project’s Makefile, link against it according, see [push-swap](https://github.com/darrenkuro/push-swap) as an example.

---

## 📝 Notes & Lessons

### Makefile

#### Order-only prerequisite

```Makefile
# Ensure OBJDIR exists before compiling each .c file into a .o file.
# The dependency after '|' is an order-only prerequisite: it must exist,
# but won't cause a rebuild if its timestamp changes.
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
    $(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
```

#### Dependency tracking

```Makefile
# Add -MMD and -MP flags will automatically generate dependency files.
# MMD tells the compiler to generate .d files containing header dependencies.
# MP adds dummy rules for each header file to prevent errors if headers are later deleted.
# This ensures object files are rebuilt when relevant headers change.
CFLAGS := ... -MMD -MP

# '-' indicates optional, so that make doesn't error if these files are missing.
# It is at the end of the Makefile to avoid overwrite for conflicting targets.
-include $(OBJ:.o=.d)
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 📫 Contact

Darren Kuro – [darren0xa@gmail.com](mailto:darren0xa@gmail.com)
GitHub: [@darrenkuro](https://github.com/darrenkuro)
