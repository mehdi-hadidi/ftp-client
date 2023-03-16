#pragma once

#include <iostream>


namespace mh
{
    class Net
    {
        private:
            const char* m_host;
            const unsigned short m_port;
        public:
            Net();
            Net(const char* host , const unsigned short port);
            bool connect();
            bool disonnect();
            int send(const char* msg , size_t size);
            int send(const char* msg , size_t size , int timeout);
            int receive(char* msg , size_t size);
            int receive(char* msg , size_t size , int timeout);
    };
}
