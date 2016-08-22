/*
 * MailerException.h
 *
 *  Created on:	Aug 12, 2011
 *      Author: Marek Hlobil, marek.hlobil@gmail.com
 */

#include <iostream>
#include <exception>

#ifndef MAILEREXCEPTION_H_
#define MAILEREXCEPTION_H_

class MailerException
{
public:
	virtual const char* what() = 0;
};

class SocketCreateException: public MailerException
{
public:
	const char* what() { return "Unable to create socket."; }
	virtual ~SocketCreateException() {}
};

class ConnectionCreateException: public MailerException
{
public:
	const char* what() { return "Unable to connect to server."; }
	virtual ~ConnectionCreateException() {}
};

class NoResponseException: public MailerException
{
public:
	const char* what() { return "No response from server."; }
	virtual ~NoResponseException() {}
};

class HostToIPException: public MailerException
{
public:
	const char* what() { return "Unable to get IP address from hostname."; }
	virtual ~HostToIPException() {}
};

class AddressInvalidException: public MailerException
{
public:
	const char* what() { return "Bad hostname / IP address."; }
	virtual ~AddressInvalidException() {}
};

class BadLoginOrPasswordException: public MailerException
{
public:
	const char* what() { return "Bad login or password."; }
	virtual ~BadLoginOrPasswordException() {}
};

class MessageNotFoundException: public MailerException
{
public:
	const char* what() { return "Message with given id was not found."; }
	virtual ~MessageNotFoundException() {}
};

class InvalidPortNumberException: public MailerException
{
public:
	const char* what() { return "Given port number is invalid."; }
	virtual ~InvalidPortNumberException() {}
};

class QuittingException: public MailerException
{
public:
	const char* what() { return "Failed to QUIT properly."; }
	virtual ~QuittingException() {}
};

class MessageRetrieveException: public MailerException
{
public:
	const char* what() { return "Failed to retrieve message from server."; }
	virtual ~MessageRetrieveException() {}
};

class MessageDeleteException: public MailerException
{
public:
	const char* what() { return "Failed to delete message from server."; }
	virtual ~MessageDeleteException() {}
};

#endif /* MAILEREXCEPTION_H_ */
