#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SZ 2048
#define NAME_LEN 32

// Global variables
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[NAME_LEN];

void send_file(FILE *fp, int sockfd){
    char data[BUFFER_SZ] = {0};

    // While data is being read
    while(fgets(data, BUFFER_SZ, fp) != NULL){
        // Send file through the socket to the server
        if (send(sockfd, data, sizeof(data), 0) == -1){
            perror("Error in sending file.");
            exit(1);
        }
        bzero(data, BUFFER_SZ);
    }
}

void str_overwrite_stdout() {
    printf("%s", "> ");
    fflush(stdout);
}

void str_trim_lf (char* arr, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

// Receive message from server and print onto client
void recv_msg_handler() {
    char message[BUFFER_SZ] = {};
    while (1) {
        int receive = recv(sockfd, message, BUFFER_SZ, 0);
        if (receive > 0) {
            printf("%s", message);
            str_overwrite_stdout();
        } 
        else if (receive == 0) {
            break;
        }
        bzero(message, BUFFER_SZ);
    }
}

// Send message to server
void send_msg_handler() {
    char buffer[BUFFER_SZ] = {};
    char message[BUFFER_SZ + NAME_LEN] = {};
    
    while(1) {
        str_overwrite_stdout();
        fgets(buffer, BUFFER_SZ, stdin);
        str_trim_lf(buffer, BUFFER_SZ);

        if (strcmp(buffer, "exit") == 0) {
            break;
        } 
        // Prints message from other client
        else {
            // SUPRESSED -Wformat -Overflow Warning
            sprintf(message, "%s: %s\n", name, buffer);
            send(sockfd, message, strlen(message), 0);
        }
        bzero(buffer, BUFFER_SZ);
        bzero(message, BUFFER_SZ + NAME_LEN);
    }
    catch_ctrl_c_and_exit(2);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Local IP and connect to chosen port
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    // Enable Ctr-C to exit
    signal(SIGINT, catch_ctrl_c_and_exit);

    // Accept Client Name
    printf("Please enter your name: ");
    fgets(name, NAME_LEN, stdin);
    str_trim_lf(name, strlen(name));

    // Enforce name rules due to string capacity
    if (strlen(name) > NAME_LEN - 1 || strlen(name) < 2){
        printf("Name must be less than 30 and more than 2 characters.\n");
        return EXIT_FAILURE;
    }

    FILE *fp, *fp2;
    char *filename = "send.txt";

    struct sockaddr_in server_addr;

    // Socket settings (from server.c)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);


    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1) {
        printf("ERROR: connect\n");
        return EXIT_FAILURE;
    }

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Error in Reading File");
        exit(1);
    }

    // Read incoming files
    char a;
    fp2 = fopen("receive.txt","w");
    a = fgetc(fp);
    while ((a = fgetc(fp)) != EOF)
    {
        fputc(a, fp2);
    }

    // Send Client Name to Server
    send(sockfd, name, NAME_LEN, 0);

    // Call send_file to read file and sent to server
    send_file(fp, sockfd);
    printf("File Successfully Sent!\n");

    fclose(fp);
    fclose(fp2);

    printf("=== SUCCESSFULLY ENTERED SEND-SECURE SERVER ===\n");

    // Create thread to send messages
    pthread_t send_msg_thread;
    if(pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0){
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    // Create thread to receive messages
    pthread_t recv_msg_thread;
    if(pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0){
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    // Leave if flag to leave is raised
    while (1){
        if(flag){
            printf("\nSucessfuly Exited Chatroom\n");
            break;
        }
    }

    // Close socket stream
    close(sockfd);

    return EXIT_SUCCESS;
}
