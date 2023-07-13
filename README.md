# Command Line Socket Chat
2-party chat program
## Table of Content:

- [About The Program](#about-the-program)
- [Screenshot](#screenshot)
- [Technologies](#technologies)
- [Setup](#setup)
- [Status](#status)


## About The Program
This is a program written in C that can operate in server or client mode based on the command-line arguments provided. 
It reads data from standard input and sends it over a network connection, and it reads data from a network connection and writes it to standard output. 
It uses the poll function to know when data is available to read or when it can write data without blocking.
## Screenshot

![image](https://github.com/arjuntrivedi/Command-line-Chat-System/assets/72959325/ae23c33f-e437-48bd-9e3e-1eeedc74841b)


## Technologies
I used C and Socket Programming, applying concepts including TCP/IP, protocol POSIX System Calls, and I/O handling.

## Setup
- Compile the C code using a compiler like gcc
`gcc socketchat.c -o socketchat`
- Start terminal 1 (Server) with `./socketchat`
    -The terminal will display a message saying that the server is listening on a particular port. 
- Start terminal 2 (Client) using the localhost IP address and the server port.
`./socketchat [IP address] [Port #]`
- After this, the client will be connected to the server. Whatever you type in Terminal 2 (client) will be sent to the server and vice versa.
- Note: If you're running this on two different machines, use the IP address of the server machine.


## Status - In Progress
I have plans to extend this application with additional features, such as support for multiple clients, GUI, encryption, and authentication.

