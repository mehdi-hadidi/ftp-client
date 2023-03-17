#pragma once

#include <iostream>


namespace mh
{
    class Net
    {
        private:
            const char* m_host;
            const unsigned short m_port;
            int m_sock_fd;
           
        public:
            Net() = delete;
            Net(const char* host , const unsigned short port);
            bool connect();
            void disonnect() noexcept;
            size_t send(const char* msg , size_t size , unsigned int timeout_milisec = 30);
            size_t receive(char* msg , size_t size , unsigned int timeout_milisec = 30);
    };
}
