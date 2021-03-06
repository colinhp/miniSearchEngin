 ///
 /// @file    SocketIO.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-19 22:06:17
 ///

#include "SocketIO.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <iostream>

namespace ccx{

SocketIO::SocketIO(int sfd)
: _sfd(sfd)
{
}

ssize_t SocketIO::send_n(const char * buf, ssize_t size)
{
	ssize_t totle = 0;
	ssize_t temp;
	
	while(totle < size)
	{
		temp =  ::send(_sfd, buf + totle, size - totle, 0);
		if(temp <= 0)
		{
			perror("send");
			return -1;
		}
		totle += temp;
	}
	return totle;
}

ssize_t SocketIO::recv_n(char * buf, ssize_t size)
{
	ssize_t totle = 0;
	ssize_t temp;
	std::cout << size << std::endl;
	while(totle < size)
	{
		temp =  ::recv(_sfd, buf + totle, size - totle, 0);
		if(temp <= 0)
		{
			return -1;
		}
		totle += temp;
	}
	return totle;
}

int SocketIO::send_protocol(string & data)
{
	ssize_t ret;
	ssize_t size = strlen(data.c_str());
	ret = send_n((char*)&size, 4);
	if(-1 == ret)
	{
		return -1;
	}
	ret = send_n(data.c_str(), size);
	if(-1 == ret)
	{
		return -1;
	}
	return ret;
}

int SocketIO::recv_protocol(string & data)
{
	ssize_t ret;
	ssize_t size = 0;
	ret = recv_n((char*)&size, 4);
	if(-1 == ret)
	{
		return -1;
	}
	char * buf = new char[100000000];
	ret = recv_n(buf, size);
	if(-1 == ret)
	{
		return -1;
	}
	data = buf;
	delete [] buf;
	return ret;
}

}
