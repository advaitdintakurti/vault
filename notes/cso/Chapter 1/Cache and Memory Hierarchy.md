Copying information from one place to another is a big overhead that slows down the process of execution, and thus we need to make the copy operations *as fast as possible.*

> Because of physical laws, larger storage devices are slower than smaller ones. A typical register file stores only a few hundred bytes of information, as opposed to billions of bytes in the main memory. However, the processor can read data from the register file almost 100 times faster than from memory. This causes a  processor–memory gap in speed.

To deal with the difference in speed system designers include smaller, faster storage devices called *cache memories* (or simply *caches*) that serve as temporary staging areas for information that the processor is likely to need in the near future.
![[cache.png]]

The cache are divided into tiers, with (inversely) varying sizes and access speeds.
- **L1 Cache:**  Holds tens of thousands of bytes and can be accessed nearly as fast as the register.
- **L2 Cache:**  Holds 10-100 times as much as the L1 cache, but is also around 5 times slower.
- **L3 Cache:**  Newer and more powerful systems also have a third level of cache.

These caches are implemented with a hardware technology known as static random access memory.

### Memory Hierarchy
The storage devices in a computer system are organized in a *memory hierarchy*.

![[memory-hierarchy.png]]

The main idea of a memory hierarchy is that storage at one level serves as a cache for storage at the next lower level.