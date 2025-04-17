
The operating system is a layer of software that connects application programs to the hardware.

![[os1.png|800]]

![[os2.png|700]]

The operating system has two primary purposes: 
- To protect the hardware from misuse by runaway applications.
- To provide applications with simple and uniform mechanisms to interact with hardware devices.

The operating system achieves both goals via the fundamental abstractions shown in Figure 1.11: processes, virtual memory, and files. As this figure suggests, files are abstractions for I/O devices, virtual memory is an abstraction for both the main memory and disk I/O devices, and processes are abstractions for the processor, main memory, and I/O devices.

### Processes
A process is the operating system’s abstraction for a running program. Multiple processes can run concurrently on the same system, and each process appears to have exclusive use of the hardware.

![[contextswitching.png]]
A single CPU can appear to execute multiple processes concurrently by having the processor switch among them. The operating system performs this interleaving with a mechanism known as *context switching*.

The context of a process comprises the state information the CPU needs to execute it, including the current values of the program counter (PC), register file, and main memory contents. At any moment, only one process actively runs on the CPU. During a context switch, the operating system saves the current process's context in memory, restores the new process's context, and transfers CPU control to the new process.

For the new process, this switch is seamless, despite the CPU running other processes in between. Context switching gives the illusion to each process that it has exclusive use of the CPU.

### Kernel
Process transitions are managed by the *kernel*, which is always resident in the memory. When an application requires an OS action, such as reading or writing a file, it issues a system call, transferring control to the kernel. The kernel performs the requested operation and returns control to the application. The kernel is not a separate process but a collection of code and data structures used to manage all processes.

### Threads
A process can consist of multiple execution units, called *threads*, each running in the context of the process and sharing the same code and global data.

Threads provide a mechanism by which an application can perform multiple tasks concurrently.

### Virtual Memory
**Virtual memory** is an abstraction that provides each process with the illusion that it has exclusive use of the main memory. Each process has the same uniform address space, which starts at address zero and continues to the largest possible address.

The virtual address space seen by each process consists of a number of well-defined areas, each with a specific purpose.

Starting with the lowest addresses and working up, these areas are:

- **Program code and data**: Initialized from the executable object file
- **Heap**: Expands and contracts dynamically at run time
- **Shared libraries**: Hold the code and data for shared libraries
- **Stack**: Used by the process to store function parameters, local variables, and return information
- **Kernel virtual memory**: The top region of the address space is reserved for the kernel

![[virtualaddressspace.png]]

Virtual memory abstracts RAM allocation, enabling processes to use large address spaces regardless of available physical RAM. It simplifies memory management by providing a uniform address format for each process, independent of hardware. Additionally, it ensures memory protection, preventing one process from accessing another's memory.

### Files
A **file** is a sequence of bytes. All input and output in the system is performed in terms of reads and writes to files, using a set of system calls called *Unix I/O*. Files are stored on external devices such as disks. Each I/O device, such as a keyboard, display, or network, is modeled as a file, and the operating system provides a uniform set of system calls that applications use to read and write files.