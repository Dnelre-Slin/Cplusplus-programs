#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <vector>
#include <thread>

#pragma comment (lib, "ws2_32.lib")

void runClientComm(SOCKET *clientSocketPtr, sockaddr_in *clientPtr, int *clientSizePtr, bool *serverRunning)
{
	SOCKET &clientSocket = *clientSocketPtr;
	sockaddr_in &client = *clientPtr;
	int &clientSize = *clientSizePtr;

	if (*serverRunning)
	{
		if (clientSocket == INVALID_SOCKET)
		{
			std::cerr << "Can't create client socket! Qutting\n";
			return;
		}

		char host[NI_MAXHOST];		// Client's remote name
		char service[NI_MAXSERV];	// Service (i.e. port) the client is connected on

		ZeroMemory(host, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			std::cout << host << " connected on port " << service << std::endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			std::cout << host << " connect on port " <<
				ntohs(client.sin_port) << std::endl;
		}

		std::cout << "Client port: " << client.sin_port << '\n';

		// While loop: accept and echo message back to client
		char buf[4096];

		while (*serverRunning)
		{
			ZeroMemory(buf, 4096);

			// Wait for client to send data.
			int bytesReceived = recv(clientSocket, buf, 4096, 0);
			if (bytesReceived == SOCKET_ERROR)
			{
				std::cerr << "Error in resv(). Qutting" << std::endl;
				break;
			}

			if (bytesReceived == 0)
			{
				std::cout << "Client disconnected\n";
				break;
			}

			std::cout << std::string(buf, 0, bytesReceived) << '\n';

			// Echo message back to client.
			std::cout << "Just before sending.\n";
			send(clientSocket, buf, bytesReceived + 1, 0);
			std::cout << "Just after sending.\n";
		}
	}


	// Close the socket
	closesocket(clientSocket);
	delete clientSocketPtr;
	delete clientPtr;
	delete clientSizePtr;
}

std::string strToLower(const std::string &str)
{
	std::string str_lower;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		str_lower.push_back(tolower(str[i]));
	}
	return str_lower;
}

void shutdownFunc(bool *run, SOCKET *listener)
{
	while (*run)
	{
		std::string command;
		std::getline(std::cin, command);
		if (strToLower(command) == "shutdown")
		{
			closesocket(*listener);
			*run = false;
		}
	}
}

int main()
{
	// Initialize winsock
	WSAData wsaData;
	WORD ver = MAKEWORD(2, 2);

	if (WSAStartup(ver, &wsaData) != 0)
	{
		std::cerr << "Can't Initialize winsock! Quitting\n";
		return 0;
	}

	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create listening socket! Qutting\n";
		return 0;
	}

	// Bind the an ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;		//Could also use inet_pton .....
	
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	std::vector<std::thread> threads;
	bool serverRunning = true;

	sockaddr_in *client;
	int *clientSize;
	SOCKET *clientSocket;


	std::thread shutdownCommandThread(shutdownFunc, &serverRunning, &listening);

	while (serverRunning)
	{
		client = new sockaddr_in;
		clientSize = new int(sizeof(*client));
		clientSocket = new SOCKET(accept(listening, (sockaddr*)client, clientSize));

		std::cout << "At first: " << client->sin_port << '\n';
		std::cout << "New connection attempting to be established.\n";
		threads.push_back(std::thread(runClientComm, clientSocket, client, clientSize, &serverRunning));
	}

	shutdownCommandThread.join();
	for (unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}

	closesocket(listening);
	//if (clientSocket == INVALID_SOCKET)
	//{
	//	std::cerr << "Can't create a socket! Qutting\n";
	//	return 0;
	//}

	//char host[NI_MAXHOST];		// Client's remote name
	//char service[NI_MAXSERV];	// Service (i.e. port) the client is connected on

	//ZeroMemory(host, NI_MAXHOST);
	//ZeroMemory(service, NI_MAXSERV);

	//if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	//{
	//	std::cout << host << " connected on port " << service << std::endl;
	//}
	//else
	//{
	//	inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	//	std::cout << host << " connect on port " <<
	//		ntohs(client.sin_port) << std::endl;
	//}

	//// Close listening socket
	////closesocket(listening);

	//// While loop: accept and echo message back to client
	//char buf[4096];
	//
	//while (true)
	//{
	//	ZeroMemory(buf, 4096);

	//	// Wait for client to send data.
	//	int bytesReceived = recv(clientSocket, buf, 4096, 0);
	//	if (bytesReceived == SOCKET_ERROR)
	//	{
	//		std::cerr << "Error in resv(). Qutting" << std::endl;
	//		break;
	//	}
	//	
	//	if (bytesReceived == 0)
	//	{
	//		std::cout << "Client disconnected\n";
	//		break;
	//	}

	//	std::cout << std::string(buf, 0, bytesReceived) << '\n';

	//	// Echo message back to client.
	//	send(clientSocket, buf, bytesReceived + 1, 0);
	//}

	//// Close the socket
	//closesocket(clientSocket);

	// Cleanup winsock
	WSACleanup();
}