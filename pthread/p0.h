
#define NUM_THREADS 16
#define BIG_ARRAY_DIM0 1024
#define BIG_ARRAY_DIM1 65536

/*
 * struct to pass parameters to a dispatched thread
 */
typedef struct {
  uint32_t tnum;     /* thread number */
  int sleep_time, loop0, loop1;
  double ret_val;    /* some sort of a return data value */
  uint64_t big_array[BIG_ARRAY_DIM0][BIG_ARRAY_DIM1]; /* memory abuse */
} thread_parm_t;

