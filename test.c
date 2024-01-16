#include <stdio.h>
#include <stdlib.h>

#define IS_NTH_BIT(n, k) (n & (1 << k))

int main()
{
    printf("%d\n", IS_NTH_BIT(345, 17));
}