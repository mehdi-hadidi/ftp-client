#pragma once
namespace mh::common
{
    enum class Result{
        EXCEPTION = -1,
        TIMEOUT = 0
    };

    const Result wait(const int fd, const unsigned int timeout = 30);
};