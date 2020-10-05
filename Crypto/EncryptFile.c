#include "EncryptFile.h"

void setKey()
{
    key = rand() % LEN;
}

char *encrypt(char *str)
{
    int len = strlen(str);
    char *temp = (char *)malloc(sizeof(char) * len);
    int i;
    setKey();
    for (i = 0; i < len; i++)
    {
        if (str[i] + key > 'z')
        {
            int r = str[i] + key - 1;
            temp[i] = 'a' + r - 'z';
        }
        else
            temp[i] = str[i] + key;
    }
    return temp;
}

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

void encryptFile(char *fileName)
{
    FILE *fd = fopen(fileName, "r");
    FILE *otherfd;
    char *buffer = (char *)malloc(100 * sizeof(char));
    int retVal;
    char *encryptText;
    char *newFileName;
    while (!feof(fd))
    {
        retVal = fread(buffer, sizeof(char), 1, fd);
        if (retVal == 0)
        {
            perror("error in reading file");
            exit(1);
        }
    }
    encryptText = encrypt(buffer);
    close(fd);
    newFileName = (char *)malloc((strlen("Encrypted") + strlen(fileName)) * sizeof(char));
    if (newFileName == NULL)
    {
        perror("memory error");
        exit(2);
    }
    newFileName = "Encrypted";
    strcat(newFileName, fileName);
    otherfd = fopen(newFileName, "w");
    fwrite(encryptText, sizeof(char), strlen(encryptText), otherfd);

    close(otherfd);
    //remove(fileName);
    free(newFileName);
    free(encryptText);
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

int main(int argc, char *args[])
{
    char *fileName = args[1];
    encryptFile(fileName);

    return 0;
}
