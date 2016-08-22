#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sstream>
#include <sys/socket.h>

#include "pop3.h"
#include "MailerException.h"

pop3::pop3()
{
}

pop3::~pop3()
{
	close(this->sock);
}

//获得用户指定的消息ID，然后将其从服务器上删除
std::string pop3::GetMsg(int msgId)
{
	this->createConnection();
	if(this->loginUser())//用户登录邮箱
	{
		this->sendMsg("LIST",msgId);
		std::string data = this->readData();

		if(!this->responseOK(data))
		{
			throw new MessageNotFoundException();
		}
		else
		{
			//下载消息
			this->sendMsg("RETR",msgId);
			data = this->readData("\r\n.\r\n");
			if(!this->responseOK(data))
			{
				throw new MessageRetrieveException();
			}

			data.replace(0,data.find_first_of("\n")+1,"");
			std::istringstream iss(data.erase(data.length()-3,3));

			//从服务器中删除邮件
			this->sendMsg("DELE",msgId);
			if(!this->responseOK(this->readData()))
			{
				throw new MessageDeleteException();
			}

			//退出连接
			this->logoutUser();

			return data;
		}
	}

	return "";
}

//建立与服务器的连接
void pop3::createConnection()
{
	struct sockaddr_in server;
	struct hostent * hostinfo;
	std::string ipAddress;

	this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if(this->sock == -1)
	{
		throw new SocketCreateException();
	}
	
	hostinfo = gethostbyname(this->getHostname().c_str());
	if(hostinfo)
	{
		in_addr *address = (in_addr *)hostinfo->h_addr_list[0];
		ipAddress = inet_ntoa(*address);
	}

	else
	{
		ipAddress = this->getHostname();
	}

	//设置服务器地址
	server.sin_family = AF_INET;
	server.sin_port = htons(this->port);
	server.sin_addr.s_addr = inet_addr(ipAddress.c_str());

	if(server.sin_addr.s_addr == INADDR_NONE)
	{
		throw new AddressInvalidException();
	}

	//连接服务器
	if(connect(this->sock,(struct sockaddr*)&server,sizeof(server)) == -1)
	{
		throw new ConnectionCreateException();
	}

	//读取消息
	std::string data = this->readData();

	if(!this->responseOK(data))
	{
		throw new NoResponseException();
	}
}

//读取来自套接字的数据
std::string pop3::readData(std::string delim)
{
	std::string data;
	int len = 0;
	char *buffer = new char [BUFFER_SIZE];
	while ((len = read(this->sock, buffer, BUFFER_SIZE)) > 0)
	{
		data.append(buffer,len);
		if(data.substr(data.size() - delim.size(),delim.size()).compare(delim) == 0)
			break;
	}

	return data;
}


//检测来自服务器的响应
bool pop3::responseOK(std::string data)
{
	if(data.length() < 3)
		return false;
	return (data.substr(0,3).compare("+OK") != 0) ? false : true;
}

bool pop3::loginUser()
{
	this->sendMsg("USER",this->getUsername());//校验用户名
	std::string data = this->readData();

	if(!this->responseOK(data))
	{
		throw new BadLoginOrPasswordException();
	}

	this->sendMsg("PASS",this->getPassword());//校验密码
	data = this->readData();

	if(!this->responseOK(data))
	{
		throw new BadLoginOrPasswordException();
	}

	return true;
}

void pop3::sendMsg(std::string msg,int param)
{
	std::stringstream ss;
	ss<<param;
	this->sendMsg(msg,ss.str());// 函数重载，用于将数值转化为字符串
}

void pop3::sendMsg(std::string msg,std::string param)
{
	std::string data;
	int len = 0;

	if(param.length() > 0)
	{
		msg.append(" ");
		msg.append(param);
	}

	msg.append("\r\n");

	write(this->sock,msg.c_str(),msg.length());
}

//用户登出
void pop3::logoutUser()
{
	this->sendMsg("QUIT");
	std::string data = this->readData();

	if(!this->responseOK(data))
	{
		throw new QuittingException();
	}
}
