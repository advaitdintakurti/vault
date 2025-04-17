Enums are user-defined types that assign names to integer constants.
```c
enum EnumName { constant1, constant2, ... };
```

Constants are assigned integer values starting from `0`, unless specified.
```c
enum Weekday { Sunday, Monday, Tuesday };
// Sunday=0, Monday=1, Tuesday=2
```

You can assign specific values, and the subsequent constants continue from the last value. 
```c
enum Weekday { Sunday = 1, Monday = 5, Tuesday };
// Sunday=1, Monday=5, Tuesday=6
```

Multiple constants can share the same value, _but why would you do that?_
```c
enum Sample { A = 1, B = 1, C };  // A=1, B=1, C=2
```

> Enums are useful when dealing with `switch/case` statements

```c
enum Weekday {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

int main() {
    enum Weekday today = Monday;
    switch (today) {
        case Sunday: printf("Sunday\n"); break;
        case Monday: printf("Monday\n"); break;
    }
}
```

---
Next: [[Linked List]]