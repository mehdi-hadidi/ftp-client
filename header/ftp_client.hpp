#pragma once
#include <iostream>
#include "net.hpp"


namespace mh
{   
    class FtpClient
    {
        private:
            mh::Net* net = nullptr;
            bool isConnected = false;
        private:
            inline size_t sendCommand(const char* ftp_cmp , const char* value);
        public:
            FtpClient(const char* host , unsigned short port);
            bool sendUser(const std::string& user);
            bool sendPassword(const std::string& password);
            ~FtpClient();        
    };    
} 
