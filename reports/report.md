# SoftSysSecureSend

A secure, multi-user file-transfer chatroom in C developed by [Conan McGannon](https://github.com/hyrtzhyro) and [Daniel Park](https://github.com/DanPark13).

Our goal of our project is to learn about network programming in C by building a chat application using sockets. As we mentioned in our proposal, our lower bound is building a simple chat application usable by multiple connected clients. However, our stretch goal for this project is an application where multiple clients can not only send messages, but also files such as documents and images as well.

As mentioned in our proposal and update, the main purpose of this project is to learn more about network programming concepts such as servers, clients, sockets, communication protocols. We want to build this application to use eff effective software development tools such as Makefiles and libraries for collaboration to make this project more of a fruit of our learning experience rather than focusing on the final product.

For research on our topic, we consulted networking programming documentation. We wanted to learn more about networks due to our lack of knowledge in the area, so we used resources such as the ones listed below to learn more about the different terminology such as sockets, IPs, clients, servers, etc.
- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/), 
- [Carleton University COMP1406 Course's Chapter 12 on Network Programming](https://people.scs.carleton.ca/~lanthier/teaching/COMP1406/Notes/COMP1406_Ch12_NetworkProgramming.pdf),
- [Internal Pointers' "Network programming for beginners: introduction to sockets" Article](https://internalpointers.com/post/network-programming-beginners-overview),
- and [GeeksforGeeks' "Socket Programming in C/C++" Article](https://www.geeksforgeeks.org/socket-programming-cc/#:~:text=What%20is%20socket%20programming%3F,reaches%20out%20to%20the%20server)

To get into more specific on chat applications, we used
- Head First C Chapter 11
- [Idiot Developer's Video Series on Socket Programming](https://www.youtube.com/watch?v=hptViBE23fI&list=PLHYn9gDxQOpizt0_tvN7nJHP_70il0YJm&ab_channel=IdiotDeveloper)

You can view the full list of resources we used and referenced in the [resources.md](https://github.com/olincollege/SoftSysSecureSend/blob/main/reports/resources.md) file.

4) What were you able to get done?  Include in the report whatever evidence is appropriate to demonstrate the outcome of the project.  Consider including snippets of code with explanation; do not paste in large chunks of unexplained code.  Consider including links to relevant files.  And do include output from the program(s) you wrote.

5) Explain at least one design decision you made.  Were there several ways to do something?  Which did you choose and why?

6) You will probably want to present a few code snippets that present the most important parts of your implementation.  You should not paste in large chunks of code or put them in the Appendix.  You can provide a link to a code file, but the report should stand alone; I should not have to read your code files to understand what you did.

For the implementation, unlike our last project where we were closer to the lower echelon of our deliverables, we were able to reach the upper echelon, although not the top, of our deliverables. And throughout our project, we pivoted our scope of the project. Originally, we wanted this project to be primarily about file transferring, but we decided that it would make more sense to have a multi-client chat room to simulatt a real group chat. So for our submission, we implemented a chatroom that multiple clients can connect to and send messages in. Clients are able to name themselves, which will appear on the server terminal. When a client sends a message, their message will show up on the server as well as the other clients that are connected to it. We went above and beyond for the messaging server/client, something we are extremely proud of.

`Show images of implementation`

However, we also wanted to have some sort of file transferring capabilities as well since that was our original goal for our project. Given our time, instead of our clients being able to send images as well, we scaled down the file transferring to only text files through the socket.

`Show images of implementation`

And with that, clients automatically send files when they connect to the client onto the server to simulate other clients being able to see the files sent as well. They can also send text messages to each other through the server to simulate a real group chat.

`Show images of working`

Compared to last project, we are very happy how this project turned out. Although there are some bugs we would have liked to patch out, whether it's the server not being able to take more than about a dozen clients or occasionally failing to read the file the client sent over, we are proud that we were able to (almost) reach the upper echelon of what we wanted to create at the beginning stages of this project. And overall, we are most proud that we were able to apply our skills from class, especially the material more recently, into an expanded project that cement our understanding of the topic.

For future implemenations, outside of debugging would defintely go into fleshing out the file transfer to include images and videos but more excitingly, a GUI. Right now, the project is run on terminal, but we think being able to have a chat application built simiarly to Telegram or Messenger would be fun to work on as well as a great opportunity to make a systems application which would be great experience to have.

We were able to apply our skills from class, especially the material more recently, into an expanded project.
