#include "Application.h"

#define QLEN 16

int main()
{
	Application * app = new Application();
	Params pa;
	pa.hostname = "pop3.sina.com";//使用的新浪邮箱
	pa.username = "username@sina.com";//邮箱地址
	pa.password = "***********";//邮箱密码
	pa.port = 110;
	pa.msgId = 1;

	Params *p = app->ProcessParams(pa);
	app->Run(p);

	delete app;
}
