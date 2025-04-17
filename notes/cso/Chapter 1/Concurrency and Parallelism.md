**Concurrency** refers to a system with multiple, simultaneous activities, while parallelism uses concurrency to make a system run faster. **Parallelism** can be exploited at multiple levels of abstraction in a computer system.

### Thread-Level Concurrency
**Concurrency** enables multiple programs or control flows to execute simultaneously, improving efficiency and multitasking capabilities. Modern systems achieve concurrency through processes and threads, where:

- **Processes** are independent programs.
- **Threads** are control flows within a single process, sharing the same memory space.

![[multiprocessors.png|600]]

#### Simulated Concurrency (Uniprocessor Systems):
A single processor rapidly switches among tasks, creating the illusion of simultaneous execution. This allows:
- Multiple users to interact with a system (e.g., many users accessing a web server).
- A single user to perform multiple tasks (e.g., browsing, word processing, streaming music).

#### True Concurrency (Multiprocessor Systems):
Modern systems use multiple processors or cores under a single operating system kernel. This configuration includes:
- **Multi-core Processors:** Several CPU cores on a single chip, each with dedicated L1/L2 caches and shared higher-level caches and memory interfaces.
- **Hyperthreading:** Enables a single core to execute multiple threads by duplicating some CPU components (e.g., program counters, registers) and sharing others (e.g., floating-point units). Hyperthreading optimizes CPU utilization by switching threads on a cycle-by-cycle basis.

**Benefits of Multiprocessing and Hyperthreading**
1. Reduces the need to simulate concurrency, enabling efficient multitasking.
2. Enhances performance for multi-threaded applications by executing threads in parallel.

Thread-level parallelism is essential for modern applications to fully utilize multi-core and hyperthreaded systems, motivating developers to design programs that exploit parallelism effectively.

![[multicore.png|600]]

### Instruction-Level Parallelism
Modern processors achieve **instruction-level parallelism (ILP)** by executing multiple instructions simultaneously, significantly improving performance compared to early microprocessors.

> Pipelining allows different stages of hardware to operate in parallel, each handling part of a separate instruction. This efficient design enables sustained execution rates close to one instruction per clock cycle. Superscalar processors, capable of executing more than one instruction per cycle, dominate modern architectures.

### SIMD Parallelism
Modern processors support **single-instruction, multiple-data (SIMD)** parallelism, where a single instruction performs multiple operations simultaneously. For instance, recent Intel and AMD processors can use SIMD instructions to add eight pairs of single-precision floating-point numbers (`float`) in parallel.

SIMD is particularly effective for applications involving image, sound, and video processing. While some compilers can automatically extract SIMD parallelism from C programs, a more reliable approach is to use specialized vector data types supported by compilers like GCC. This programming style offers greater control and optimization opportunities.