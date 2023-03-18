#include <iostream>
#include <cstring>
// #include <format>

#include "../header/ftp_client.hpp"
#include "../header/command.hpp"
#include "../header/reply_command.hpp"


mh::FtpClient::FtpClient(const char* host , unsigned short port)
{
    net = new Net(host , port);
    net->connect();

    char reply[1024] = {0x00};
    net->receive(reply , sizeof(reply));
}

bool mh::FtpClient::sendUser(const std::string& user)
{   
   return sendCommand(CMD_USER , user.c_str()) == RPLY_LOGIN_SUCCESSFUL ?
                                              true : 
                                              false;                  
}

 bool mh::FtpClient::sendPassword(const std::string& password)
 {
    return sendCommand(CMD_PASSWORD , password.c_str()) == RPLY_SERVICE_READY_FOR_NEW_USER ? 
                                                       true : 
                                                       false;
 }                                                   


size_t mh::FtpClient::sendCommand(const char* ftp_cmp , const char* value)
{
    char reply[1024] = {0x00};
    char cmd[30] = {0x00};
    std::sprintf(cmd , "%s %s\r\n" , ftp_cmp , value);
    if( net->send(cmd , strlen(cmd)) > 0)
    {
        if( net->receive(reply , sizeof(reply)) > 0)
        {
            std::cout << reply << std::endl;
            reply[3] = 0x00;
            return std::stoi(reply);
        }
         
    }

    return 0;
}

mh::FtpClient::~FtpClient()
{
    net->disonnect();
    delete[] net;
}