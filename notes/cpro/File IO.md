> **Q:** Why do we need to store data in files?
> **A:**  More space available to store data (compared to RAM)
> **A:**  To ensure that data persists over multiple executions.
> **A:**  To work with other programs

### `fopen` / `fclose` 
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *myfile = fopen("data.txt", "w");
  if (!myfile) {
    printf("no file :(");
    exit(73);
  }

  printf("yes file :)");

  fclose(myfile);
}
```

```c
void printfile(FILE *file) {
  char ch = 'a';
  do {
    ch = fgetc(file);
    putchar(ch);
  } while(ch != EOF);
}
```

### Implementing `cp`
```c
#include <stdio.h>

void cpfile(FILE *source, FILE *sink) {
  char ch = 'a';
  do {
    ch = fgetc(source);
    fputc(ch, sink);
  } while(ch != EOF);
}

int main(int argc, char* argv[]) {
  if(argc!=3) {
    printf("err: invalid arguments");
    return 1;
  }

  FILE* source = fopen(argv[1], "r");
  FILE* sink = fopen(argv[2], "w");

  cpfile(source, sink);
}
```

### Reading line by line with`fgets`
**`fgets(char *str, int n, FILE *stream)`**: Reads up to `n-1` characters from `stream` into `str` until a newline or EOF
```c
#include <stdio.h>

void printfile(FILE *file) {
  char buffer[256];
  int ln = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    ln++;
    printf("%d. %s", ln, buffer);
  }
}

int main() {
  FILE *file = fopen("data.txt", "r");
  if (!file) {
    printf("Error opening file.\n");
    return 1;
  }

  printfile(file);
  fclose(file);
}
```


### File Position Functions
- **`ftell(FILE *stream)`**: Returns current position in file
- **`fseek(FILE *stream, long offset, int whence)`**: Sets position in file
  - `SEEK_SET`: Start of file
  - `SEEK_CUR`: Current position
  - `SEEK_END`: End of file
- **`rewind(FILE *stream)`**: Sets position back to start (same as `fseek(file, 0, SEEK_SET)`)

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "r+");
    if (!file) return 1;

    // Get current position
    long pos = ftell(file);
    printf("Current position: %ld\n", pos);

    // Move 10 bytes from start
    fseek(file, 10, SEEK_SET);

    // Move 5 bytes forward from current position
    fseek(file, 5, SEEK_CUR);

    // Move 20 bytes before end of file
    fseek(file, -20, SEEK_END);

    // Go back to start
    rewind(file);

    fclose(file);
}
```

### More Reading Functions
- `getline(char **lineptr, size_t *n, FILE *stream)` : Reads entire line (dynamically allocates)
- `getdelim(char **lineptr, size_t *n, int delim, FILE *stream)`: Reads until delimiter
- `getw(FILE *stream)`: Reads integer
- `getc(FILE *stream)` / `fgetc(FILE *stream)`: Reads character
- `ungetc(int c, FILE *stream)`: Pushes character back to stream
- `fscanf(FILE *stream, const char *format, ...)`: Reads formatted input from a file

```c
#include <stdio.h>
#include <stdlib.h>

void read_file_lines() {
    FILE *file = fopen("data.txt", "r");
    if (!file) return;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // getline automatically allocates memory
    while ((read = getline(&line, &len, file)) != -1) {
        printf("Length: %zu, Line: %s", read, line);
    }

    free(line);
    fclose(file);
}

void read_csv_fields() {
    FILE *file = fopen("data.csv", "r");
    if (!file) return;

    char *field = NULL;
    size_t len = 0;

    // Read comma-separated values
    while (getdelim(&field, &len, ',', file) != -1) {
        printf("Field: %s\n", field);
    }

    free(field);
    fclose(file);
}

void read_formatted_input() {
    FILE *file = fopen("data.txt", "r");
    if (!file) return;

    int id;
    float score;
    char name[50];

    // Read formatted input from file
    while (fscanf(file, "%d %f %49s", &id, &score, name) == 3) {
        printf("ID: %d, Score: %.2f, Name: %s\n", id, score, name);
    }

    fclose(file);
}
```

### Writing Functions
- **`putw(int w, FILE *stream)`**: Writes integer
- **`putc(int c, FILE *stream)`** / **`fputc(int c, FILE *stream)`**: Writes character
- **`fputs(const char *s, FILE *stream)`**: Writes string
- **`fprintf(FILE *stream, const char *format, ...)`**: Formatted output

```c
void write_examples() {
    FILE *file = fopen("output.txt", "w");
    if (!file) return;

    // Write integers
    putw(42, file);
    putw(123, file);

    // Write characters
    putc('A', file);
    fputc('B', file);

    // Write strings
    fputs("Hello\n", file);
    
    // Formatted output
    fprintf(file, "Number: %d, String: %s\n", 42, "test");

    fclose(file);
}
```

### Reading/Writing Binary Data
- **`fwrite(const void *ptr, size_t size, size_t count, FILE *stream)`**: Writes `count` items of data of `size` bytes each from `ptr` to `stream`.
- **`fread(void *ptr, size_t size, size_t count, FILE *stream)`**: Reads `count` items of data of `size` bytes each into `ptr` from `stream`.
- Use "rb" and "wb" modes for binary files

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  float score;
} Record;

void write_record(FILE *file, Record *record) {
  fwrite(record, sizeof(Record), 1, file);
}

void read_record(FILE *file, Record *record) {
  fread(record, sizeof(Record), 1, file);
}

int main() {
  FILE *file = fopen("data.bin", "wb");
  if (!file) {
    printf("Error opening file.\n");
    return 1;
  }

  Record r1 = {1, 95.5};
  write_record(file, &r1);
  fclose(file);

  file = fopen("data.bin", "rb");
  Record r2;
  read_record(file, &r2);
  printf("ID: %d, Score: %.1f\n", r2.id, r2.score);
  fclose(file);
}
```

### Reading/Writing an Array of Structs
```c
#include <stdio.h>

typedef struct Customer {
  char name[100];
  int phone_no;
} Customer;

int main() {
  Customer c[3] = {
      {"Ramu", 90034699}, {"Ammu", 900146939}, {"Thomas", 769834234}};
  FILE *cus_file = fopen("customer.bin", "w");

  fwrite(c, sizeof(Customer), 3, cus_file);
  fclose(cus_file);

  Customer d[3];
  cus_file = fopen("customer.bin", "r");

  fread(&d, sizeof(Customer), 3, cus_file);
  for (int i = 0; i < 3; i++) {
    printf("Customer Read Details: %s, %d", d[i].name, d[i].phone_no);
  }
  fclose(cus_file);

  return 0;
}
```


---
Next: [[Multifile Programming]]