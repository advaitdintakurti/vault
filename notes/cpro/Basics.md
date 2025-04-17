## Program from scratch
```bash
> vim main.c            # edit main.c
> gcc main.c -o main    # compile main.c to main
> ./main                # run main
```

## Anatomy of `Hello World!`
```c
#include <stdio.h> // c library where printf() is defined

int main() {  // <return type> main(<parameter type(s)>)
  // main fucntion is run whenever the program is run

  printf("Hello World"); // printf() is called here, with "Hello World"
                         // as its argument

  // every statement must end in a semicolon

  return 0; // if not specified, 0 will be returned by default.
}
```

Generally, a return code of `0` is used to signify success, and other return values are used to signify runtime errors.

`//` is used for single line comments, and `/* */` are used for multi line comments


C code is whitespace agnostic, so all of these lines could be combined into one.

---
Next: [[Makefiles]]