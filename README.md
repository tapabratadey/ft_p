# ft_p

![DEMO](https://user-images.githubusercontent.com/12387917/43361269-8012bd90-927f-11e8-8f57-d446db303e86.gif)

Ft_p, this project is about implementing a client and a server that allows the transfer of files within a TCP/IP network. I had to create my own C language based FTP server and client while utilizing the FTP/RFC protocol. This project taught me about sockets, TCP/IP protocols, and IPv4/IPv6. I chose a server system that utilizes a fork. All servers handle multiple simultaneous connections, and all clients are able to send, receive, and navigate their server file hierarchies, I implemented few shell commands such as ls, pwd, and cd. Also implemented a “get” function that downloads a file from the server to the client and a “put” function that uploads a file from the client to the server. I forked to run multiple processes to execute all the commands.</br>

Instructions on how to run it:</br>
git clone https://github.com/tapabratadey/ft_p.git && cd ft_p && sh run.sh</br></br>
To run the program:</br></br>
	Start the server:</br>
		./server 8080</br></br>
	connect a client:</br>
		cd client_env</br>
		./client 127.0.0.1 8080</br></br>
Commands available:</br>
	- cd to change directories</br>
	- ls to display the list of files and directories</br>
	- pwd to see the current working directory</br>
	- get to download files</br>
	- put to upload files</br>
	- quit to close the connection and exit the program</br>
