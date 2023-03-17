#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "../header/common.hpp"

const mh::common::Result mh::common::wait(const int fd, const unsigned int timeout)
{
    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    return (mh::common::Result) select(fd + 1, &fds, nullptr, nullptr, &tv);
}