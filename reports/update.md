# SoftSysSendSecure

Authors: Conan McGannon, Daniel Park

## Project Update

Our goal of our project is to learn about network programming in C by building a chat application using sockets. As we mentioned in our proposal, our lower bound is building a simple chat application usable by multiple connected clients. However, our stretch goal for this project is an application where multiple clients can not only send messages, but also files such as documents and images as well.

As mentioned in our proposal, our learning goals for this project are to use effective software development tools such as Makefiles and libraries, as well as learning more about network programming's concepts such as servers, clients, sockets, communication protocols, and such. Like our “Lisperers” project, we want to use the project as a learning experience, to focus on learning through the development process rather than focusing on the final product.

On our progress with the chat application, we have successfully reached our stretch goal of ours to make a multi-user chatroom. We wanted to take this update day (4/25/22) to check our progress, and we did not anticipate that we would have a single user chat application ready. However, we managed to make a chatroom that can take up to 10 people (we selected this limitation due to any more causing performance issues) and text each other through the server with each client running its own process. You can view the instructions to test the functionality out yourself in the `README.md`

With the chat room successfully completed, we have already started on researching and working on the file transfering functionality for the project. Since we only have a week left, we decided to scope it so that a client will read the text file and send it over to the server, where the server will read the data from the client and save that data in a seperate text file. This will mimic the way how clients interact with popular chat applications like Messenger and Discord, where the file sent by a client will be viewable by any client connected to the specific group chat. And while the file will be sent automatically when, we also have a stretch goal, if we manage to finish our goal early as we have done with our last sprint, to have the file be sent manually through a client rather than automatically when it connects to the server.

For this process, since we already have the connection between the server and clients, we will jump base off of what we have in terms of BLAB.

Our tasks currently for this last stretch of the phase is:
1. Open the existing file on the client side and read the data (Definition of Done: If the client can read the data from the file and save it): Conan
2. Automatically create a new file when the server opens (Definition of Done: If the server can automatically create a new file when `./server` is run): Daniel
3. Establish connection for the data transmission between client and server (Definition of Done: If server can read the data from the client similarly to how it reads it when implementing the chat room): Conan & Daniel
4. Write the received data into the newly created file (If the data received from the client is pasted onto the newly created file from the server): Daniel

In addition to our technical duties, we will also begin to start the final report due in eight days by writing up a draft together when we have our weekly meeting on Wednesday.

Updated Trello Board: https://trello.com/b/meaJJb8v/softsyssecuresend
