# SoftSysSecureSend

A secure, multi-user file-transfer chatroom in C developed by [Conan McGannon](https://github.com/hyrtzhyro) and [Daniel Park](https://github.com/DanPark13).

## Project Preview

Our goal of our project is to learn about network programming in C by building a chat application using sockets. As we mentioned in our proposal, our lower bound is building a simple chat application usable by multiple connected clients. However, our stretch goal for this project is an application where multiple clients can not only send messages, but also files such as documents and images as well.

As mentioned in our proposal and update, the main purpose of this project is to learn more about network programming concepts such as servers, clients, sockets, communication protocols. We want to build this application to use eff effective software development tools such as Makefiles and libraries for collaboration to make this project more of a fruit of our learning experience rather than focusing on the final product.

## Resources & Research

For research on our topic, we consulted networking programming documentation. We wanted to learn more about networks due to our lack of knowledge in the area, so we used resources such as the ones listed below to learn more about the different terminology such as sockets, IPs, clients, servers, etc.
- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/), 
- [Carleton University COMP1406 Course's Chapter 12 on Network Programming](https://people.scs.carleton.ca/~lanthier/teaching/COMP1406/Notes/COMP1406_Ch12_NetworkProgramming.pdf),
- [Internal Pointers' "Network programming for beginners: introduction to sockets" Article](https://internalpointers.com/post/network-programming-beginners-overview),
- [GeeksforGeeks' "Socket Programming in C/C++" Article](https://www.geeksforgeeks.org/socket-programming-cc/#:~:text=What%20is%20socket%20programming%3F,reaches%20out%20to%20the%20server)

To get into more specific on chat applications, we used
- Head First C Chapter 11
- [Idiot Developer's Video Series on Socket Programming](https://www.youtube.com/watch?v=hptViBE23fI&list=PLHYn9gDxQOpizt0_tvN7nJHP_70il0YJm&ab_channel=IdiotDeveloper)

You can view the full list of resources we used and referenced in the [resources file.](https://github.com/olincollege/SoftSysSecureSend/blob/main/reports/resources.md)

## Code Implementation

For the implementation, unlike our last project where we were closer to the lower echelon of our deliverables, we were able to reach the upper echelon, although not the top, of our deliverables. And throughout our project, we pivoted our scope of the project. Originally, we wanted this project to be primarily about file transferring, but we decided that it would make more sense to have a TCP multi-client-server chat room to simulatt a real group chat. So for our submission, we implemented a chatroom that multiple clients can connect to and send messages in. Clients are able to name themselves, which will appear on the server terminal. When a client sends a message, their message will show up on the server as well as the other clients that are connected to it. We went above and beyond for the messaging server/client, something we are extremely proud of.

However, we also wanted to have some sort of file transferring capabilities as well since that was our original goal for our project. Given our time, instead of our clients being able to send images as well, we scaled down the file transferring to only text files through the socket.

### Client-Server Architecture

To get a general structure of our program, our code is seperated by `server.c` which is a remote computer that provides messaging services and `client.c` which is the one that requests these services from the server. This system is called a client-server architecture, a model in network programming where the client sends a request to the server through a network and the server accepts the request and sends the required data to the client.

We can begin implementing the architecture within our `server.c`, where we create server and client sockets that allows communication by sending and receiving data over the network.

```C
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
```

The process of a server implementation can be easily explained through the **BLAB** steps acronym.

`B`: *Bind* the TCP socket to the IP and port. (Make sure to also catch errors!)

```C
    // Bind to port
    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("Error in Binding to Socket\n");
        exit(1);
    }
```

`L`: *Listen* and wait for clients

```C
    // Listen for clients
    if(listen(listenfd, 10) < 0){
        // Listen for 10 seconds
        printf("Error in Listening to Client\n");
        exit(1);
    }
```

`A`: When a client connects to the same IP and port as the server, *accept* the client and server connection is established

```C
	connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &addr_size);
```

`B`: Server and Client can *begin* talking with each other.

And since we are handling a multi-user chatroom, we want to create multiple clients. To do so, we can create a queue of additional clients to the server to dynamically add clients to the chat-based room. This is also where we are able to receive the file from the socket

```C
	// Create client in server
    client_t *cli = (client_t *)malloc(sizeof(client_t));
    cli->address = cli_addr;
    cli->sockfd = connfd;
    cli->uid = uid++;

	// Add client to queue
    queue_add(cli);
    pthread_create(&tid, NULL, &handle_client, (void*)cli);

    // Receive file from the client socket
    receive_file(cli->sockfd);
``` 

We decided to cap the limit of allowed clients onto the server because past about 11 or 12, the server starts not being able to send messages to other clients from other clients messages. It is a small bug that we decided not to fix, and decided to cap it at 10 members which is still a lot of people.

If you want the full implementation, check out [server.c](https://github.com/olincollege/SoftSysSecureSend/blob/main/src/server.c)

Then on the client side on file `client.c`, we can break down the process of establishing a client to connect to the server in two simple steps: `connect` and `send`.

But before we do that, similarly to the server, we create a socket to connect to the server. We also establish the name of the client which is inputted by the user.

```C
	// Local IP and connect to chosen port
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    // Enable Ctr-C to exit
    signal(SIGINT, catch_ctrl_c_and_exit);

    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
```

Next, we can connect our client to the server and send our information and file to the server when we connect to it.

```C
	int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1) {
        printf("Error in Creating Socket\n");
        exit(1);
    }
    printf("Connected to Server Successfully!\n");

    // Send Client Name to Server
    send(sockfd, name, NAME_LEN, 0);

    // Send file to Server
    send_file(fp, sockfd);
```

We also have to create a thread to be able to send messages because many clients connected to the server will be sending over and receiving messages at the same time.

```C
    // Create thread to send messages
    pthread_t send_msg_thread;
    if(pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0){
        printf("Error in Creating Pthread\n");
        exit(1);
    }

    // Create thread to receive messages
    pthread_t recv_msg_thread;
    if(pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0){
        printf("Error in Creating Pthread\n");
        exit(1);
    }
```

If you want the full implementation, check out [client.c](https://github.com/olincollege/SoftSysSecureSend/blob/main/src/server.c)

### File Transfer Implementation



## Project in Action

And with that, clients automatically send files when they connect to the client onto the server to simulate other clients being able to see the files sent as well. They can also send text messages to each other through the server to simulate a real group chat.

**Opening the server that will host all the clients onto port 8080**

![ServerOpen](https://i.imgur.com/iiRa7Eml.png)

**Connecting a single client to the server and automatically "sends" the file to the server**

![SingleClient](https://i.imgur.com/g7FCmpIh.png)

![ClientSendMessage](https://i.imgur.com/oeVxyhUh.png)

**Client can also send message and displayed on the server**

![ClientMessage](https://i.imgur.com/UIwdlIHh.png)

**Multiple clients can connect to the server, send its own file, and send messages displayed on the server and other clients**

![Multiple](https://i.imgur.com/5OgBxN1h.png)

## Conclusion

Compared to last project, we are very happy how this project turned out. Although there are some bugs we would have liked to patch out, whether it's the server not being able to take more than about a dozen clients or occasionally failing to read the file the client sent over, we are proud that we were able to (almost) reach the upper echelon of what we wanted to create at the beginning stages of this project. And overall, we are most proud that we were able to apply our skills from class, especially the material more recently, into an expanded project that cement our understanding of the topic.

For future implemenations, outside of debugging would defintely go into fleshing out the file transfer to include images and videos but more excitingly, a GUI. Right now, the project is run on terminal, but we think being able to have a chat application built simiarly to Telegram or Messenger would be fun to work on as well as a great opportunity to make a systems application which would be great experience to have.

We were able to apply our skills from class, especially the material more recently, into an expanded project.
