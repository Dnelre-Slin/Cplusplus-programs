#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

int main()
{
	std::string ipAddress = "127.0.0.1";      //Server ip address.
	int port = 54000;						// Listening port # of server.

	// Initialize WinSock.
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsRes;
	
	if ((wsRes = WSAStartup(ver, &data)) != 0)
	{
		std::cerr << "Can't start winsock. Err #" << wsRes << '\n';
		return 0;
	}

	// Create socket.
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't start winsock. Err #" << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}

	// Fill in a hint structure.
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server.
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server. Err #" << WSAGetLastError() << '\n';
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	// Do-while loop to send and receive data.
	char buf[4096];
	std::string userInput;

	do
	{
		// Prompt the user for some text.
		std::cout << "> ";
		getline(std::cin, userInput);

		if (userInput.size() > 0) // Make sure user has typed something.
		{
			// Send the text.
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response.
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console.
					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << '\n';
				}

			}

		}
		
	} while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}