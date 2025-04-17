>All information in a system is represented as a bunch of bits.

```c
#include <stdio.h>

int main() {
    printf("hello, world\n");
    return 0;
}
```

The `hello.c` program is stored in a file and is organized as 8-bit chunks called bytes. Each byte has an integer value that corresponds to some character.

![[hello-world-ascii.png]]

> ASCII (American Standard Code for Information Interchange) is used above.

Files that only contain ASCII characters are called *text files*, others are called *binary files.*