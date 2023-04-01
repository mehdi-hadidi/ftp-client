#pragma once
namespace mh::common
{
    #define MAX_LENGTH_SIZE 1024
    #define MODE_ACTIVE  1
    #define MODE_PASSIVE 2


    enum class Result{
        EXCEPTION = -1,
        TIMEOUT = 0
    };

    const Result wait(const int fd, const unsigned int timeout = 30);
};