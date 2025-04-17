 Custom data type that groups variables of different types.
```c
 struct Name {
    dataType member1;
    dataType member2;
    ...
};
```
- `Name`: The name of the structure.
- `member1`, `member2`, etc.: The data members of the structure.

You can declare variables and access members using the dot (`.`) operator:
```c
struct Student {
    char name[100];
    char email[100];
    float marks;
};

// ...

struct Student advait = {
    "Advait Dintakurti",
    "advait.dintakurti@students.iiit.ac.in",
    0 // :(
};

// pls #include <string.h>
strcpy(advait.email, "advait.dintakurti@research.iiit.ac.in"); // :(

// ...

printf("Name: %s\n", advait.name);
printf("Email: %s\n", advait.email);
printf("Marks: %d\n", advait.marks);
```


### Array of Structures
```c
struct Student arr[360];

// ...

for(int i = 0; i < 360; i++) {
    scanf("%s %s %d", &arr[i].name, &arr[i].email, &arr[i].marks)
}

// ...

sort(students); // sort based on marks

for(int i = 0; i < 360; i++) {
    printf("%s %d" arr[i].name, arr[i].marks)
}
```


### `typedef`
```c
struct Rectangle {
  float height;
  float width;
};

typedef struct Rectangle Rect;

void print(Rect rect) {
  printf("Height: %f | Width: %f", rect.height, rect.width);
}

int main() {
  Rect rect = { 4.5, 5.6 };
  print(rect);
  
  return 0;
}
```

#### `typedef` for arrays
You can also use `typedef` to define aliases for arrays:
```c
typedef int Coordinates[2];

// ...

Coordinates point = {3,4};
```

### Arrow operator
When working with structure pointers, the members can be accessed using the arrow operator (`->`), which is a shorthand for dereferencing the pointer and accessing the member.
```c
rect->height
// is equivalent to:
(*rect).height
```


---
Next: [[Enums]]