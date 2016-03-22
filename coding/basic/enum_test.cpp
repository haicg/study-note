#include <iostream>
int main()
{
    enum AA
    {
        A = 0xf0000
    };
    enum BB
    {
        B = (A<<12)
    };
    enum CC
    {
        C = 0xf0000000
    };
    std::cout << std::dec << B << std::endl;
    std::cout << std::hex << (B >> 12) << std::endl;
    std::cout << std::hex << sizeof(C) << std::endl;
    std::cout << std::dec << (C) << std::endl;
    std::cout << std::hex << (C >> 12) << std::endl;
    return 0;
}
