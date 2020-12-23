#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//2017A7PS0171P
//PRATEEK SHARMA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#define PACKET_SIZE 100
#define SIZE 300
#define PDR 10
#define BUFF_SIZE 30
	//#pragma warning disable CS1998
#include"packet.h"


void die(char *s)
{
 perror(s);
 exit(1);
}
int ptr=0,wrt=1;
DATA_PKT serv_buff[BUFF_SIZE];
//DATA_PKT dummy;
//dummy.sq_no=-1;


//for(int i=0;i<BUFF_SIZE;i++){
//serv_buff[i].sq_no= -1;}
 //memset(&serv_buff, '0', sizeof(serv_buff));
void fillbuffer(DATA_PKT pkt,FILE *fp)
{
	//printf("\n\nghghghg  %d\n\n",pkt.sq_no);
	for(int i=1;i<BUFF_SIZE;i++){
		if(serv_buff[i].sq_no==-1)
		{
			serv_buff[i]=pkt;
			break;
		}
	}
	//ptr++;
	int i;
	for(i=0;i<BUFF_SIZE;i++)
	{
		if(serv_buff[i].sq_no==wrt)
		{
			//printf("\nhola %d\n",serv_buff[i].sq_no);
			 fwrite(serv_buff[i].data, sizeof(char),sizeof(serv_buff[i].data),fp);
serv_buff[i].sq_no=-1;
			i=0;
			wrt=wrt+1;
			//break;
		}
	}
	
}


