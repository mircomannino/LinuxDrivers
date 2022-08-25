#ifndef __USER_SPACE_DRIVER_H__
#define __USER_SPACE_DRIVER_H__

#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <unistd.h>

const char* FILE_PATH = "/dev/base_driver";

int device_read(char* buf, const size_t count) 
{
    int fd = open(FILE_PATH, O_RDONLY);
    auto check = read(fd, buf, count);
    close(fd);
    if(!check) 
    {
        std::cerr << "Error: cannot read from the device\n"; 
        return 1;
    }
    return 0; 
}

int device_write(const char* buf, const size_t count)
{
    int fd = open(FILE_PATH, O_RDWR);
    auto check = write(fd, buf, count);
    close(fd);
    if(!check) 
    {
        std::cerr << "Error: cannot write to the device\n";
        return 1;
    }
    return 0;
}

void print_buffer(char* buf, const size_t count) 
{
    for(auto i = 0; i < count; i++) 
    {
        std::cout << buf[i];
    }
    std::cout << std::endl;
}

#endif