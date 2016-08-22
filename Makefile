client:client.cpp pop3.o Application.o MailerException.h
	g++ -o client client.cpp pop3.o Application.o
pop3.o:pop3.cpp pop3.h MailerException.h
	g++ -o pop3.o -c pop3.cpp
Application.o:Application.cpp Application.h pop3.h MailerException.h
	g++ -o Application.o -c Application.cpp
