#include "Encrypt.h"

void setKey(int *key)
{
    srand(1);
    //*key = rand();
    *key = 98;
}

char *Encrypt(char *str)
{
    int len = strlen(str);
    int i;
    int val;
    int *key = &val;
    setKey(key);
    printf("key = %d\n", *key);
    char *binKey = decToBin(*key);
    printf("binary key = %s\n", binKey);
    int index = 0;
    int otherIndex = 0;
    int eindex = 0;
    char *encryptedStr = (char *)malloc(8 * sizeof(char));
    char *encryptedText = (char *)malloc(strlen(str) * sizeof(char));
    for (i = 0; i < len; i++)
    {
        char *binStr = decToBin((int)str[i]);
        //printf("binStr = %s\n", binStr);
        while (eindex <= 7)
        {
            encryptedStr[eindex++] = XOR(binStr[otherIndex++], binKey[index++]);
            if (otherIndex == 8)
                otherIndex = 0;
            if (index == 8)
                index = 0;
        }
        //printf("encryptedStr = %s\n", encryptedStr);
        encryptedText[i] = (char)binToDec(encryptedStr);
        //printf("%c\n", encryptedText[i]);
        eindex = 0;
    }
    //printf("encrypt = %s\n", encryptedText);
    return encryptedText;
}

int main(int argc, char *args[])
{
    char *text = "Hello, World";
    char *res = (char *)malloc(strlen(text) * sizeof(char));
    res = Encrypt(text);

    char *other = (char *)malloc(strlen(text) * sizeof(char));
    other = Encrypt(res);

    printf("result = %s\n", other);
    return 0;
}