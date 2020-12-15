/*
 * client.cpp
 *
 *      Author: davlet
 */

#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <memory>
#include "clientHelper.h"


int main()
{
	int sock;
	auto addrPtr = std::make_shared<struct sockaddr_in>();

	short int req;
	short int serverAnswer;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    if(connecter(sock, addrPtr) < 0)
    {
        perror("connect");
        exit(2);
    }


    std::cout << "0: Sign in" << std::endl << "1: Sign up" << std::endl;
	std::cin >> req;


    if(req == 0)
    {
    	send(sock, &req, sizeof(short int), 0);
    	authorization(sock);
    }
    else if (req == 1)
    {
    	send(sock, &req, sizeof(short int), 0);
    	registration(sock);
    }

    close(sock);

    return 0;
}
