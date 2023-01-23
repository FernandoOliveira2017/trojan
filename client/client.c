#include <stdio.h>
#include <winsock2.h>

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	SOCKET clientSock;
	struct sockaddr_in addr;
	char msg[1024];
	
	ZeroMemory(&addr, sizeof(addr));
	
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port        = htons(atoi(argv[2]));
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	connect(clientSock, (struct sockaddr *) &addr, sizeof(addr));
	
	while (recv(clientSock, msg, 1024, 0)) {
		scanf(msg);
		send(clientSock, msg, strlen(msg), 0);
	}
	
	closesocket(clientSock);
	WSACleanup();
}
