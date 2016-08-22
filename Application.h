#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#define DEFAULT_PORT 110

struct Params
{
	std::string hostname;
	std::string username;
	std::string password;
	int port;
	int msgId;
};

class Application
{
public:
	Params * ProcessParams(Params pa);
	void Run(Params *p);
};

#endif
