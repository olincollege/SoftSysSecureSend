/*  
	server.c/src/file_only

	Server side code
	Receives data from client and saves it to text file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
 
void receive_file(int sockfd){
	int n;
	FILE *fp;
	char buffer[1024];

	// Create a new file (if not pre-existing)
	fp = fopen("receive.txt", "w");

	// While data is received
	while(1){
		// Receive data through socket
		n = recv(sockfd, buffer, 1024, 0);
		if (n <= 0){
			break;
			return;
		}
		// Save data to file
		fprintf(fp, "%s", buffer);
    	bzero(buffer, 1024);
    }
    return;
}
 
int main(){
	int e;

	int sockfd, new_sock;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	char buffer[1024];

	// Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("Error in Creating Socket");
		exit(1);
	}
	printf("Server Socket Created Successfully!\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8080;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Bind socket to port 8080 and local IP
	e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e == -1){
		perror("Error in Binding Socket");
		exit(1);
	}
	printf("Successfully Binded to Port!\n");

	// When successful, start listening for connections
	if(listen(sockfd, 10) == 0){
		printf("Listening for Client...\n");
	}
	else{
		perror("Error in Client Not Found");
		exit(1);
	}

	// Accept connection from client
	addr_size = sizeof(new_addr);
	new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

	// Call receive_file to receive data from client through socket
	receive_file(new_sock);
	printf("File Received Successfully!\n");
	return 0;
}