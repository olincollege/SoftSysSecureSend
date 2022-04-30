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

int main(){
	// Declare local IP and port
	char *ip = "127.0.0.1";
	int port = 8080;
	int e;

	// Create socket and connect function is executed
	int sockfd;
	struct sockaddr_in server_addr;
	FILE *fp;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("Error in Socket Creation.");
		exit(1);
	}
	printf("Server Socket Created Successfully.")
}

