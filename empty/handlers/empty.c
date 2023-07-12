#ifndef HOST
// files in ${PSPIN_RT}/runtime/include
#include <handler.h>
#include <packets.h>
#include <spin_dma.h>
#else
#include <handler_profiler.h>
#endif

#ifndef NUM_INT_OP
#define NUM_INT_OP 0
#endif

volatile __attribute__((section(".l2_handler_data"))) uint8_t handler_mem[] = {0xde, 0xad, 0xbe, 0xef};

// definition in "handler.h"
// typedef struct handler_args 
// {
//     task_t *task;
//     uint32_t hpu_gid;
//     uint32_t cluster_id;
//     uint32_t hpu_id;
// } handler_args_t;

__handler__ void empty_ph(handler_args_t *args){ 
#if (NUM_INT_OP > 0)
    volatile int xx = 0;
    int x = xx;
    for(int i = 0; i < NUM_INT_OP; i++){
        x = x * i;
    }
    xx = i;
#endif
}

void init_handlers(handler_fn *hh, handler_fn *ph, handler_fn *th, void **handler_mem_ptr){
    volatile handler_fn handlers[] = {NULL, empty_ph, NULL};
    *hh = handlers[0];
    *ph = handlers[1];
    *th = handlers[2];

    *handler_mem_ptr = (void*) handler_mem;
}