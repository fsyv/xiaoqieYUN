/*


该函数主要为服务器的核心框架
为客户端提供服务和响应


*/


void *serverForClient(Socket client)
{
	//命令枚举
	Order order;
	char[5][20] orderPara;

	//等待用户的登陆
	//这个函数响应用户的登陆操作
	//刚点开客户端只是完成连接
	//返回值为布尔值，函数操作完成查表，和生成用户文件结构，生成文件结构另写一个函数文件
	if (waitForLogin(client) == false)
	{
		//相关处理
	}

	while (serverFlag)
	{
		//读取用户命令和提供的参数
		readOrder(client, orderPara);
		if (order.Load == toInt(orderPara[0]))
		{
			//相关操作
		}


		/*
		
		如果想再加功能，类似加语句
		但要保证一个功能一个函数
		保持这个文件的“简洁性”
		这只是个框架，有语法错误的
		
		
		*/
	}
}