The `printf()` function in C is used to output formatted text to the console. It's part of the standard I/O library (`stdio.h`), and allows you to print various data types using format specifiers.

```c
#include <stdio.h>

int main() {
    int age = 17;
    printf("I am %d years old.\n", age);
}
```

### Format Specifiers

Format specifiers in `printf()` tell the function what type of data to expect and how to format it.

- **`%d` or `%i`**: Integer (decimal)
- `%ld`: `long int`
- `%lld`: `long long int`
- **`%f`**: Floating-point number
- **`%.nf`**: Floating-point number with `n` decimal places
- **`%e` or `%E`**: Scientific notation
- **`%c`**: Single character
- **`%s`**: String (null-terminated array of characters)
- **`%u`**: Unsigned integer
- **`%p`**: Pointer
- **`%%`**: Literal `%` character

You can also print numbers with padded digits using the format specifier `%mnd`
where `m` is the digit to pad with, and `n` is the number of digits to pad it to.
```c
int a = 47;
printf("%05d", a); // Output: 00047
```

### Escape Sequences

Escape sequences are used to represent special characters in strings. They start with a backslash (`\`).

- **`\n`**: Newline
- **`\t`**: Horizontal tab
- **`\\`**: Backslash
- **`\"`**: Double quote
- **`\r`**: Carriage return
- **`\b`**: Backspace
- **`\a`**: Alert (bell)
- **`\0`**: Null character (end of string)

---
Next: [[scanf()]]