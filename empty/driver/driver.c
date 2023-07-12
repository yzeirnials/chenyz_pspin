// function definition in "gdriver.h"
#include "gdriver.h"
#include <stdint.h>

uint32_t fill_packet(uint32_t msg_idx, uint32_t pkt_idx, uint8_t *pkt_buff, uint32_t max_pkt_size, uint32_t* l1_pkt_size)
{   
    // nothing to do here

    return max_pkt_size;
}

// int gdriver_add_ectx(const char *hfile, const char *hh, const char *ph, const char *th,
//     fill_packet_fun_t fill_cb, void *l2_img, size_t l2_img_size,
//     void *matching_ctx, size_t matching_ctx_size);
// int gdriver_run();
// int gdriver_fini();
// int gdriver_init(int argc, char **argv, match_packet_fun_t matching_cb, int *ectx_num);

int main(int argc, char **argv){
    const char *handlers_file = "build/empty";
    const char *hh = "empty_hh";
    const char *ph = "empty_ph";
    const char *th = "empty_th";
    int ectx_num;

    gdriver_init(argc, argv, NULL, &ectx_num);
    // gdriver_set_packet_fill_callback(fill_packet);

    gdriver_add_ectx(handlers_file, hh, ph, th, fill_packet, NULL, 0, NULL, 0);
    
    gdriver_run();
    
    
    return ((gdriver_fini()) ? EXIT_SUCCESS : EXIT_FAILURE);
}
