#pragma once
#include <iostream>
#include "net.hpp"
#include "ftp_reply.hpp"


namespace mh
{   
    class FtpClient
    {
        private:
            std::string dataIp;
            unsigned short dataPort = 0;
            unsigned short dataChannel = 0;
            mh::Net* net = nullptr;
            bool isConnected = false;
            unsigned short sendTimeout = 0;
            unsigned short receiveTimeout = 0;
        private:
            inline mh::FtpReply::FtpResult sendCommand(const char* ftp_cmp , const char* value = "");
            inline std::string receiveLine();
        public:
            FtpClient(const char* host , unsigned short port);
            void setSendTimeout(unsigned short);
            void setReceiveTimeout(unsigned short);
            unsigned short getReceiveTimeout();
            bool sendUser(const std::string& user);
            bool sendPassword(const std::string& password);
            mh::FtpReply::FtpResult sendCredential(const std::string& user , 
                                                   const std::string& password);
            mh::FtpReply::FtpResult sendPassive();                                       
            mh::FtpReply::FtpResult getList();                                       

            ~FtpClient();        
    };    
} 
