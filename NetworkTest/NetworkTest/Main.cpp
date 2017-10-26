#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
		WSADATA wsaData;
	
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			fprintf(stderr, "WSAStartup failed.\n");
			exit(1);
		}

	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2) {
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	printf("IP addresses for %s:\n\n", argv[1]);

	for (p = res; p != NULL; p = p->ai_next) {
		void *addr;
		char *ipver;

		// get the pointer to the address itself,
		// different fields in IPv4 and IPv6:
		if (p->ai_family == AF_INET) { // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else { // IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		// convert the IP to a string and print it:
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("  %s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(res); // free the linked list

	WSACleanup();

	return 0;
}

//int main()
//{
//	WSADATA wsaData;
//
//	//sockaddr_in sa = getaddrinfo();
//
//	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
//	{
//		fprintf(stderr, "WSAStartup failed.\n");
//		exit(1);
//	}
//
//	//sockaddr_in sa;
//	//sockaddr_in6 sa6;
//
//	//sa.sin_addr. = INADDR_ANY;
//	//sa6.sin6_addr = in6addr_any;
//
//	int status;
//	struct addrinfo hints;
//	struct addrinfo *servinfo;
//
//	memset(&hints, 0, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_flags = AI_PASSIVE;
//
//	if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)))
//	{
//		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
//		exit(1);
//	}
//
//	freeaddrinfo(servinfo);
//
//	system("PAUSE");
//	return 0;
//}