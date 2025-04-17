### Arguments
```c
#include <stdio.h>

int main(int argc, char* argv[]) {

    printf("You passed %d arguments", argc);

    for(int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}
```

```
$ ./scratch i am passing arguments

You passed 5 arguments
Argument 0: /home/nuxsh/cpro/scratch/scratch
Argument 1: i
Argument 2: am
Argument 3: passing
Argument 4: arguments
```

---
Next: [[File IO]]