int main(void)
{
	//#pragma warning disable CS1998

	//#pragma diag_suppress 177
for(int i=0;i<BUFF_SIZE;i++){
serv_buff[i].sq_no= -1;}
 int listenfd = 0;
 int connfd = 0;
 struct sockaddr_in serv_addr;
 char sendBuff[1025];
 int numrv;
 listenfd = socket(AF_INET, SOCK_STREAM, 0);
printf("Socket retrieve success\n");
 memset(&serv_addr, '0', sizeof(serv_addr));
 memset(sendBuff, '0', sizeof(sendBuff));
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 serv_addr.sin_port = htons(5001);
 bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
 if(listen(listenfd, 10) == -1)
 {
 printf("Failed to listen\n");
 return -1;
 }
//while(1)
 //{
 unsigned char offset_buffer[10] = {'\0'};
 unsigned char command_buffer[2] = {'\0'};
 int offset;
 int command;
 int connfd0 = accept(listenfd, (struct sockaddr*)NULL ,NULL);
int  connfd1 = accept(listenfd, (struct sockaddr*)NULL ,NULL);



int received_int = 0;
//int return_status =recvfrom(connfd1, &received_int, sizeof(received_int), 0, (struct sockaddr_in *)&serv_addr, sizeof(serv_addr));
int return_status = read(connfd1, &received_int, sizeof(received_int));
//if (return_status > 0) {
   //fprintf(stdout, "Received int = %d\n", ntohl(received_int));
//}
int cutoff=ntohl(received_int);
//printf("llreceived_int%d\n",cc);

 //printf("Waiting for client to send the command (Full File (0)Partial File (1)\n");

 offset = 0;
 


 /* Open the file that we wish to transfer */
//FILE *fp = fopen("source_file.txt","rb");
  FILE *fp = fopen("output.txt", "ab");

 if(fp==NULL)
 {
 printf("File opern error");
 return 1;
 }
 
 
int recv_len;
 char recvBuff[PACKET_SIZE];

 
 /* Read data from file and send it */
// fseek(fp, offset, SEEK_SET);
 
	 //rcv_pkt.sq_no=countt;
	 //rcv_pkt.is_ack=0;

 //memset(rcv_pkt.data, '0', sizeof(rcv_pkt.data));
//while(1) {
	 fd_set fr,fw,fe;
	int bp=0; 
	//cutoff=cutoff+1;
	
while(1){	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//if(bp==cutoff){
//break;}
//printf("\nhidkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
//for(int i=0;i<3;i++){
	
FD_ZERO(&fr);
	FD_ZERO(&fw);
	FD_ZERO(&fe);


	FD_SET(connfd0,&fr);
	FD_SET(connfd1,&fr);
	//FD_SET(sock2,&fr);

	//FD_SET(sock2,&fw);
	//FD_SET(sock0,&fw);
	//FD_SET(sock1,&fw);
	int n=connfd1+1;
	int num=select(n,&fr,&fw,&fe,NULL);
//printf ("%d\n",num);
int popflag=0;
if(FD_ISSET(connfd1,&fr))//////////////////////////////////////////////////////////////////////////////////////////
	 {
		  	 DATA_PKT rcv_pkt1;

		// printf ("nn2");
connfd=connfd1;
		   memset(recvBuff, '0', sizeof(recvBuff));

	 recv_len = read(connfd, &rcv_pkt1, sizeof(rcv_pkt1));
	 
printf("RCVD PKT: Seq. No %d of size %d Bytes from channel %d\n ",rcv_pkt1.sq_no,rcv_pkt1.size_pkt,rcv_pkt1.channel);
//printf("\nBytes received %d\n\n",rcv_pkt1.sq_no);
 int lower=1,upper=100;
  int rn = (rand() % (upper - lower + 1)) + lower; 
   // printf("dfdfdfdfdfdfddddddddddddddddddddddddddd11 %d\n",rn);

 if(rn>PDR || rcv_pkt1.sq_no==1 ){
 
		

		 
		 
		 
 
 // recvBuff[n] = 0;
  memset(recvBuff, '0', sizeof(recvBuff));

//for(int i=0;i<PACKET_SIZE;i++)
	//recvBuff[i]=rcv_pkt1.data[i];
 // printf("11%s",rcv_pkt1.data);
 //fwrite(rcv_pkt1.data, 1,recv_len,fp);
// fwrite(rcv_pkt1.data, sizeof(char),sizeof(rcv_pkt1.data),fp);
fillbuffer(rcv_pkt1,fp);
 // printf("%s \n", recvBuff);
  DATA_PKT ack_pkt1;
    ack_pkt1.sq_no=rcv_pkt1.sq_no;
	 ack_pkt1.is_ack=1;
	 ack_pkt1.channel=rcv_pkt1.channel;
memset(ack_pkt1.data, '0', sizeof(ack_pkt1.data));
//if( ack_pkt1.sq_no==1){
	//printf("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");

if (write(connfd, &ack_pkt1, sizeof(ack_pkt1))==-1)
 {
 die("sendto()");
 }
  printf("SENT ACK: for PKT with Seq. No. %d rom channel %d\n",ack_pkt1.sq_no,ack_pkt1.channel);

//}	 
 
	 
 /**
 else{
	if (sendto(connfd, &ack_pkt1, sizeof(ack_pkt1), 0 , (struct sockaddr_in *)&serv_addr, sizeof(serv_addr))==-1)
 {
 die("sendto()");
 }
}**/

 	// DATA_PKT rcv_pkt1;

 
 if(recv_len < 0)
 {
 printf("\n Read Error \n");
 }
 		 		   bp++;
//printf("\n\nbp%d\n\n",bp);

  if(bp==cutoff){
		   memset(recvBuff, '0', sizeof(recvBuff));
//printf("\n\nbp%d\n\n",bp);

		 break;}

	 }

	 }
FD_ZERO(&fr);
	FD_ZERO(&fw);
	FD_ZERO(&fe);


	FD_SET(connfd0,&fr);
	FD_SET(connfd1,&fr);
	//FD_SET(sock2,&fr);

	//FD_SET(sock2,&fw);
	//FD_SET(sock0,&fw);
	//FD_SET(sock1,&fw);
	 n=connfd1+1;
	num=select(n,&fr,&fw,&fe,NULL);
	 

if(FD_ISSET(connfd0,&fr))/////////////////////////////////////////////////////////////////////////////////////////
	 {
		
		 	 DATA_PKT rcv_pkt;

		// printf ("nn1");
		 connfd=connfd0;
				   memset(recvBuff, '0', sizeof(recvBuff));

	 recv_len = read(connfd, &rcv_pkt, sizeof(rcv_pkt));
	 printf("RCVD PKT: Seq. No %d of size %d Bytes from channel %d\n ",rcv_pkt.sq_no,rcv_pkt.size_pkt,rcv_pkt.channel);

 //printf("\n\nBytes received %d\n\n",rcv_pkt.sq_no);
 int lower=1,upper=100;
  int rn = (rand() % 
           (upper - lower + 1)) + lower;
 // printf("dfdfdfdfdfdfddddddddddddddddddddddddddd %d\n",rn);
		   
  if(rn>PDR || rcv_pkt.sq_no==2 ){

		/** if(bp>cutoff){
			 printf("\n\nbp%d\n\n",bp);

		   memset(recvBuff, '0', sizeof(recvBuff));

		 break;}
		   	  bp++;**/

 // recvBuff[n] = 0;
  memset(recvBuff, '0', sizeof(recvBuff));
 // printf("22%s",rcv_pkt.data);

// for(int i=0;i<PACKET_SIZE;i++)
	/// recvBuff[i]=rcv_pkt.data[i];
  //printf("%s",recvBuff);
 //fwrite(rcv_pkt.data, 1,recv_len,fp);
 fillbuffer(rcv_pkt,fp);
 // printf("%s \n", recvBuff);
  DATA_PKT ack_pkt;
    ack_pkt.sq_no=rcv_pkt.sq_no;
	 ack_pkt.is_ack=1;
	 	 ack_pkt.channel=rcv_pkt.channel;

memset(ack_pkt.data, '0', sizeof(ack_pkt.data));
//if( ack_pkt.sq_no==2){
if (write(connfd, &ack_pkt, sizeof(ack_pkt))==-1)
 {
 die("sendto()");
 }
 printf("SENT ACK: for PKT with Seq. No. %d rom channel %d\n",ack_pkt.sq_no,ack_pkt.channel);
//}


 
 

 
 if(recv_len < 0)
 {
 printf("\n Read Error \n");
 }
// printf("\n\nbp%d\n\n",bp);

	 		   bp++;

  if(bp==cutoff){
		   memset(recvBuff, '0', sizeof(recvBuff));
//printf("\n\nbp%d\n\n",bp);

		 break;}
	 }
	

}
}
//}
 
//}
	//#pragma warning disable CS1998

printf("END");
 return 0;
}
