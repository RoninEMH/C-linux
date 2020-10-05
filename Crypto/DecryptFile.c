#include "DecryptFile.h"

char *dencrypt(char *str)
{
    int len = strlen(str);
    char *temp = (char *)malloc(sizeof(char) * len);
    int i;
    for (i = 0; i < len; i++)
    {
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

void dencryptFile(char *fileName)
{
    FILE *fd = fopen(fileName, "r");
    FILE *otherfd;
    int len = strlen(fileName);
    int otherlen = strlen("Encrypted");
    char *originalFileName = (char *)malloc((len - otherlen) * sizeof(char));
    int i;
    char *buffer = (char *)malloc(100 * sizeof(char));
    int retVal;
    char *dencryptText;

    for (i = 0; i < len; i++)
        originalFileName[i] = fileName[i + otherlen];

    while (!feof(fd))
    {
        retVal = fread(fileName, sizeof(char), 1, fd);
        if (retVal == 0)
        {
            perror("error in reading file");
            exit(1);
        }
    }

    dencryptText = dencrypt(buffer);
    close(fd);
    otherfd = fopen(originalFileName, "w");
    fwrite(dencryptText, sizeof(char), strlen(dencryptText), otherfd);

    close(otherfd);
    free(originalFileName);
    free(dencryptText);
}

int main(int argc, char* args[])
{
    char *fileName = args[1];
    dencryptFile(fileName);
}