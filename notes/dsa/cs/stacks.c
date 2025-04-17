#include <stdio.h>
#include <stdlib.h>

// -- Stacks --
typedef struct {
    int top;
    int capacity;
    int *array;
} Stack;

Stack *createStack(int capacity)
{
    return &(Stack){-1, capacity, malloc(capacity * sizeof(int))};
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int item) {
    !isFull(stack) ? stack->array[++stack->top] = item : 0;
}

int pop(Stack *stack) {
    return isEmpty(stack) ? -1 : stack->array[stack->top--];
}

int peek(Stack *stack) {
    return isEmpty(stack) ? -1 : stack->array[stack->top];
}

// Function to reverse a stack using recursion
void insertbottom(Stack *s, int item) {
    if (isEmpty(s)) {
        push(s, item);
        return;
    }
    int temp = pop(s);
    insertbottom(s, item);
    push(s, temp);
}

void reverseStack(Stack *s) {
    if (isEmpty(s)) return;
    int temp = pop(s);
    reverseStack(s);
    insertbottom(s, temp);
}

// Reverse a stack using another temporary stack
void reverseStack2(Stack *s) {
    Stack *temp = createStack(100);
    while (!isEmpty(s)) {
        int item = pop(s);
        push(temp, item);
    }
    while (!isEmpty(temp)) {
        int item = pop(temp);
        push(s, item);
    }
}

// Function to sort a stack in ascending order
void sortedInsert(Stack *s, int x) {
    if (isEmpty(s) || x > peek(s)) {
        push(s, x);
        return;
    }
    int temp = pop(s);
    sortedInsert(s, x);
    push(s, temp);
}

void sortStack(Stack *s) {
    if (!isEmpty(s)) {
        int x = pop(s);
        sortStack(s);
        sortedInsert(s, x);
    }
}

// Function to check if brackets are balanced
int checkbalanced(char *expr) {
    Stack *s = createStack(100);
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
            push(s, expr[i]);
        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
            if (isEmpty(s)) return 0;
            if ((peek(s) == '(' && expr[i] == ')') ||
                (peek(s) == '{' && expr[i] == '}') ||
                (peek(s) == '[' && expr[i] == ']'))
                pop(s);
            else return 0;
        }
    }
    return isEmpty(s);
}

// Function to evaluate postfix expression
int evaluatePostfix(char *exp) {
    Stack *s = createStack(100);
    for (int i = 0; exp[i]; i++) {
        if (exp[i] >= '0' && exp[i] <= '9')
            push(s, exp[i] - '0');
        else {
            int val1 = pop(s);
            int val2 = pop(s);
            switch (exp[i]) {
                case '+': push(s, val2 + val1); break;
                case '-': push(s, val2 - val1); break;
                case '*': push(s, val2 * val1); break;
                case '/': push(s, val2 / val1); break;
            }
        }
    }
    return pop(s);
}

// Function to evaluate infix expression
int evaluateInfix(char *exp) {
    Stack *nums = createStack(100);
    Stack *ops = createStack(100);
    char *ptr = exp;
    while (*ptr) {
        if (*ptr >= '0' && *ptr <= '9') {
            push(nums, *ptr - '0');
        } else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            while (!isEmpty(ops) && peek(ops) != '(' && 
                  ((peek(ops) == '*' || peek(ops) == '/') || 
                   (*ptr != '*' && *ptr != '/'))) {
                int b = pop(nums), a = pop(nums);
                char op = pop(ops);
                push(nums, op == '+' ? a + b : op == '-' ? a - b : 
                            op == '*' ? a * b : a / b);
            }
            push(ops, *ptr);
        } else if (*ptr == '(') {
            push(ops, *ptr);
        } else if (*ptr == ')') {
            while (peek(ops) != '(') {
                int b = pop(nums), a = pop(nums);
                char op = pop(ops);
                push(nums, op == '+' ? a + b : op == '-' ? a - b : 
                            op == '*' ? a * b : a / b);
            }
            pop(ops);
        }
        ptr++;
    }
    while (!isEmpty(ops)) {
        int b = pop(nums), a = pop(nums);
        char op = pop(ops);
        push(nums, op == '+' ? a + b : op == '-' ? a - b : 
                    op == '*' ? a * b : a / b);
    }
    return pop(nums);
}

// Infix to Postfix
int precedence(char op) {
    return op == '+' || op == '-' ? 1 : op == '*' || op == '/' ? 2 : -1;
}

void infix_to_postfix(const char *infix, char *postfix) {
    Stack *s = createStack(100);
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(s) && peek(s) != '(')
                postfix[k++] = pop(s);
            pop(s);
        } else {
            while (!isEmpty(s) && precedence(infix[i]) <= precedence(peek(s)))
                postfix[k++] = pop(s);
            push(s, infix[i]);
        }
    }
    while (!isEmpty(s))
        postfix[k++] = pop(s);
    postfix[k] = '\0';
}

// Infix to Prefix
void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infix_to_prefix(const char *infix, char *prefix) {
    char reversed[100000];
    strcpy(reversed, infix);
    reverse_string(reversed);

    for (int i = 0; i < strlen(reversed); i++) {
        if (reversed[i] == '(') reversed[i] = ')';
        else if (reversed[i] == ')') reversed[i] = '(';
    }

    char postfix[100000];
    infix_to_postfix(reversed, postfix);

    reverse_string(postfix);
    strcpy(prefix, postfix);
}

// -- Monotonic Stack --

// Next Greater Element
void nextGreaterElement(int *arr, int n) {
    Stack *s = createStack(100);
    for (int i = 0; i < n; i++) {
        while (!isEmpty(s) && arr[i] > arr[peek(s)]) {
            printf("%d -> %d\n", pop(s), arr[i]);
        }
        push(s, i);
    }
    while (!isEmpty(s)) {
        printf("%d -> -1\n", pop(s));
    }
}

// Next Greater Element (Circular)
void nextGreaterElementCircular(int *arr, int n) {
    Stack *s = createStack(100);
    for (int i = 0; i < 2 * n; i++) {
        while (!isEmpty(s) && arr[i % n] > arr[peek(s)]) {
            printf("%d -> %d\n", pop(s), arr[i % n]);
        }
        if (i < n) push(s, i % n);
    }
    while (!isEmpty(s)) {
        printf("%d -> -1\n", pop(s));
    }
}