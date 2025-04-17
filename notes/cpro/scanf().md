The `scanf()` function in C is used to read formatted input from the standard input (typically the keyboard). It’s the counterpart to `printf()` and allows you to capture user input.

```c
#include <stdio.h>

int main() {
    int age;
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("You are %d years old.\n", age);
    return 0;
}
```

`scanf()` has the same format specifiers and escape codes as `printf()`

### Buffer Overflow
When reading strings with `%s`, ensure the input fits in the buffer to avoid overflow. Use `%Ns` to limit the input size, where `N` is the maximum number of characters to read.

```c
char name[20];
scanf("%19s", name);
```

---
Next: [[Loops]]