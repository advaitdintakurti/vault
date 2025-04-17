Amdahl's law states that when we speed up one part of a system, the overall speedup depends on how significant this part was and how much it sped up. Consider a system where an application requires time T<sub>old</sub> to execute. If a part of the system that initially consumes a fraction α of this time is sped up by a factor of k, the overall execution time will be:
> T<sub>new</sub> = (1 - α)T<sub>old</sub> + (αT<sub>old</sub>)/ k = T<sub>old</sub>((1 - α) + α/k)

From this, speedup **S = T<sub>old</sub>/T<sub>new</sub>** can be computed as:
> S = 1/((1 - α) + α/k)

For example, if the part of the system that initially consumed 60% of the time (α = 0.6) is sped up by a factor of 3 (k = 3), the speedup will be: `1/(0.4 + 0.6/3) = 1.67x`.

**Even though a major part of the system has been improved substantially, the net speedup is less than the speedup of the improved part.**

To significantly speed up the entire system, the speed of a very large fraction of the overall system must be improved

One special case of Amdahl's law is when k is set to ∞, meaning a part of the system is sped up to the point where it takes a negligible time.

The speedup in this case is **S<sub>∞</sub> = 1/(1 - α)**

For example, if 60% of the system is sped up to the point where it takes a negligible time, the net speedup will be `1/0.4 = 2.5x`

Amdahl's law can be applied to improving any process, including manufacturing and academics.