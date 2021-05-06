/*
 * clientHelper.h
 *
 *      Author: Davlet
 */

#ifndef CLIENTHELPER_H_
#define CLIENTHELPER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>

#include <memory>

inline int connecter(int _sock, std::shared_ptr<struct sockaddr_in> addr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = htons(3425);
	addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	return connect(_sock, (struct sockaddr *)addr.get(), sizeof(addr));
}



inline std::string getLogin()
{
	//enter login
    char* loginBuf = new char[100];
    std::cout << "login: " << std::endl;
    std::cin >> loginBuf;

    std::string login(loginBuf);
    delete[] loginBuf;

    return login;
}


inline std::string getPassword()
{
	//enter password
	char* passwordBuf = new char[100];
	std::cout << "password: " << std::endl;
	std::cin >> passwordBuf;

	std::string password(passwordBuf);
	delete[] passwordBuf;

	return password;
}


inline void authorization(int _sock)
{
	//enter login
	auto login = getLogin();

	//enter password
	auto password = getPassword();

	short int serverMsg;
	send(_sock, login.c_str(), login.size(), 0);
	recv(_sock, &serverMsg, sizeof(short int), 0);

	if(serverMsg == 401)
	{
		std::cout <<"This login is not registered " << std::endl;
		return;
	}

	send(_sock, password.c_str(), password.size(), 0);
	recv(_sock, &serverMsg, sizeof(short int), 0);

	if(serverMsg == 200)
	{
		std::cout <<"Access is allowed" << std::endl;
		return;
	}
	if(serverMsg == 401)
	{
		std::cout <<"Invalid password" << std::endl;
		return;
	}

}


inline void registration(int _sock)
{
	//enter login
	auto login = getLogin();

	//enter password
	auto password = getPassword();

	short int serverMsg;
	send(_sock, login.c_str(), login.size(), 0);
	recv(_sock, &serverMsg, sizeof(short int), 0);

	if(serverMsg == 401)
	{
		std::cout <<"This login is used already" << std::endl;
		return;
	}

	send(_sock, password.c_str(), password.size(), 0);
	recv(_sock, &serverMsg, sizeof(short int), 0);

	if(serverMsg == 200)
	{
		std::cout <<"Registration completed successfully" << std::endl;
		return;
	}
	if(serverMsg == 401)
	{
		std::cout <<"Server error" << std::endl;
		return;
	}
}

#endif /* CLIENTHELPER_H_ */
