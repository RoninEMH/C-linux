#include "DecryptFile.h"

char *decrypt(char *str)
{
    //setKey();
    //key is 0
    int len = strlen(str);
    char *temp = (char *)malloc(sizeof(char) * len);
    int i;
    for (i = 0; i < len; i++)
    {
        if (str[i] < 'a' || str[i] > 'z')
            str[i] = temp[i];
        if (str[i] - key < 'a')
        {
            int r = str[i] - 'a' - key + 1;
            temp[i] = 'z' + r;
        }
        else
            temp[i] = str[i] - key;
    }
    return temp;
}

void decryptFile(char *fileName)
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
    char *text = (char *)malloc(100 * sizeof(char));
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
    printf("key = %d\n", key);
    dencryptText = decrypt(text);
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
    decryptFile(fileName);
    return 0;
}