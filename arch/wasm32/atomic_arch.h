#ifndef _INTERNAL_ATOMIC_H
#define _INTERNAL_ATOMIC_H

#include <stdint.h>

#define a_ctz_l a_ctz_l
static inline int a_ctz_l(unsigned long x)
{
	if (x == 0)
		return 32;
	int nTrailingZeros = 0;
	while(!(x&1))
	{
		++nTrailingZeros;
		x >>= 1;
	}
	return nTrailingZeros;
}

#define a_ctz_64 a_ctz_64
static inline int a_ctz_64(uint64_t x)
{
	uint32_t lo = (uint32_t)x;
	if (lo == 0)
		return a_ctz_l((unsigned long)(x >> 32)) + 32;
	else
		return a_ctz_l((unsigned long)lo);
}

#define a_and_64 a_and_64
static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	*p &= v;
}

#define a_or_64 a_or_64
static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	*p |= v;
}

#define a_store_l a_store_l
static inline void a_store_l(volatile void *p, long x)
{
	__c11_atomic_store((_Atomic long*)p, x, __ATOMIC_SEQ_CST);
}

#define a_or_l a_or_l
static inline void a_or_l(volatile void *p, long v)
{
	__c11_atomic_fetch_or((_Atomic long*)p, v, __ATOMIC_SEQ_CST);
}
#define a_cas_p a_cas_p
static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	void* expected = t;
	__c11_atomic_compare_exchange_strong((_Atomic uintptr_t*)p, &expected, s, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	return expected;
}

#define a_cas_l a_cas_l
static inline long a_cas_l(volatile void *p, long t, long s)
{
	long expected = t;
	__c11_atomic_compare_exchange_strong((_Atomic long*)p, &expected, s, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	return expected;
}

#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s)
{
	int expected = t;
	__c11_atomic_compare_exchange_strong((_Atomic int*)p, &expected, s, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	return expected;
}

#define a_or a_or
static inline void a_or(volatile void *p, int v)
{
	__c11_atomic_fetch_or((_Atomic int*)p, v, __ATOMIC_SEQ_CST);
}

#define a_and a_and
static inline void a_and(volatile void *p, int v)
{
	__c11_atomic_fetch_and((_Atomic int*)p, v, __ATOMIC_SEQ_CST);
}

#define a_swap a_swap
static inline int a_swap(volatile int *x, int v)
{
	return __c11_atomic_exchange((_Atomic int*)x, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_add a_fetch_add
static inline int a_fetch_add(volatile int *x, int v)
{
	return __c11_atomic_fetch_add((_Atomic int*)x, v, __ATOMIC_SEQ_CST);
}

#define a_inc a_inc
static inline void a_inc(volatile int *x)
{
	__c11_atomic_fetch_add((_Atomic int*)x, 1, __ATOMIC_SEQ_CST);
}

#define a_dec a_dec
static inline void a_dec(volatile int *x)
{
	__c11_atomic_fetch_sub((_Atomic int*)x, 1, __ATOMIC_SEQ_CST);
}

#define a_store a_store
static inline void a_store(volatile int *p, int x)
{
	__c11_atomic_store((_Atomic int*)p, x, __ATOMIC_SEQ_CST);
}

#endif
