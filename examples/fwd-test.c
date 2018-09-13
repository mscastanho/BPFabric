#include <linux/if_ether.h>
#include <linux/ip.h>
// #include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include <net/nsh.h>
#include "ebpf_switch.h"
#include "ebpf_helpers.h"

struct bpf_map_def SEC("maps") inports = {
    .type = BPF_MAP_TYPE_HASH,
    .key_size = 6, // MAC address is the key
    .value_size = sizeof(uint32_t),
    .max_entries = 256,
};

void dump (char *desc, void *addr, int len);


uint64_t prog(struct packet *pkt)
{
    struct ethhdr *eth = pkt->eth;
    struct iphdr outer_ip, *ip;
    char pt[128];


    // if(ntohs(eth->h_proto) == ETH_P_ARP){
    //     printf("eth dest: %x:",pkt->eth->h_dest[0]);
    //     printf("%x:%x:",pkt->eth->h_dest[1],pkt->eth->h_dest[2]);
    //     printf("%x:%x:",pkt->eth->h_dest[3],pkt->eth->h_dest[4]);
    //     printf("%x\n",pkt->eth->h_dest[5]);

    //     printf("eth src: %x:",pkt->eth->h_source[0]);
    //     printf("%x:%x:",pkt->eth->h_source[1],pkt->eth->h_source[2]);
    //     printf("%x:%x:",pkt->eth->h_source[3],pkt->eth->h_source[4]);
    //     printf("%x\n\n",pkt->eth->h_source[5]);
    // }


    // bpf_debug(pt);
    
    // if(ntohs(eth->h_proto) == ETH_P_IP) // If IP packet...
    // {
    //     eth->h_proto = 0xAAAA; // Signal it is encapsulated
    //     ip = (struct iphdr *) (((char*) eth) + sizeof(struct ethhdr));
    //     memmove(&outer_ip,ip,sizeof(struct iphdr));

    //     bpf_push_header(pkt,sizeof(struct ethhdr),sizeof(struct iphdr),&outer_ip);
    // }else if (eth->h_proto == 0xAAAA){ // If encapsulated IP packet...
    //     bpf_pop_header(pkt,sizeof(struct ethhdr),sizeof(struct iphdr));
    //     eth->h_proto = 0x0008;
    // }

    // uint32_t *out_port;

    // // if the source is not a broadcast or multicast
    // if ((pkt->eth->h_source[0] & 1) == 0) {
    //     // Update the port associated with the packet
    //     bpf_map_update_elem(&inports, pkt->eth->h_source, &pkt->metadata.in_port, 0);
    // }

    // // Flood if the destination is broadcast or multicast
    // if (pkt->eth->h_dest[0] & 1) {
    //     return FLOOD;
    // }

    // // Lookup the output port
    // if (bpf_map_lookup_elem(&inports, pkt->eth->h_dest, &out_port) == -1) {
    //     // If no entry was found flood
    //     return FLOOD;
    // }

    // return *out_port;
    printf("Pkt length: %d",pkt->metadata->length);
    dump("====== Packet at FWD ======",pkt->eth,pkt->metadata->length);
    return DROP;
}
char _license[] SEC("license") = "GPL";



