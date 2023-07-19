// function definition in "gdriver.h"
#include "gdriver.h"
#include <stdint.h>
// #include <cstdint>
#include <time.h>
#include <assert.h>
#include "../handlers/filtering.h"

#define SEED 6598736

uint32_t fill_packet(uint32_t msg_idx, uint32_t pkt_idx, uint8_t *pkt_buff, uint32_t max_pkt_size, uint32_t* l1_pkt_size)
{   
    assert(max_pkt_size >= KEY_SIZE);
    for(int i = 0; i < KEY_SIZE / sizeof(uint32_t); i++){
        ((uint32_t *)pkt_buff)[i] = rand();
    }
    return max_pkt_size;
}

// int gdriver_add_ectx(const char *hfile, const char *hh, const char *ph, const char *th,
//     fill_packet_fun_t fill_cb, void *l2_img, size_t l2_img_size,
//     void *matching_ctx, size_t matching_ctx_size);
// int gdriver_run();
// int gdriver_fini();
// int gdriver_init(int argc, char **argv, match_packet_fun_t matching_cb, int *ectx_num);

uint16_t hashmult(const uint16_t key){
    uint16_t hash = 0;
    uint8_t *key_byte = (uint8_t *) &key;
    for(uint16_t i = 0; i < sizeof(uint16_t); i++){
        hash = hash * 31 + (key_byte[i]);
    }
    return hash;
}

void fill_htable(uint32_t *vec, uint32_t length){
    for(uint32_t i = 0; i < length; i++){
        vec[hashmult((uint16_t)i)] = i;
    }
}

int main(int argc, char **argv){
    const char *handlers_file = "build/filtering";
    const char *hh = NULL;
    const char *ph = "filtering_ph";
    const char *th = NULL;
    int ectx_num;

    // srand(SEED);
    srand((unsigned int)(time(0)));

    uint32_t *vec = (uint32_t *)malloc(sizeof(uint32_t) * (TOT_WORDS));
    fill_htable(vec, TOT_WORDS);

    gdriver_init(argc, argv, NULL, &ectx_num);
    // gdriver_init(argc, argv, handlers_file, hh, ph, th);

    // gdriver_set_packet_fill_callback(fill_packet);
    gdriver_add_ectx(handlers_file, hh, ph, th, fill_packet, (void*) vec, sizeof(uint32_t) * (TOT_WORDS), NULL, 0);
    

    gdriver_run();
    
    assert(gdriver_fini() == EXIT_SUCCESS);

    free(vec);

    return 0;
    
    // return ((gdriver_fini()) ? EXIT_SUCCESS : EXIT_FAILURE);
}