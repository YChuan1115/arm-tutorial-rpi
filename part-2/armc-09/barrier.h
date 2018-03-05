#ifndef BARRIER_H
#define BARRIER_H

/*
 * Data memory barrier
 * No memory access after the DMB can run until all memory accesses before it
 * have completed
 */
#ifdef RPI3
#define dmb() asm volatile \
		("DMB ISHST");
#else
#define dmb() \
		asm volatile \
		("mcr p15, #0, %[zero], c7, c10, #0" : : [zero] "r" (0) ); \
		asm volatile \
		("mcr p15, #0, %[zero], c7, c14, #0" : : [zero] "r" (0) ); \
		asm volatile \
		("mcr p15, #0, %[zero], c7, c7, #0" : : [zero] "r" (0) );
#endif

/*
 * Data synchronisation barrier
 * No instruction after the DSB can run until all instructions before it have
 * completed
 */
#define dsb() asm volatile \
		("mcr p15, #0, %[zero], c7, c10, #1" : : [zero] "r" (0) )

#define invmva() asm volatile \
		("mcr p15, #0, %[zero], c7, c10, #1" : : [zero] "r" (0) )

#define invset() asm volatile \
		("mcr p15, #0, %[zero], c7, c10, #2" : : [zero] "r" (0) )
/*
 * Clean and invalidate entire cache
 * Flush pending writes to main memory
 * Remove all data in data cache
 */
#define flushcache() 

//asm volatile \
		("mcr p15, #0, %[zero], c7, c14, #0" : : [zero] "r" (0) )

#endif	/* BARRIER_H */