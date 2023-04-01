#include <iostream>
#include <cstring>
// #include <format>

#include "../header/ftp_client.hpp"
#include "../header/common.hpp"
#include "../header/ftp_command.hpp"
#include "../header/ftp_reply.hpp"
#include "../header/utility.hpp"

mh::FtpClient::FtpClient(const char *host, unsigned short port)
{
    net = new Net(host, port);
    net->connect();

    char reply[1024] = {0x00};
    net->receive(reply, sizeof(reply));
}

mh::FtpReply::FtpResult mh::FtpClient::sendCredential(const std::string& user , 
                                                      const std::string& password)
{
    mh::FtpReply::FtpResult result;
    mh::FtpReply rply;

    result = sendCommand(CMD_USER, user.c_str()); // send username
    if(result.rspCode != 331)
    {
        return result;        
    }

    result = sendCommand(CMD_PASSWORD, password.c_str()); // send password
    if(result.rspCode != 230)
    {   
        return result; 
    }

    result.isOk = true;
    return result;

}


mh::FtpReply::FtpResult mh::FtpClient::getList()
{
    sendPassive();
    
    mh::Net net("10.0.0.169" , this->dataPort);
    if( net.connect() )
    {
        sendCommand(CMD_LIST); 
        char buff[1000] = {0x00};
        net.receive(buff , 1000 );
        std::cout << buff << std::endl;
        return {};
    }
    return {};
}


mh::FtpReply::FtpResult mh::FtpClient::sendPassive()
{
    // ex: (10,0,0,169,120,154)
    // ip = 10.0.0.169
    // port = 120 * 256 + 154 => 30874
    mh::FtpReply::FtpResult result = sendCommand(CMD_PASSIVE_MODE);
    if(result.rspCode != 227)
    {
        result.isOk = false;
        return result;
    }
    std::string str = result.rspMessage;
    int from  = str.find('(');
    int to = str.find(')');
    std::string result_ip_port = result.rspMessage.substr( from + 1, to - from - 1  );
    std::vector<std::string> separated =  mh::utility::split(result_ip_port , ',');

    
    this->dataIp.reserve(20);
    this->dataIp.append(separated[0]);
    this->dataIp.append(".");
    this->dataIp.append(separated[1]);
    this->dataIp.append(".");
    this->dataIp.append(separated[2]);
    this->dataIp.append(".");
    this->dataIp.append(separated[3]);


    this->dataPort = std::stoi(separated[4]) * 256 + std::stoi(separated[5]);


    return result; 

}


mh::FtpReply::FtpResult mh::FtpClient::sendCommand(const char *ftp_cmp, const char *value)
{
    char reply[MAX_LENGTH_SIZE] = {0x00};
    char cmd[30] = {0x00};
    std::sprintf(cmd, "%s %s\r\n", ftp_cmp, value);
    std::cout << cmd << std::endl;

    if (net->send(cmd, strlen(cmd)) > 0)
    {
        std::string str = receiveLine();     
        std::cout << str << std::endl;
        return {
            true,
            std::stoi(str.substr(0 , 3)) ,
            str.substr(4)
        };
        
    }

    return {false , 0 , "unknown exception"};
}



std::string mh::FtpClient::receiveLine()
{
    int len = 0;
    char reply[MAX_LENGTH_SIZE] = {0x00};

    unsigned short timeout = getReceiveTimeout();
    while (true)
    {
        len = net->receive(reply + len, sizeof(reply));
        if (len >= 3 && reply[len - 1] == 0x0A)
        {
            // std::cout << reply << std::endl;
            // char status[4] = {0x00};    
            // std::strncpy(status , reply , 3);
            // return std::stoi(status);

            return reply;

        }
        // else
        // {
        //     break;
        // }
    }

    return 0; // timeout
}

void mh::FtpClient::setSendTimeout(unsigned short timeout)
{
    this->sendTimeout = timeout;
}
void mh::FtpClient::setReceiveTimeout(unsigned short timeout)
{
    this->receiveTimeout = timeout;
}

unsigned short mh::FtpClient::getReceiveTimeout()
{
    return this->receiveTimeout;
}

mh::FtpClient::~FtpClient()
{
    net->disonnect();
    delete[] net;
}