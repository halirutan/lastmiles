
#define NUM_THREADS 16
#define SLEEP_TIME 3

/*
 * struct to pass parameters to a dispatched thread
 */
typedef struct {
  uint32_t tnum;     /* thread number */
  int sleep_time;
  double ret_val;
} thread_parm_t;

