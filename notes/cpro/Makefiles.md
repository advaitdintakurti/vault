### Makefiles

Makefiles are used in automation of the build process for software projects. They define a set of rules for compiling and linking programs, ensuring that your project is built efficiently and consistently.

A typical Makefile consists of _targets_, _dependencies_, and _commands_

#### Sample Makefile:
```c
build:
	gcc main.c -o main

run:
	@gcc main.c -o main
	@./main

clean:
	rm main
```

- **`build`**: Compiles `main.c` into an executable named `main`.
- **`run`**: Rebuilds `main.c` (if needed) and runs the `main` executable. The `@` symbol before commands suppresses their output in the terminal, making the process cleaner.
- **`clean`**: Deletes the `main` executable, cleaning up your directory.
---
Next: [[Basic Operators]]