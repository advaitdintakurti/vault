![[hw-organization.png]]

#### Buses
Buses carry information back and forth between components. They are designed to transfer fixed-size chunks of bytes known as words. Most machines today have word sizes of either 4 bytes (32 bits) or 8 bytes (64 bits).

#### I/O Devices
Input/Output (I/O) devices connect the system to the external world. Each I/O device is connected to the I/O bus by either a *controller* or an *adapter*. 
- **Controller:**  Chipsets on the device itself or on the motherboard.
- **Adapter**:  Card that plugs into a slot on the motherboard.

#### Memory
The main memory is a temporary storage device that holds both a program and the data it manipulates while the processor is executing the program. Physically, main memory consists of a collection of dynamic random access memory (DRAM) chips. Logically, memory is organized as a linear array of bytes, each with its own unique address (array index) starting at zero.

#### Processor
The **Central Processing Unit (CPU)** is the core component that interprets and executes instructions stored in main memory. At its core lies the **Program Counter (PC)**, a register that holds the address of the next instruction to execute.

From power-on to power-off, the processor continuously executes the instruction at the PC, interprets it, performs the required operation, and updates the PC to the address of the next instruction, which may not always be contiguous.

**Instruction Set Architecture (ISA):** Defines the effects of machine-code instructions, ensuring instructions execute in sequence through a series of steps:
 - **Fetch:** Read the instruction from memory at the PC.
 - **Decode:** Interpret the instruction bits.
 - **Execute:** Perform the specified operation.
 - **Update:** Adjust the PC to the next instruction.
    
**Register File:** A small, fast storage containing multiple word-sized registers with unique names.

**Arithmetic/Logic Unit (ALU):** Performs computations to produce new data or address values.

Here are some examples of the simple operations that the CPU might carry out at the request of an instruction:
- **Load:** Transfer a byte or word from memory to a register.
- **Store:** Transfer a byte or word from a register to memory.
- **Operate:** Use the ALU to compute results from two registers and store them in another.
- **Jump:** Update the PC with a specific address from the instruction.
