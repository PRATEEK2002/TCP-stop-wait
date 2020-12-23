//2017A7PS0171P
//PRATEEK SHARMA
#ifndef packet
#define packet
typedef struct packet2{
 int sq_no;
char data[PACKET_SIZE];
 int is_ack;
 int is_last;
 int size_pkt;
 int channel;
}DATA_PKT;
#endif