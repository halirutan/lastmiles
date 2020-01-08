
#define NUM_THREADS 16
#define BIG_ARRAY_DIM0 128
#define BIG_ARRAY_DIM1 65536

/*
 * struct to pass params to dispatched thread
 */
typedef struct {
  uint32_t tnum;
  int sleep_time, loop0, loop1;
  double ret_val;
  uint64_t big_array[BIG_ARRAY_DIM0][BIG_ARRAY_DIM1];
} thread_parm_t;

