Prototype TCP Client–Server Chat Application
A simple prototype TCP client–server chat application developed in C using the Winsock API. The project demonstrates the fundamentals of socket-based communication by enabling bidirectional text messaging between a single client and a server through the command line.
Note: This is a prototype implementation created for learning basic socket programming concepts. It is designed to handle communication between one client and one server.

                 		Features
- Prototype client–server chat application
- Bidirectional text communication
- Configurable host and port using command-line arguments
- Basic input validation and error handling
- Command-line interface for interactive messaging
- Graceful session termination using a predefined exit command

 Technologies Used
- C
- Winsock2
- TCP Sockets
- Visual Studio / MSVC (Windows)

 Project Structure
```
├── server.c
├── client.c
└── README.md
```

 How It Works
1. Start the server by providing a port number.
2. Start the client with the server hostname and port.
3. The client connects to the server.
4. Both applications exchange text messages through the terminal.
5. Entering `Bye` ends the communication.

 Build
Compile both files using a C compiler with Winsock support.


### Server


```bash
cl server.c ws2_32.lib
```


### Client


```bash
cl client.c ws2_32.lib
```


## Run


Start the server:


```bash
server.exe <port>
```


Example:


```bash
server.exe 5000
```


Start the client:


```bash
client.exe <hostname> <port>
```


Example:


```bash
client.exe localhost 5000
```
 
 Learning Objectives
This project was built to understand the basics of:


- TCP socket communication
- Client–server architecture
- Winsock programming in C
- Sending and receiving messages using sockets
- Basic socket error handling 
