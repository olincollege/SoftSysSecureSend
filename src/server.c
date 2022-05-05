/*  
    server.c

    Server Side receives connections from client
    Client can send messages to the server and server communicates those messages to the other connected clients
    Server also receives files and saves it to the directory for other clients to see (simulated file transfer)
*/

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
#include <errno.h>

#define MAX_CLIENTS 10
#define BUFFER_SZ 2048
#define NAME_LEN 32

static _Atomic unsigned int cli_count = 0;
static int uid = 10;

// Client Struct
typedef struct{
    struct sockaddr_in address;
    int sockfd;
    int uid;
    char name[NAME_LEN];
} client_t;

void receive_file(int sockfd){
    int n;
    FILE *fp;
    char buffer[BUFFER_SZ];

    // Create a new file (if not pre-existing)
    fp = fopen("receive.txt", "w");
    // While data is received
    while(1){
        // Receive data through socket
        n = recv(sockfd, buffer, BUFFER_SZ, 0);
        if (n <= 0){
            break;
            return;
        }
        // Save data to file
        fprintf(fp, "%s", buffer);
        bzero(buffer, BUFFER_SZ);
    }
}

// Create total number of clients
client_t *clients[MAX_CLIENTS];

// Sends messages to the server through clients
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Add `>` character after each message to indicate who is writing the message
void str_overwrite_stdout(){
    printf("\r%s", "> ");
    fflush(stdout);
}

// Format message string
void str_trim_lf(char* arr, int length){
    for(int i=0; i<length; i++){
        if(arr[i] == '\n'){
            arr[i] = '\0';
            break;
        }
    }
}

// Add clients to the queue stack
void queue_add(client_t *cl){
    pthread_mutex_lock(&clients_mutex);

    for(int i=0; i<MAX_CLIENTS; i++){
        if(!clients[i]){
            clients[i] = cl;
            break;
        }
    }
    
    pthread_mutex_unlock(&clients_mutex);
}

// Remove clients from the queue stack
void queue_remove(int uid){
    pthread_mutex_lock(&clients_mutex);

    for(int i=0; i<MAX_CLIENTS; i++){
        if(clients[i]){
            if(clients[i]->uid == uid){
                clients[i] = NULL;
                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// Client who sends message to server
void send_message(char *s, int uid){
    pthread_mutex_lock(&clients_mutex);

    for(int i=0; i<MAX_CLIENTS; i++){
        if(clients[i]){
            if(clients[i] -> uid != uid){
                // Write through socket, if fail return error
                if(write(clients[i]->sockfd, s, strlen(s)) < 0){
                    printf("Error in Sending Message to Clients\n");
                    break;
                }
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

// Handles client in server
void *handle_client(void *arg){
    char buffer[BUFFER_SZ];
    char name[NAME_LEN];
    int leave_flag = 0;
    cli_count++;

    client_t *cli = (client_t*)arg;

    // Get name of client connection and return if connection successful
    if(recv(cli->sockfd, name, NAME_LEN, 0) <= 0 || strlen(name) < 2 || strlen(name) >= NAME_LEN -1){
        printf("Error in Invalid Name Input\n");
        leave_flag = 1;
    } else {
        strcpy(cli->name, name);
        sprintf(buffer, "%s has joined!\n", cli->name);
        printf("%s", buffer);
        send_message(buffer, cli->uid);
    }

    bzero(buffer, BUFFER_SZ);

    // When client is connected to server
    while(1){
        if(leave_flag){
            break;
        }

        // If message from client received
        int receive = recv(cli->sockfd, buffer, BUFFER_SZ, 0);

        // If receive is true, send message to server
        if(receive > 0){
            if(strlen(buffer) > 0){
                send_message(buffer, cli->uid);
                str_trim_lf(buffer, strlen(buffer));
                printf("%s\n", buffer);
            }
        // If receive is false and client has called for exit
        } 
        else if (receive == 0 || strcmp(buffer, "exit") == 0){
            sprintf(buffer, "%s has left\n", cli->name);
            printf("%s", buffer);
            send_message(buffer, cli->uid);
            leave_flag = 1;
        // No connection
        } 
        else{
            printf("Error in Client Not Found\n");
            leave_flag = 1;
        }
        bzero(buffer, BUFFER_SZ);
    }

    close(cli->sockfd);
    queue_remove(cli->uid);
    free(cli);
    cli_count--;
    pthread_detach(pthread_self());

    return NULL;
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    int option = 1;
    int listenfd = 0, connfd = 0;
    socklen_t addr_size;

    // Create sockets for server and client
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    // Socket Settings
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    // Signals
    signal(SIGPIPE, SIG_IGN);

    // Reuse socket if already connected once
    if(setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof(option)) < 0){
        printf("Error in Reusing Socket\n");
        exit(1);
    }

    // Bind to port
    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("Error in Binding to Socket\n");
        exit(1);
    }

    // Listen for clients
    if(listen(listenfd, 10) < 0){
        // Listen for 10 seconds
        printf("Error in Listening to Client\n");
        exit(1);
    }

    printf("=== WELCOME TO SEND-SECURE: A SECURE WAY TO SEND MESSAGES ===\n");

    while(1){
        addr_size = sizeof(cli_addr);
        // Accept client if found
        connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &addr_size);

        // Check if MAX_CLIENTS have been reached
        if((cli_count + 1) == MAX_CLIENTS){
            printf("Error in Maximum clients connected reached");;
            close(connfd);
            continue;
        }

        // Create client in server
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->address = cli_addr;
        cli->sockfd = connfd;
        cli->uid = uid++;

        // Add client to queue
        queue_add(cli);
        pthread_create(&tid, NULL, &handle_client, (void*)cli);

        receive_file(cli->sockfd);
        printf("File Received Successfully!\n");

        // Sleep in thread reduces CPU usage of thread
        sleep(1);
    }
    return 0;
}
