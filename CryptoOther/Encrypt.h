#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int power(int x, int y)
{
    int i;
    int result = 1;
    for (i = 0; i < y; i++)
        result *= x;
    return result;
}

char XOR(char x, char y)
{
    if ((x != '0' && x != '1') || (y != '0' && y != '1'))
        return 'x';
    else if (x == y)
        return '0';
    else
        return '1';
}

int binToDec(char *bin)
{
    int i;
    int len = strlen(bin);
    int dec = 0;
    for (i = 0; i < len; i++)
        dec += power(2, i) * (bin[len - i - 1] - '0');
    return dec;
}

char *decToBin(int num) //up to 2^8 - 1
{
    const int size = 8;
    char *bin = (char *)malloc(sizeof(char) * size);
    int i;
    int dec = num;
    int index = size - 1;
    while (index >= 0)
    {
        if (dec >= power(2, index))
        {
            dec -= power(2, index);
            bin[size - index - 1] = '1';
        }
        else
            bin[size - index - 1] = '0';

        index--;
    }
    return bin;
}