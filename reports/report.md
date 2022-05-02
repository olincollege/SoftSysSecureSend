# SoftSysSecureSend

A multi-user, file-transfer capable chatroom in C developed by [Conan McGannon](https://github.com/hyrtzhyro) and [Daniel Park](https://github.com/DanPark13).

## Content

Your project report should answer the following questions (note that some are the same as in the proposal):

1) What is the goal of your project; for example, what do you plan to make, and what should it do?

Our goal of our project is to learn about network programming in C by building a chat application using sockets. As we mentioned in our proposal, our lower bound is building a simple chat application usable by multiple connected clients. However, our stretch goal for this project is an application where multiple clients can not only send messages, but also files such as documents and images as well.

2) What are your learning goals; that is, what do you intend to achieve by working on this project?

As mentioned in our proposal and update, our learning goals for this project are to use effective software development tools such as Makefiles and libraries, as well as learning more about network programming's concepts such as servers, clients, sockets, communication protocols, and such. Like our “Lisperers” project, we want to use the project as a learning experience, to focus on learning through the development process rather than focusing on the final product.

3) What resources did you find that were useful to you?  If you found any resources you think I should add to the list on the class web page, please email them to me.

The resources that we used can be separated into two categories: network programming documentation and chat application tutorials. We wanted to learn more about networks due to our lack of knowledge in the area, so we used resources like
- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/), 
- [Carleton University COMP1406 Course's Chapter 12 on Network Programming](https://people.scs.carleton.ca/~lanthier/teaching/COMP1406/Notes/COMP1406_Ch12_NetworkProgramming.pdf),
- [Internal Pointers' "Network programming for beginners: introduction to sockets" Article](https://internalpointers.com/post/network-programming-beginners-overview),
- and [GeeksforGeeks' "Socket Programming in C/C++" Article](https://www.geeksforgeeks.org/socket-programming-cc/#:~:text=What%20is%20socket%20programming%3F,reaches%20out%20to%20the%20server)

to learn more about the different terminology such as sockets, IPs, clients, servers, etc.

For the chat application tutorials, we ended up deciding on following [IdiotDeveloper's "Chatroom in C using Threads | Socket Programming in C" Tutorial](https://www.youtube.com/watch?v=fNerEo6Lstw&ab_channel=IdiotDeveloper) for the basic multi-user chatroom structure, and using . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .(add whichever file transfer resources used here) to allow for file transfer between clients on the server.


4) What were you able to get done?  Include in the report whatever evidence is appropriate to demonstrate the outcome of the project.  Consider including snippets of code with explanation; do not paste in large chunks of unexplained code.  Consider including links to relevant files.  And do include output from the program(s) you wrote.

5) Explain at least one design decision you made.  Were there several ways to do something?  Which did you choose and why?

6) You will probably want to present a few code snippets that present the most important parts of your implementation.  You should not paste in large chunks of code or put them in the Appendix.  You can provide a link to a code file, but the report should stand alone; I should not have to read your code files to understand what you did.

7) Reflect on the outcome of the project in terms of your learning goals.  Between the lower and upper bounds you identified in the proposal, where did your project end up?  Did you achieve your learning goals?

### Lisperers Answer (for reference):

Overall, we are satisfied with our work completing the Lisp-based calculator. While we were not able to reach our goals of building a full-fledged Lisp language that can have programs be built off of it, we are satisfied more in the progress we made learning about the Lisps, its uses, history, and implementation. We learned a lot when it comes to special ways in parsing through Symbolic Expressions and Quoted Expressions within a Lisp environment. In our next steps, we hope to continue this project further to include string and conditional implementations as well as implementing a standard library of functions so a future user may be able to implement a project using the language.

But with where we are at right now, through all that learning and progress we made in this month, we were able to have an implementation that can take in input, parse it for specific commands, compute mathematical operations, and save operations and integers into functions and variables respectively.




Audience: Target an external audience that wants to know what you did and why.  More specifically, think about students in future versions of SoftSys who might want to work on a related project.  Also think about people who might look at your online portfolio to see what you know, what you can do, and how well you can communicate.

 You don't have to answer the questions above in exactly that order, but the logical flow of your report should make sense.  Do not paste the questions into your final report. 

## Submission Mechanics

1) In your project report, you should already have a folder called "reports" that contains a Markdown document called "update.md".  Make a copy of "update.md" called "report.md"

2) At the top of this document, give your report a title that at least suggests the topic of the project.  The title should not contain the name of the class or the words "project" or "report".

3) List the complete names of all members of the team. 

4) Answer the questions in the Content section, above. Use typesetting features to indicate the organization of the document.  Do not include the questions as part of your document.

5) Complete your update, view it on GitHub, and copy the GitHub URL.  Then paste the URL in the submission space below.
