/*  
	client.c/src/file_only

	Client side code
	Reads text file and sends it to server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
 
void send_file(FILE *fp, int sockfd){
  char data[1024] = {0};
 
  while(fgets(data, 1024, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("Error in sending file.");
      exit(1);
    }
    bzero(data, 1024);
  }
}
 
int main(){
	int e;
	int sockfd;
	struct sockaddr_in server_addr;

	FILE *fp;
	char *filename = "send.txt";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("Error in Creating Socket");
		exit(1);
	}
	printf("Server Socket Created Successfully!\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8080;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e == -1) {
		perror("Error in Connecting Socket");
		exit(1);
	}
	printf("Connected to Server Successfully!\n");

	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error in Reading File");
		exit(1);
	}

	send_file(fp, sockfd);
	printf("File Successfully Sent!\n");
	close(sockfd);
	return 0;
}
