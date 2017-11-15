#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void transmiteComenzi(char *comenzi, int sockfd){
	int i,j=0;
	char nou[20], msg[20];
	for(i=0;i<strlen(comenzi);i++){
		if(strchr("fslrb", comenzi[i])!=NULL){
			nou[j]=comenzi[i];
			j++;
		}
	}
	for(i=0;i<j;i++){
		sprintf(msg, "%c", nou[i]);
		if( send(sockfd , msg , strlen(msg) , 0) < 0)
        	{
            		puts("Send failed");
            		return 1;
        	}
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
    int sockfd = 0, i, j;
    char recvBuff[1024], message[2];
    struct sockaddr_in serv_addr;

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(20236);

    if(inet_pton(AF_INET, "193.226.12.217", &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

  /*  sprintf(message, "%c", 'f');
   if( send(sockfd , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
	for(i=0; i<10000; i++)
		for(j=0; j<100000; j++);
sprintf(message, "%c", 's');
   if( send(sockfd , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
*/

transmiteComenzi(argv[1], sockfd);
    return 0;
}
