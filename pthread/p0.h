
#define NUM_THREADS 16

/*
 * struct to pass parameters to a dispatched thread
 */
typedef struct {
  uint32_t tnum;     /* thread number */
  int sleep_time;
  double ret_val;    /* some sort of a return data value */
} thread_parm_t;

