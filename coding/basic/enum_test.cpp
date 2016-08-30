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
    std::cout <<"A = " << std::hex << A << std::endl;
    std::cout <<"B>>12 = " << std::hex << (B >> 12) << std::endl;
    std::cout <<"C = " << std::hex << (C >> 12) << std::endl;
    return 0;
}
