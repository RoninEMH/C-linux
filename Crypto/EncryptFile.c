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
        if (str[i] < 'a' || str[i] > 'z')
            temp[i] = str[i];
        else if (str[i] + key > 'z')
        {
            int r = str[i] + key - 1;
            temp[i] = 'a' + r - 'z';
        }
        else
            temp[i] = str[i] + key;
    }
    return temp;
}

void encryptFile(char *fileName)
{
    int i;
    FILE *fd = fopen(fileName, "r");
    FILE *otherfd;
    char *buffer = (char *)malloc(1 * sizeof(char));
    int index = 0;
    int retVal;
    char *encryptText;
    char *newFileName;
    char *text = (char *)calloc(FILE_SIZE, sizeof(char));
    int size = 0;

    while (!feof(fd))
    {
        retVal = fread(buffer, sizeof(char), 1, fd);
        if (retVal == 0)
            break;
        text[index] = *buffer;
        index++;
    }

    text = (char *)realloc(text, index * sizeof(char));
    encryptText = (char *)malloc(strlen(text) * sizeof(char));
    encryptText = encrypt(text);
    fclose(fd);

    for (i = 0; i < strlen(fileName); i++)
    {
        if (fileName[i] == '.')
        {
            size = strlen(fileName) - i;
            break;
        }
    }

    newFileName = (char *)malloc((strlen("Encrypted") + strlen(fileName)) * sizeof(char));
    strncpy(newFileName, fileName, strlen(fileName) - size);
    strcat(newFileName, "Encrypted");
    strcat(newFileName, ".txt");

    otherfd = fopen(newFileName, "w");
    fwrite(encryptText, sizeof(char), strlen(encryptText), otherfd);

    fclose(otherfd);
    //remove(fileName);
    free(buffer);
    free(text);
    free(newFileName);
    free(encryptText);
}

int main(int argc, char *args[])
{
    char *fileName = args[1];
    encryptFile(fileName);
    return 0;
}
