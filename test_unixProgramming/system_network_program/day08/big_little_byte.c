#include <stdio.h>
#include <stdint.h>

typedef union big_little_endian
{
    int data;
    // char ch;
    uint8_t oneByte;
}ble;

void test_big_or_little_endian()
{
    ble bigOrLittleEndian;
    bigOrLittleEndian.data = 0x12345678;  

    // printf("little address = %x\n", bigOrLittleEndian.ch);  // 78
    printf("little address = %x\n", bigOrLittleEndian.oneByte);  // 78
}

void test_big_or_little_endian01()
{
    int a = 0x12345678;

    printf("little address = %x\n", *(char*)&(a));  // 78 低地址放低字节：小端序
}

int main()
{
    // test_big_or_little_endian();
    test_big_or_little_endian01();
    
    return 0;
}