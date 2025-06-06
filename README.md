## Description

**42sh** is a command-line interpreter developed as part of the Epitech curriculum.
It replicates the behavior of a basic Unix shell, inspired by TCSH.
The project includes support for built-ins, line editing, redirections, pipes, command history, and aliases.

---


## Features

- **External command execution** via `fork()` / `execve()`.
- **Built‐ins**:
  - `cd`, `env`, `exit`, `setenv`, `unsetenv`, `which`, `where`, `repeat`, `echo`, `alias`, `history`
- **Robust parsing**:
  - LL‐style parser for command input to build an AST, followed by AST interpretation.
- **Redirections**:
  - Output redirection `>` / `>>`, input redirection `<`, and here‐doc `<<`.
- **Multiple pipelines** (`|`).
- **Logical operators** `&&` and `||`.
- **Command history** stored in a file and accessible via the `history` built-in.
- **Customizable aliases**.
- **Line editing** using arrow keys to navigate and modify input.

---

## Requirements

- Unix‐like environment (Linux, macOS, etc.)

## Compile Instructions
To compile the standard version of 42sh,
simply run make:

```bash
make
```

To compile a version with debug symbols enabled,
use the ``debug`` rule:

```bash
make debug
```

To compile a version with the address sanitizer,
you may use the ``sanitize`` rule:

```bash
make sanitize
```

When you're done, you can use the ``clean`` rule
to delete any temporary files, or the ``fclean``
rule to delete everything but the source code.
