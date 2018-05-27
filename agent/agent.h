#ifndef AGENT_H
#define AGENT_H

typedef void (*tx_packet_fn)(void *buf, int len, uint64_t out_port, int flags);
typedef void (*pop_header_fn)(void *pkt, int offset, int encap_len);
typedef void (*push_header_fn)(void *pkt, int offset, int encap_len, void* data);

struct agent_options {
    uint64_t dpid;
    char* controller;
};

int agent_start(ubpf_jit_fn *ubpf_fn, tx_packet_fn tx_fn, pop_header_fn pop_fn, push_header_fn push_fn, struct agent_options *opts);
int agent_packetin(void *pkt, int len);
int agent_stop(void);

#endif
