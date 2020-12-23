#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
//2017A7PS0171P
//PRATEEK SHARMA
#include <arpa/inet.h>
#define PACKET_SIZE 100
#define SIZE 300
#include <time.h> 
#define timeto_resend 0.02
#include"packet.h"
void die(char *s)
{
 perror(s);
 exit(1);
}

int main(void)
{
  int sockfd = 0;
 int bytesReceived = 0;
 char recvBuff[PACKET_SIZE];
 unsigned char buff_offset[10]; // buffer to send the File offset value
// unsigned char buff_command[2]; // buffer to send the Complete File (0)or Partial File Command (1).
 int offset; // required to get the user input foroffset in case of partial file command
 //int command; // required to get the user input for command
 memset(recvBuff, '0', sizeof(recvBuff));
 struct sockaddr_in serv_addr;
 /* Create a socket first */
 
 /* Initialize sockaddr_in data structure */
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_port = htons(5001); // port
 serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 /* Attempt a connection */
 int sockfd0;
 if((sockfd0 = socket(AF_INET, SOCK_STREAM, 0))< 0)
 {
 printf("\n Error : Could not create socket \n");
 return 1;
 }
 if(connect(sockfd0, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
 {
 printf("\n Error : Connect Failed \n");
 return 1;
 }

 int sockfd1;
 if((sockfd1 = socket(AF_INET, SOCK_STREAM, 0))< 0)
 {
 printf("\n Error : Could not create socket \n");
 return 1;
 }
 if(connect(sockfd1, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
 {
 printf("\n Error : Connect Failed \n");
 return 1;
 }
 /* Create file where data will be stored */
 //FILE *fp;
 //fp = fopen("destination_file.txt", "ab");
 int size;
 //FILE *f = fopen("source_file.txt" ,"rb");
  FILE *f = fopen("input.txt" ,"rb");

    if (f == NULL) return -1;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fclose(f);
 size=size/PACKET_SIZE;
 if(size%PACKET_SIZE!=0)
	 size=size+1;
 
int converted_number = htonl(size);

 //Write the number to the opened socket
write(sockfd1, &converted_number, sizeof(converted_number));
// sendto(sockfd1, &converted_number, sizeof(converted_number));
//sendto(sockfd1, &converted_number, sizeof(converted_number), 0 , (struct sockaddr_in *) &serv_addr, sizeof(serv_addr));
 
 // printf("\nsize %d\n",size);

 //FILE *fp = fopen("source_file.txt","rb");
 FILE *fp = fopen("input.txt","rb");

 if(NULL == fp)
 {
 printf("Error opening file");
 return 1;
 }

 // Else { command = 0 then no need to send the value of offset }


 /* Receive data in chunks of 256 bytes */
 int countt=0;
 int nread;
  //packet2
 DATA_PKT send_pkt1;
   countt++;

	 send_pkt1.sq_no=countt;
	 send_pkt1.is_ack=0;

 memset(send_pkt1.data, '0', sizeof(send_pkt1.data));

 /* First read file in chunks of 256 bytes */
 //unsigned char buff[PACKET_SIZE]={0};
  nread = fread(send_pkt1.data,1,PACKET_SIZE,fp);
  send_pkt1.size_pkt=nread;
    send_pkt1.channel=1;

 // printf("\n11%s\n",send_pkt1.data);
 //printf("Bytes read %d \n", nread);
 /* If read was success, send data. */
 if(nread > 0)
 {
 //printf("Sending \n");
 //write(sockfd, buff, nread);
 //if (sendto(sockfd1, &send_pkt1, sizeof(send_pkt1), 0 , (struct sockaddr_in *) &serv_addr, sizeof(serv_addr))==-1)
 write(sockfd1, &send_pkt1, sizeof(send_pkt1));
printf("SENT PKT: Seq. No %d of size %d Bytes from channel %d\n",send_pkt1.sq_no,send_pkt1.size_pkt,send_pkt1.channel);
 

 }
 
 //packet1
 
  countt++;

	 DATA_PKT send_pkt2;
	 send_pkt2.sq_no=countt;
	 send_pkt2.is_ack=0;

 memset(send_pkt2.data, '0', sizeof(send_pkt2.data));

 /* First read file in chunks of 256 bytes */
 //unsigned char buff[PACKET_SIZE]={0};
  nread = fread(send_pkt2.data,1,PACKET_SIZE,fp);
    //printf("\n22%s\n",send_pkt2.data);
send_pkt2.size_pkt=nread;
    send_pkt2.channel=2;

// printf("Bytes read %d \n", nread);
 /* If read was success, send data. */
 if(nread > 0)
 {
 //printf("Sending \n");
 //write(sockfd, buff, nread);
write(sockfd0, &send_pkt2, sizeof(send_pkt2));
printf("SENT PKT: Seq. No %d of size %d Bytes from channel %d\n",send_pkt2.sq_no,send_pkt2.size_pkt,send_pkt2.channel);

 
 }
 DATA_PKT send_pkt,rsend_pkt;
int cc=0;
 clock_t before2,before1;
 
 while(1)
 {
	 if(cc==size)
		 break;
	  
 fd_set fr,fw,fe;
FD_ZERO(&fr);
FD_ZERO(&fw);
FD_ZERO(&fe);


FD_SET(sockfd0,&fr);
FD_SET(sockfd1,&fr);
//FD_SET(sock2,&fr);

//FD_SET(sock2,&fw);
//FD_SET(sock0,&fw);
//FD_SET(sock1,&fw);
int n=sockfd1+1;
int num=select(n,&fr,&fw,&fe,NULL);
int sockfd;
int recv_len,nread;
int popflag=0;
clock_t before = clock();

if(FD_ISSET(sockfd1,&fr))
	 {
		 popflag=1;
		// printf("ddddddddddddddddddddddddddd");
		 sockfd=sockfd1;
		 //		 printf ("nn2");
				  DATA_PKT ack_pkt;
 
 recv_len = read(sockfd, &ack_pkt, sizeof(ack_pkt));
  printf("RCVD ACK: for PKT with Seq. No. %d from channel %d\n",ack_pkt.sq_no,ack_pkt.channel);

 //printf("\n\nack %d\n\n",ack_pkt.sq_no);
	cc++;
	 if(cc==size)
		 break;	 

	 countt++;

	 //DATA_PKT send_pkt;
	 send_pkt.sq_no=countt;
	 send_pkt.is_ack=0;

 memset(send_pkt.data, '0', sizeof(send_pkt.data));

 /* First read file in chunks of 256 bytes */
 //unsigned char buff[PACKET_SIZE]={0};
  nread = fread(send_pkt.data,1,PACKET_SIZE,fp);
  send_pkt.size_pkt=nread;
	    send_pkt.channel=1;

// printf("Bytes read %d \n", nread);
 /* If read was success, send data. */
 if(nread > 0)
 {
 //printf("Sending \n");
 //write(sockfd, buff, nread);
 if (write(sockfd, &send_pkt, sizeof(send_pkt))==-1)
 {
 die("sendto()");
 }
 printf("SENT PKT: Seq. No %d of size %d Bytes from channel %d\n",send_pkt.sq_no,send_pkt.size_pkt,send_pkt.channel);

clock_t before1 = clock();

}
 /*
 * There is something tricky going on with read ..
 * Either there was error, or we reached end of file.
 */
 if (nread < PACKET_SIZE)
 {
 if (feof(fp))
 //printf("End of file\n");
 if (ferror(fp))
 printf("Error reading\n");
 //break;
 }

}


else{
int	sec=0;
printf("\nTime taken  seconds  milliseconds (iterations)\n");	
//send_pkt.sq_no=100;
 clock_t difference = clock() - before1;
  sec = difference / CLOCKS_PER_SEC;
  
  //if( sec > timeto_resend ){
if (write(sockfd1, &send_pkt, sizeof(send_pkt))==-1){
 
 die("sendto()");
}
 printf("SENT PKT: Seq. No %d of size %d Bytes from channel %d\n",send_pkt.sq_no,send_pkt.size_pkt,send_pkt.channel);

//}
//printf("\nTime taken  seconds  milliseconds (iterations)sssssssssssssssssssssssssssssssssssssssssssssssssssss\n");}	
}

	 
FD_ZERO(&fr);
FD_ZERO(&fw);
FD_ZERO(&fe);


FD_SET(sockfd0,&fr);
FD_SET(sockfd1,&fr);
//FD_SET(sock2,&fr);

//FD_SET(sock2,&fw);
//FD_SET(sock0,&fw);
//FD_SET(sock1,&fw);
 n=sockfd1+1;
 num=select(n,&fr,&fw,&fe,NULL);
	 
  if(FD_ISSET(sockfd0,&fr))////////////////////////////////////////////////////////////////////
	 {
		/** if(popflag==1)
		 {
			 FD_ZERO(&fr);
FD_ZERO(&fw);
FD_ZERO(&fe);


FD_SET(sockfd0,&fr);
FD_SET(sockfd1,&fr);
		 }**/
		 		// printf("ppppppppppppppppppppppp");

		 sockfd=sockfd0;
		 		// printf ("nn1");
				  DATA_PKT ack_pkt;
 
 recv_len = read(sockfd, &ack_pkt, sizeof(ack_pkt));
 printf("RCVD ACK: for PKT with Seq. No. %d from channel %d\n",ack_pkt.sq_no,ack_pkt.channel);
// printf("\n\nack %d\n\n",ack_pkt.sq_no);
	 cc++;
	if(cc==size)
		 break;

	 countt++;

	// DATA_PKT send_pkt;
	 rsend_pkt.sq_no=countt;
	 rsend_pkt.is_ack=0;
    rsend_pkt.channel=2;

 memset(rsend_pkt.data, '0', sizeof(rsend_pkt.data));

 /* First read file in chunks of 256 bytes */
 //unsigned char buff[PACKET_SIZE]={0};
 nread = fread(rsend_pkt.data,1,PACKET_SIZE,fp);
  rsend_pkt.size_pkt=nread;

// printf("Bytes read %d \n", nread);
 /* If read was success, send data. */
 if(nread > 0)
 {
 //printf("Sending \n");
 //write(sockfd, buff, nread);
 if (write(sockfd, &rsend_pkt, sizeof(rsend_pkt))==-1)
 {
 die("sendto()");
 }
  printf("SENT PKT: Seq. No %d of size %d Bytes from channel %d\n",rsend_pkt.sq_no,rsend_pkt.size_pkt,rsend_pkt.channel);


 clock_t before2 = clock();


}
 /*
 * There is something tricky going on with read ..
 
 
 * Either there was error, or we reached end of file.
 */
 if (nread < PACKET_SIZE)
 {
 if (feof(fp))
// printf("End of file\n");
 if (ferror(fp))
 printf("Error reading\n");
// break;
 }


	 }
	 
	else{
int	sec=0;
//printf("\nTime taken  seconds  milliseconds (iterations)\n");	
//send_pkt.sq_no=100;
 /**if (sendto(sockfd0, &rsend_pkt, sizeof(rsend_pkt), 0 , (struct
sockaddr_in *) &serv_addr, sizeof(serv_addr))==-1)
 {
 die("sendto()");
 }**/


clock_t difference = clock() - before2;
  sec = difference / CLOCKS_PER_SEC;
  
 // if( sec > timeto_resend ){
if (write(sockfd0, &rsend_pkt, sizeof(rsend_pkt))==-1)
 {
 die("sendto()");
 }
   printf("SENT PKT: Seq. No %d of size %d Bytes from channel %d\n",rsend_pkt.sq_no,rsend_pkt.size_pkt,rsend_pkt.channel);

//printf("\nTime taken  seconds  milliseconds (iterations)sssssssssssssssssssssssssssssssssssssssssssssssssssss\n");
//}	
}

 
 }
 
 close(sockfd);
 sleep(1);

 return 0;
}
