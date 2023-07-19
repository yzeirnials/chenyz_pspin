#ifndef HOST
// files in ${PSPIN_RT}/runtime/include
#include <handler.h>
#else
#include <handler_profiler.h>
#endif

#define NUM_INT_OP 0
#define STRIDE 1
#define OFFSET 0
#define MAX_HPUS_IN_CLUSTER 4

#include <packets.h>
#include <spin_dma.h>

#include "filtering.h"
#include <packets.h>
// args including NB_CORES, NB_CLUSTERS, NB_COUNTERS, PACKET_QUEUE_LENGTH ...
#include <spin_conf.h>
#include <stdint.h>

// #include <spin_types.h>

volatile __attribute__((section(".l2_handler_data"))) uint8_t handler_mem[] = {0xde, 0xad, 0xbe, 0xef};

// definition in "handler.h"
// typedef struct handler_args 
// {
//     task_t *task;
//     uint32_t hpu_gid;
//     uint32_t cluster_id;
//     uint32_t hpu_id;
// } handler_args_t;

uint32_t fnvHash(uint8_t* keybyte, size_t length){
    const uint32_t FNV_OFFSET_BASIS = 2166136261U;
    const uint32_t FNV_PRIME = 16777619U;

    uint32_t hash = FNV_OFFSET_BASIS;
    // const uint8_t* key = reinterpret_cast<const uint8_t*>(&keybyte);
    for(size_t i = 0; i < length; i++){
        hash ^= (uint32_t) (keybyte[i]);
        hash *= FNV_PRIME;
    }

    return hash;
}
 


__handler__ void filtering_ph(handler_args_t *args){
    task_t *task = args -> task;

    uint32_t *mem = (uint32_t *) task -> handler_mem; // L2_memory
    uint8_t *key_byte = (uint8_t *) task -> pkt_mem; // L1_memory

    uint32_t hash;
    // generate hash value of keybyte and lengthof(keybyte), stored in hash
    // to be done
    hash = fnvHash(key_byte, KEY_SIZE);

    // hash need to be powers of 2
    hash = FAST_MOD(hash, TOT_WORDS);
    
    //
    *((uint32_t *) task -> l2_pkt_mem) = mem[hash];

    spin_cmd_t cpy;
    uint64_t host_address = task -> host_mem_high;
    host_address = (host_address << 32) | (task -> host_mem_low);
    spin_dma_to_host(host_address, task -> l2_pkt_mem, task -> pkt_mem_size, 0, &cpy);

}

void init_handlers(handler_fn *hh, handler_fn *ph, handler_fn *th, void **handler_mem_ptr){
    volatile handler_fn handlers[] = {NULL, filtering_ph, NULL};
    *hh = handlers[0];
    *ph = handlers[1];
    *th = handlers[2];

    // *handler_mem_ptr = (void*) handler_mem;
}