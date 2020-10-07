#include "DecryptFile.h"

int power(int x, int y)
{
    int i;
    int result = 1;
    for (i = 0; i < y; i++)
        result *= x;
    return result;
}

int convert(char *str)
{
    int len = strlen(str);
    int i;
    int num = 0;
    for (i = len; i > 0; i--)
        num += (int)(str[i - 1] - '0') * power(10, len - i);
    return num;
}

char *decrypt(char *str, unsigned key)
{
    //key must be put in
    int len = strlen(str);
    printf("len = %d\n", len);
    char *temp = (char *)malloc(sizeof(char) * len);
    int i;
    for (i = 0; i < len; i++)
    {
        if (str[i] < 'a' || str[i] > 'z')
            temp[i] = str[i];
        else if (str[i] - key < 'a')
        {
            int r = str[i] - 'a' - key + 1;
            temp[i] = 'z' + r;
        }
        else
            temp[i] = str[i] - key;
    }
    return temp;
}

void decryptFile(char *fileName, unsigned key)
{
    FILE *fd = fopen(fileName, "r");
    FILE *otherfd;
    int len = strlen(fileName);
    int otherlen = strlen("Encrypted");
    char *originalFileName = (char *)malloc((len - otherlen) * sizeof(char));
    int i;
    char *buffer = (char *)malloc(1 * sizeof(char));
    int retVal;
    char *dencryptText;
    char *text = (char *)malloc(FILE_SIZE * sizeof(char));
    int index = 0;

    for (i = 0; i < len - otherlen + 1; i++)
        originalFileName[i] = fileName[i + otherlen];

    while (!feof(fd))
    {
        retVal = fread(buffer, sizeof(char), 1, fd);
        if (retVal == 0)
        {
            printf("\nmessage = %s\n", text);
            break;
        }
        text[index] = *buffer;
        index++;
    }
    text = (char *)realloc(text, index * sizeof(char));
    dencryptText = (char *)malloc(strlen(text) * sizeof(char));
   
    dencryptText = decrypt(text, key);
    fclose(fd);
    
    otherfd = fopen(originalFileName, "w");
    fwrite(dencryptText, sizeof(char), strlen(dencryptText), otherfd);

    fclose(otherfd);
    free(originalFileName);
    free(dencryptText);
}

int main(int argc, char *args[])
{
    char *fileName = args[1];
    unsigned key = (unsigned)convert(args[2]);
    decryptFile(fileName, key);
    return 0;
}