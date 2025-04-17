
A **stack** is a linear data structure that operates in a **Last In, First Out (LIFO)** manner, where the last element added is the first to be removed.

### Operations

1. **Push**: Adds an element to the top of the stack.
2. **Pop**: Removes and returns the top element.
3. **Peek/Top**: Returns the top element without removing it.
4. **isEmpty**: Checks if the stack is empty.
5. **Size**: Determine the number of elements in the stack.
6. **Display**: Print all elements in the stack

## Array Implementation

Fixed size. Easy to implement but limited by predefined size.

```c
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Initialize stack
void init(Stack* s) {
    s->top = -1;
}

// Check if stack is full
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// Check if stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Push operation
void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow :(\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

// Pop operation
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow :(\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// Peek operation
int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Empty Stack :(\n");
        return -1;
    }
    return s->arr[s->top];
}

// Example usage
int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    printf("Is Empty: %d\n", isEmpty(&s)); // 0
    printf("Top element: %d\n", peek(&s)); // 20
    printf("Popped: %d\n", pop(&s));       // 20
    printf("Popped: %d\n", pop(&s));       // 10
    printf("Is Empty: %d\n", isEmpty(&s)); // 1

    return 0;
}
```

#### Dynamic Stack Expansion

If the static array is too small, the stack must grow. We can either:

**Double the Size**:
 - Allocate a new array of size `2 * old_size`.
 - Copy elements to the new array.
 - **Time Complexity**: O(n) for n elements.
 
**Increment by a Constant `c`**:
 - Allocate a new array of size `old_size + c`.
 - Copy elements to the new array.
 - **Time Complexity**: O(n<sup>2</sup>/c) over n elements.


### Balanced Parentheses

**Problem**: Check if every opening parenthesis `(`, `{`, `[` has a matching closing parenthesis `)`, `}`, `]`

**Approach**:
1. Use a stack to keep track of opening brackets.
2. Push opening brackets into the stack.
3. For each closing bracket, check if the top of the stack has the matching opening bracket.
4. If unmatched brackets exist or the stack isn't empty at the end, the expression is unbalanced.

```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

bool is_empty(Stack *s) {
    return s->top == -1;
}

bool is_full(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char value) {
    if (!is_full(s)) {
        s->items[++(s->top)] = value;
    }
}

char pop(Stack *s) {
    if (!is_empty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(Stack *s) {
    return s->items[s->top];
}

bool is_balanced(const char *expression) {
    Stack s;
    init(&s);

    for (int i = 0; i < strlen(expression); i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (is_empty(&s)) return false;
            char top = pop(&s);
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    return is_empty(&s);
}

int main() {
    const char *expr = "({[()]})";
    if (is_balanced(expr)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    return 0;
}
```

### Infix to Postfix

**Problem**: Convert an infix expression like `a + b * c` to postfix (Reverse Polish Notation) `a b c * +`.

**Approach**:
1. Use a stack to store operators.
2. For each token in the expression:
    - If its an operand, append it to the result.
    - If its an operator, pop operators of higher/equal precedence from the stack and append them to the result, then push the current operator.
    - Push `(` to the stack and pop until `)` when encountered.
3. At the end, append any remaining operators in the stack.

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char items[100];
    int top;
} Stack;

int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infix_to_postfix(const char *infix, char *postfix) {
    Stack s;
    init(&s);
    int j = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;  // Operand
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!is_empty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);  // Remove '('
        } else if (is_operator(ch)) {
            while (!is_empty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (!is_empty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX] = "a+b*(c^d-e)^(f+g*h)-i";
    char postfix[MAX];

    infix_to_postfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    return 0;
}
```

### Evaluating Postfix Notation

**Problem**: Evaluate a postfix expression

**Approach**:
1. Use a stack to store operands.
2. Traverse the expression:
    - Push numbers onto the stack.
    - When encountering an operator, pop two numbers, apply the operator, and push the result back onto the stack.
3. The final result will be the only value in the stack.

### Infix to Prefix

**Problem**: Convert an infix expression `a + b * c` to prefix (Polish Notation) `+ a * b c`.

**Approach**:
1. Reverse the infix expression.
2. Swap `(` with `)` and vice versa.
3. Convert the reversed infix to postfix.
4. Reverse the resulting postfix to get the prefix.

**Example:** `(a + b) * c`
1. Reverse Infix: `c * (b + a)`
2. Swap Parentheses: `c * ) b + a (`
3. Convert to Postfix:
    - Using the Infix to Postfix algorithm, the postfix expression is `c b a + *`.
4. Reverse Postfix: `* + a b c`.

#### Implementation:

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infix_to_prefix(const char *infix, char *prefix) {
    char reversed[MAX];
    strcpy(reversed, infix);
    reverse_string(reversed);

    for (int i = 0; i < strlen(reversed); i++) {
        if (reversed[i] == '(') reversed[i] = ')';
        else if (reversed[i] == ')') reversed[i] = '(';
    }

    char postfix[MAX];
    infix_to_postfix(reversed, postfix);

    reverse_string(postfix);
    strcpy(prefix, postfix);
}
```

---

## Linked List Implementation

Dynamic size. Uses pointers to allocate memory as needed.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Push operation
void push(Node** top, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Heap Overflow\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

// Pop operation
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        return -1; // Indicating error
    }
    Node* temp = *top;
    int value = temp->data;
    *top = (*top)->next;
    free(temp);
    return value;
}

// Peek operation
int peek(Node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1; // Indicating error
    }
    return top->data;
}

// Example usage
int main() {
    Node* stack = NULL;

    push(&stack, 10);
    push(&stack, 20);
    printf("Top element: %d\n", peek(stack)); // 20
    printf("Popped: %d\n", pop(&stack));      // 20
    printf("Popped: %d\n", pop(&stack));      // 10
    printf("Is Empty: %d\n", stack == NULL);  // 1

    return 0;
}
```

---

### Queue using two stacks
-> **Enqueue:** Push the new element onto `stack1`
-> **Dequeue:** If the second stack (`stack2`) is empty, move all elements from `stack1` to `stack2` by popping from `stack1` and pushing them onto `stack2`, and then pop the top element from `stack2`.

Or you can do it the other way round. Depends on which operation you want to be more efficient.


### Stack using two queues
-> **Push:** Enqueue the element into `queue1`.
-> **Pop:** Dequeue elements from `queue1` one by one and enqueue them into `queue2` until only one element remains, then dequeue the last element (this is the stack’s top element). Swap the roles of `queue1` and `queue2`.

