/*  
	server.c/src/file_only

	Server side code
	Receives data from client and saves it to text file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
 
void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "receive.txt";
  char buffer[1024];
 
  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, 1024, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, 1024);
  }
  return;
}
 
int main(){
	char *ip = "127.0.0.1";
	int port = 8080;
	int e;

	int sockfd, new_sock;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	char buffer[1024];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("Error in Creating Socket");
		exit(1);
	}
	printf("Server Socket Created Successfully!\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e == -1) {
		perror("Error in Binding Socket");
		exit(1);
	}
	printf("Successfully Binded to Port!\n");

	if(listen(sockfd, 10) == 0){
		printf("Listening for Client...\n");
	}
	else{
		perror("Error in Client Not Found");
		exit(1);
	}

	addr_size = sizeof(new_addr);
	new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

	write_file(new_sock);
	printf("File Received Successfully!\n");
	return 0;
}