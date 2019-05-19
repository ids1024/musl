static struct pthread __pthread;

static inline struct pthread *__pthread_self(void) {
  // TODO: multiple threads
  return &__pthread;
}

#define TP_ADJ(p) (p)

#define CANCEL_REG_IP 16
