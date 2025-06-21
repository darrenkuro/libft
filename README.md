<h1 align="center">LIBFT</h1>

<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License"/>
    <img src="https://img.shields.io/badge/score-125%2F100-3CB371?style=flat-square&logo=42&logoColor=white" alt="Score"/>
    <img src="https://img.shields.io/badge/date-May%202%2C%202023-ff6984?style=flat-square&logo=Cachet&logoColor=white" alt="Date"/>
</p>

> This repo contains many reimplementation of general purpose functions of the standard C library. It is the first project of 42 common core. It is, however, the finalized version that goes beyond the original subject of libft, which includes source code of some of the following subjects as well, such as [get-next-line](https://github.com/darrenkuro/get-next-line), and [printf](https://github.com/darrenkuro/printf).

## 📝 Notes

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

Darren Kuro – [darrenkuro@icloud.com](mailto:darrenkuro@icloud.com)  
GitHub: [@darrenkuro](https://github.com/darrenkuro)
