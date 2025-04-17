`char` arrays.

```c
char str[] = {'H', 'e', 'l', 'l', 'o'};
printf("%s", str);
```

### `string.h`
`<string.h>` is a header file that contains functions for manipulating strings.
#### `strlen`

```c
size_t strlen(const char *str);
```

Returns the length of the null-terminated string `str`, excluding `\0`

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "hello, world";
    size_t len = strlen(str);
    printf("%zu\n", str, len);  // output: 12
    return 0;
}
```

> **NOTE:** `%zu` is used to print the value of a `size_t` type variable

#### `strcpy`

```c
char *strcpy(char *dest, const char *src);
```

Copies the null-terminated string `src` into `dest`, including the null terminator, and then returns a pointer to `dest`.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "hello";
    char dest[20];

    strcpy(dest, src);
    printf("%s\n", dest);  // output: "hello"
    return 0;
}
```

#### `strcat`

```c
char *strcat(char *dest, const char *src);
```

Appends the `src` string to the end of `dest`, including the null terminator of `src`.  The resulting string in `dest` is null-terminated. Returns a pointer to `dest`.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char dest[20] = "hello, ";
    char src[] = "world";

    strcat(dest, src);
    printf("%s\n", dest);  // Output: "hello, world"
    return 0;
}
```

#### `memset`

```c
void *memset(void *str, int c, size_t n);
```

Sets the first `n` bytes of the memory area pointed to by `str` to the byte value `c` (converted to an `unsigned char`). Returns a pointer to `str`.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    
    memset(buffer, 0, sizeof(buffer)); // sets all bytes in buffer to \0

    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]);  // output: 0 0 0 0 0 0 0 0 0 0
    }
    printf("\n");
    return 0;
}
```

#### Tokenizing strings with `strtok`

```c
char *strtok(char *str, const char *delim)
```

`strtok` tokenizes a string by replacing the specified delimiter with a null character (`\0`)

```c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char input[64] = "Who, Where, When, What, Why";
    int i = 0;

    token = strtok(input, ",");
    while(token !=  NULL) {
        token = strtok(input, ",");
        printf("%s\n", token);
    }
}
```

We can also specify multiple delimiters like so:
```c
    char input[64] = "Who, Where, When, What / Why";
    int i = 0;

    token = strtok(input, ",/");
    while(token !=  NULL) {
        token = strtok(input, ",/");
        printf("%s\n", token);
    }
```

> **Note:** `strtok` is pretty gay because:
>     A. It is destructive (replaces delims with `\0`s)
>     B. Not thread-safe (stores current location in static variable)
>          Use `strtok_r` for multiple threads
>     C. Not very versatile.

---
Next: [[Memory Allocation]]