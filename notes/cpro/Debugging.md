Compile your code with `-g` to include debugging information.
```bash
gcc -g main.c -o main
```

## `gdb` - GNU Debugger

Launch `gdb`:
```bash
gdb ./main
```

#### `gdb` commands

 **Run the Program**: Start executing the program within `gdb`.
```bash
run [args]
```
> **Example**: `run 10 12` runs the program with `10` and `12` as arguments.

**Set Breakpoints**: Stop execution at specific lines or functions to examine state.
```bash
break <line_number>
break <function_name>
```
> **Example**: `break 10` sets a breakpoint at line 10.

**View Breakpoints**: List all breakpoints.
```bash
info breakpoints
```

**Remove Breakpoints**: Delete a breakpoint by number.
```bash
delete <breakpoint_number>
```

#### Navigation

**Step Through Code**:
- `next` (or `n`): Move to the next line, skipping function calls.
- `step` (or `s`): Move to the next line, stepping into functions.

**Continue Execution**: Resume running until the next breakpoint.
```bash
continue
```

**Finish**: Execute until the current function returns.
```bash
finish
```

**Quit `gdb`:
```bash
quit
```

#### **Examination**

**Print Variables**: Display variable values or expressions.
```bash
print <variable_name>
```
> Example: `print x` shows the value of `x`.

**Inspect Memory**:
- `x <address>`: Examine memory at a specific address.
- Example: `x/4x &array` shows 4 hexadecimal values starting from `array`.

**View Stack Trace**: 
See the function call stack, useful for tracking where errors occur.
```bash
backtrace (or bt)
```

**Inspect Function Arguments**: 
Display function arguments and local variables in the current frame.
```bash
info locals
info args
```

#### 6. **Debugging Common Issues**

**Segmentation Faults**: Use `backtrace` when the program crashes to see the call stack and find the source of the error.

**Watch Variables**: Monitor variables for changes, automatically stopping execution when they change.
```bash
watch <variable_name>
```

**Inspect Registers**: View CPU register values if debugging low-level issues.
```bash
info registers
```

#### **Advanced Techniques**

**Conditional Breakpoints**: Only stop when a condition is met.
```bash
break <line> if <condition>
```
> **Example**: `break 15 if x > 5`

**Log Variable Values**: Use `display` to automatically print a variable’s value at each step or breakpoint.
```bash
display <variable>
```

**Editing and Rerunning Code**: You can modify your code, recompile, and use `gdb`’s `run` command again without leaving the debugger.

---

#### Example
```bash
gcc -g main.c -o main
gdb ./main
(gdb) break main        # Set a breakpoint at main
(gdb) run               # Start the program
(gdb) next              # Move to the next line
(gdb) print variable    # Print the value of a variable
(gdb) continue          # Continue to the next breakpoint
(gdb) backtrace         # Show the stack trace if there's a crash
(gdb) quit              # Exit the debugger
```

Here’s a straightforward guide to using Valgrind for detecting memory issues in C programs.

---

## Valgrind

Valgrind is a tool to help find memory leaks, invalid memory access, and other memory-related errors.

#### Running Valgrind
```bash
valgrind ./program
```

#### Common Valgrind Options

```bash
valgrind [options] ./program [program_args]
```

**Memory Leak Check**:
```bash
valgrind --leak-check=full ./program
```
> `--leak-check=full`: Provides detailed leak information.

**Show Uninitialized Memory**:
```bash
valgrind --track-origins=yes ./program
```
> `--track-origins=yes`: Shows where uninitialized memory was first allocated.

**Suppressing Warnings**:
Valgrind may show warnings for libraries. Use a suppression file to ignore these.
```bash
valgrind --suppressions=<file> ./program
```

#### Reading Valgrind Output

**Memory Leaks**: Look for lines like:
```
definitely lost: 24 bytes in 1 blocks
indirectly lost: 0 bytes in 0 blocks
```
> **Definitely lost**: Memory that your program failed to free.
> **Indirectly lost**: Memory pointed to by lost pointers.

**Invalid Reads/Writes**:
```
Invalid read of size 4
```
> Indicates your program accessed memory it shouldn't have, usually due to going out of bounds.

**Uninitialized Value Usage**:
```
Conditional jump or move depends on uninitialized value(s)
```
> Happens when variables are used without being initialized.

#### Example
   ```bash
   gcc -g main.c -o main
   valgrind --leak-check=full --track-origins=yes ./main
   ```

This runs `example` under Valgrind with detailed checks for leaks and uninitialized memory. Check the output to see any issues Valgrind detects.