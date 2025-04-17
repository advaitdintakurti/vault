![[running-hello-1.png|600]]
Initially, the shell program is executing its instructions, waiting for us to type a command. 

As we type `./hello` on the keyboard, the shell program reads each one into a register and then stores it in memory

When we hit the enter key on the keyboard, the shell loads the executable `hello` file by executing a sequence of instructions that copies the code and data in the `hello` object file from disk to main memory.

![[running-hello-2.png|500]]

Using a technique called *direct memory access (DMA)*, the data travels directly from disk to main memory.

![[running-hello-3.png|550]]
Once the code and data in the `hello` object file are loaded into memory, the processor starts executing the instructions in the `hello` program’s main routine. These instructions copy the bytes in the `hello, world\n` string from memory to the register file, and from there to the display device, where they are displayed on the screen.