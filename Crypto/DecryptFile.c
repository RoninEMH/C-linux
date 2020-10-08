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

    for (i = 0; i < len; i++)
    {
        if (temp[i] >= 'a' && temp[i] <= 'z')
            continue;
        if (str[i] < 'A' || str[i] > 'Z')
            temp[i] = str[i];
        else if (str[i] - key < 'A')
        {
            int r = str[i] - 'A' - key + 1;
            temp[i] = 'Z' + r;
        }
        else
            temp[i] = str[i] - key;
    }
    return temp;
}

void decryptFile(char *fileName, unsigned key)
{
    int i;
    FILE *fd = fopen(fileName, "r");
    FILE *otherfd;
    int len = strlen(fileName);
    char *buffer = (char *)malloc(1 * sizeof(char));
    int retVal;
    char *dencryptText;
    char *text = (char *)malloc(FILE_SIZE * sizeof(char));
    int index = 0;
    char *newFileName;
    int size = 0;
    char *finish;

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

    for (i = 0; i < len; i++)
    {
        if (fileName[i] == '.' && (fileName[i + 1] != '/' && fileName[i + 1] != '.'))
        {
            size = len - i;
            index = i;
            break;
        }
    }
    finish = (char *)malloc((size + 1) * sizeof(char));
    newFileName = (char *)malloc((strlen("Decrypted") + len) * sizeof(char));

    strncpy(newFileName, fileName, len - size);
    strcat(newFileName, "Decrypted");
    memcpy(finish, &fileName[index], size);
    finish[size] = '\0';
    strcat(newFileName, finish);

    otherfd = fopen(newFileName, "w");
    fwrite(dencryptText, sizeof(char), strlen(dencryptText), otherfd);

    fclose(otherfd);
    free(newFileName);
    free(dencryptText);
    free(text);
    free(dencryptText);
}

int main(int argc, char *args[])
{
    char *fileName = args[1];
    unsigned key = (unsigned)convert(args[2]);
    decryptFile(fileName, key);
    return 0;
}