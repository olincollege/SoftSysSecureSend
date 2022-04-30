/*  
	server.c/src/file_only

	Server side code
	Receives data from client and saves it to text file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
	// Declare local IP and port
	char *ip = "127.0.0.1";
	int port = 8080;
	int e;

	// Create socket
	int sockfd, new_sock;
  	struct sockaddr_in server_addr, new_addr;
  	socklen_t addr_size;
  	char buffer[1024];

  	// Socket is binded to specific port
  	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  	if(sockfd < 0) {
    	perror("[-]Error in socket");
    	exit(1);
  	}
  	printf("[+]Server socket created successfully.\n");
}