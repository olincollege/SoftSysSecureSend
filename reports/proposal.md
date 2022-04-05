# SoftSysSendSecure

Authors: Conan McGannon, Daniel Park

From the last project, we needed to manage our time better, especially at the beginning of the project, to scope our project to reach our stretch goals. In the beginning, we didn’t make much progress on our project and when it hit crunch time, we realized we couldn’t meet our stretch goals and had to scope to a lower bound. For this project, we will start progress early and get as much done as possible so we can come together and see if we can hit our stretch goal or even go further.

So looking forward for this project, we want to learn more about network programming in C by building a chat application using sockets. As a lower bound, we want to be able to build a simple chat application from multiple connected clients but we want to reach our stretch goal for this project of an application where multiple clients can not only send messages, but files such as documents and images as well to establish a “secure” connection through the local environment.

Our learning goals for this project are to not only get used to working within C and using proper software development tools such as Makefiles and libraries but to dip our toes in the field of network programming and their related terminologies such as servers, clients, sockets, protocols, and such. Similar to our past project “Lisperers”, we want to use this project as a learning experience to focus more on learning through the process of developing this project rather than having our final product be the fruit of our endeavors. 

Our required resources can be separated into two categories: network programming documentation and chat application tutorials. 
Before heading into our project, we want to learn more about networks due to our lack of knowledge in the area. We will use resources such as http://beej.us/guide/bgnet/, https://people.scs.carleton.ca/~lanthier/teaching/COMP1406/Notes/COMP1406_Ch12_NetworkProgramming.pdf, https://internalpointers.com/post/network-programming-beginners-overview, and https://www.geeksforgeeks.org/socket-programming-cc/#:~:text=What%20is%20socket%20programming%3F,reaches%20out%20to%20the%20server to learn about the different terminology such as sockets, IPs, clients, servers, etc.  We would welcome any additional resources for learning more about network programming.

For the chat application tutorials, there are a lot of tutorials online not limited to https://medium.com/@securosoft/simple-chat-server-using-sockets-in-c-f72fc8b5b24e, https://github.com/ruchirsharma1993/Chat-application-in-c-using-Socket-programming, and https://www.youtube.com/watch?v=fNerEo6Lstw&ab_channel=IdiotDeveloper.

We will also look into other groups’ projects from Project 1 such as https://github.com/olincollege/SoftSysTerminalConnect4 for inspiration on how they built their own server/client-based projects.

And hopefully, with our knowledge gained from the network documentation, we will be able to head into building the chat-based application on our own and not rely on the tutorials too much, but as a stepping stone if we get stuck at any point. And we want to demonstrate our understanding further by being able to scope past this to be able to send images and files through the chat-based application.

Heading into the project, our first few steps in this project are as follows:

1. Read through the basics of network programming from the resources we have compiled above to be able to know the terminology within this field as well as the structures. Our definition of “done” is to be able to know the basics of this field and put it on a document for referral when completing our research.

2. The next step is to develop a server/client connection that runs on two separate files. Our definition of done is a base on which we can develop our application, if the client says it has connected to the server end, then we can consider that complete.

3. Our third concrete step is to complete the MVP by having clients be able to send simple string messages through the server. Our definition of “done” is if we can have two clients connect to the server and send simple string messages to the server and have them viewable by each client.

