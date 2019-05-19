#ifndef LOCK_H
#define LOCK_H

hidden void __lock(volatile int *);
hidden void __unlock(volatile int *);
#define LOCK(x) ((void)x)
#define UNLOCK(x) ((void)x)
#endif
