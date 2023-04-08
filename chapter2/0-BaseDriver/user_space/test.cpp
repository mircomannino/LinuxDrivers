#include <iostream>
#include "user_space_driver.h"

int main() 
{
    constexpr uint32_t size = 32;
    char buf[32];

    for(size_t i = 0; i < size; i++) 
        buf[i] = 65;
    std::cout << "Initial: "; print_buffer(buf, size);

    device_read(buf, size); 
    std::cout << "Before writing dev: "; print_buffer(buf, size);

    buf[11] = 'M';
    buf[12] = 'I';
    buf[13] = 'R';
    buf[14] = 'C';
    buf[15] = 'O';
    device_write(buf, size); 
    std::cout << "After Writing dev: "; print_buffer(buf, size);
}