#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <exception>

#include "../header/net.hpp"
#include "../header/common.hpp"

mh::Net::Net(const char* host , const unsigned short port) : m_host(host) ,
                                                        m_port(port)
{
   // std::cout << "constructor...\n";
}

bool mh::Net::connect()
{
    int  valread, client_fd;
    struct sockaddr_in serv_addr;

    if ((this->m_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Socket creation error" << std::endl;
        return false;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_port);
 
    if (inet_pton(AF_INET, m_host, &serv_addr.sin_addr) <= 0 ) {
        std::cout << "Address is not supported" << std::endl;
        return false;
    }
 
    if ((::connect(this->m_sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) 
    {
        std::cout << "connection Failed" << std::endl;
        return false;
    }
     
    return true;

}

size_t mh::Net::send(const char* i_msg , size_t size , unsigned int timeout_milisec)
{
   return write(this->m_sock_fd , i_msg, size);
}

size_t mh::Net::receive(char* o_msg , size_t size , unsigned int timeout_milisec)
{
    while(true)
    {
        const mh::common::Result ret = mh::common::wait(this->m_sock_fd , timeout_milisec);
        if(ret == mh::common::Result::EXCEPTION)
        {
            throw "exception";
        }
        else if(ret == mh::common::Result::TIMEOUT)
        {
            throw "time out";
        }

        return read(this->m_sock_fd , o_msg , size);
    }
}

void mh::Net::disonnect() noexcept
{
     close(this->m_sock_fd);
}