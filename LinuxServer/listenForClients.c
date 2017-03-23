/*

这个函数主要用于监听用户的连接
实际上用NIO最利于服务端的管理


*/



void *listenForClients()
{
	//创建服务端的套接字
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		//错误处理，和报告
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		//错误处理，和报告
	}

	//开始监听  
	if (listen(slisten) == SOCKET_ERROR)
	{
		//错误处理，和报告
	}


	//循环接收数据  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	while (serverFlag)
	{

		//获得用户套接字
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);

		if (sClient == INVALID_SOCKET)
		{
			//错误处理，和报告
			continue;
		}

		//将用户套接字加入在线链表中
		addSocket(clientOnline, sClient);

		//调用serverForClient，开始为用户服务，单独写一个文件
		//这个项目核心部分
		if (pthread_create(null, null, serverForClient, sClient) == 0)
		{
			//对错误的处理和报告
		}
	}

	//对链表的删除
	freeSockets(clientOnline);
}