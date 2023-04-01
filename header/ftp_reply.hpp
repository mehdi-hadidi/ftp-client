#pragma once
#include <iostream>
#include <unordered_map>

namespace mh
{
  class FtpReply
  {
  private:
    std::unordered_map<int, std::string> reply =
        {
            {200, "reply command ok"},
            {220, "service ready for new user"},
            {230, "login successful"},
            {331, "user name ok, need password"},
            {0, "unknown error"}

    };

  public:
    struct FtpResult
    {
      bool isOk = false;
      int rspCode = 0;
      std::string rspMessage;
    };

  public:
    std::string getReply(size_t status)
    {
      return reply[status];
    }
  };

}