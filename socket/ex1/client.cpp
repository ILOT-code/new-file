

#include <iostream>
#include <WinSock2.h> //包含 WinSock2.h 头文件
using namespace std;
#pragma comment(lib, "ws2_32.lib") //加载 ws2_32.dll 
#pragma warning(disable:4996)
int main()
{
//****初始化 WSA
	WSADATA wsaData;
//初始化版本
	WSAStartup(MAKEWORD(2, 2), &wsaData);
//****创建用户端 socket
	SOCKET sock = socket(PF_INET, SOCK_STREAM,);
//****创建 sockAddr 结构体
	sockaddr_in sockAddr;
//每个字节都用 0 填充
	memset(&sockAddr, 0, sizeof(sockAddr));
//绑定服务器、端口
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_port = htons(1234);
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//****建立链接
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	cout << "客户端发送链接请求" << endl;
//****接收服务器传回的数据
	while (1)
	{
		char szBuffer[MAXBYTE] = { 0 };
		recv(sock, szBuffer, MAXBYTE, 0);
		if (strcmp(szBuffer, "quit") == 0)
			break;
		cout << "接受服务器传回的消息函数" << endl;
		cout << szBuffer << endl;
	}
//****关闭套接字、终止使用 DLL
	closesocket(sock);
	WSACleanup();
	return 0;
}
