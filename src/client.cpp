/*
 * client.cpp
 *
 *      Author: davlet
 */

#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <iostream>

#include <netinet/in.h>


int main()
{
    int sock;
    struct sockaddr_in addr;

    //enter login
    char* loginBuf = new char[100];
    std::cout << "login: " << std::endl;
    std::cin >> loginBuf;

    std::string login(loginBuf);
    delete[] loginBuf;

    std::cout << login << std::endl;
    std::cout << "strlen(login): " << login.size() << std::endl;

    //enter login
    char* passwordBuf = new char[100];
    std::cout << "password: " << std::endl;
    std::cin >> passwordBuf;

    std::string password(passwordBuf);
    delete[] passwordBuf;

    std::cout << password << std::endl;
    std::cout << "strlen(password): " << password.size() << std::endl;


    char buf[sizeof(login)];


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    auto sendedBytes = send(sock, login.c_str(), login.size(), 0);
    auto readedBytes = recv(sock, buf, login.size(), 0);

    std::cout << "sendedBytes: " << sendedBytes << std::endl;
    std::cout << "readedBytes: " << readedBytes << std::endl;

    std::cout <<"client: " << buf <<std::endl;

    sendedBytes = send(sock, password.c_str(), password.size(), 0);
    readedBytes = recv(sock, buf, login.size(), 0);

    std::cout << "sendedBytes: " << sendedBytes << std::endl;
    std::cout << "readedBytes: " << readedBytes << std::endl;

    //send(sock, nullptr, sizeof(login), 0);
    std::cout <<"client: " << buf <<std::endl;
    close(sock);

    return 0;
}
