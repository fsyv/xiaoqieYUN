/*

这个文件为服务器的基本框架，主要分割出不同模块，对一些函数进行必要的说明。


*/
#include<...>

//用于记录已经连接的的用户，在这可以用链表来保存，但当数量变多时遍历比较耗时，理想的数据结构为map，但c中没有这种数据结构有时间可以用c实现类似java的map
//独立写一个sockets的c文件包含数据结构和操作
Sockets clientOnline = null;

//用于记录服务器是否开始工作，同时控制服务器的开关
bool serverFlag = false;

int main()
{


	//独立用一个线程来监听用户的连接
	//listenForClients函数独立写一个文件,该函数的
	if (pthread_create(null, null, listenForClients, null) == 0)
	{
		//对错误的处理和报告
	}


	//还可以在这写界面，用于用户的管理

	//重点在listenForCLients中和它所调用的serverForClientForClients
}