### Problem 1
Given a positive integer N, return an array of integers with all the integers from 1 to N. But for multiples of 2 the array should have -1 instead of the number, for multiples of 7 the array should have -2 instead of the number, and for multiples of both 2 and 7 the array should have -3 instead of the number.

```nasm
.global function

# void function(long long n, long long* res)
# n -> rdi
# res -> rsi
function:
  xorq %r15, %r15    # i = 0

loop:
  cmpq  %rdi, %r15
  jge   done

  incq  %r15

  movq  %r15, %rax
  cqo

  movq  $14, %rcx
  idivq %rcx
  testq %rdx, %rdx
  je    fourteen

  testb $1, %r15b
  je    two

  movq  %r15, %rax
  cqo

  movq  $7, %rcx
  idivq %rcx
  testq %rdx, %rdx
  je    seven

  movq   %r15, %rax
  jmp    write

fourteen:
  movq $-3, %rax
  jmp write

two:
  movq $-1, %rax
  jmp write

seven:
  movq $-2, %rax
  jmp write

write:
  movq %r15, %rdx
  decq %rdx
  salq $3, %rdx
  movq %rsi, %rcx
  addq %rdx, %rcx

  movq %rax, (%rcx)
  jmp loop

done:
  ret
```

