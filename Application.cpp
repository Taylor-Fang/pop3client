#include <cstdlib>
#include <sstream>
#include "Application.h"
#include "pop3.h"
#include "MailerException.h"
#include <fstream>

Params * Application::ProcessParams(Params pa)
{
	Params * params = new Params();
	params->port = pa.port;
	params->msgId = pa.msgId;
	params->hostname = pa.hostname;
	params->username = pa.username;
	params->password = pa.password;

	return params;
}

void Application::Run(Params * p)
{
	pop3 * POP3 = new pop3();
	POP3->setHostname(p->hostname);
	POP3->setUsername(p->username);
	POP3->setPassword(p->password);
	POP3->setPort(p->port);

	try
	{
		std::ofstream fout;
		fout.open("mail.txt");
		fout<<POP3->GetMsg(p->msgId);
		std::cout<<"Data has been received!"<<std::endl;
		fout.close();
	}
	catch(MailerException * e)
	{
		std::cerr << e->what() << std::endl;
	}

	delete POP3;
}
