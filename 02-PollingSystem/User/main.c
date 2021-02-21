#include "ARMCM3.h"

uint32_t flag1;
uint32_t flag2;

void delay(uint32_t count)
{
    while(count--);
}

int main(void)
{
    while(1)
    {
        /* 任内1实现 flag1 周期为 4 us的翻转 */
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);
        /* 任内1实现 flag2 周期为 4 us的翻转 */
        flag2 = 1;
        delay(100);
        flag2 = 0;
        delay(100);
    }
}
