#ifndef POP3_H_
#define POP3_H_

#include <iostream>
#include <vector>
#include <string>

#define BUFFER_SIZE 256

class pop3
{
private:
	std::string hostname;
	std::string username;
	std::string password;
	int port;
	int sock;

	void createConnection();//创建连接
	std::string readData(std::string delim = "\r\n");
	bool responseOK(std::string data);
	void sendMsg(std::string msg,std::string param = "");
	void sendMsg(std::string msg,int param);
	bool loginUser();//用户登录
	void logoutUser();//用户登出
public:
	pop3();
	~pop3();

	std::string GetMsg(int msgId = 1);
	std::string getHostname() const
	{
		return hostname;
	}
	
	std::string getPassword() const
	{
		return password;
	}

	int getPort() const
	{
		return port;
	}

	std::string getUsername() const
	{
		return username;
	}

	void setHostname(std::string hostname)
	{
		this->hostname = hostname;
	}

	void setPassword(std::string password)
	{
		this->password = password;
	}

	void setUsername(std::string username)
	{
		this->username = username;
	}

	void setPort(int port)
	{
		this->port = port;
	}
};

#endif
