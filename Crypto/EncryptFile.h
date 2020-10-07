#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>

#define LEN 26
#define FILE_SIZE 200 

static unsigned key;

void setKey();
char *encrypt(char *str);
void encryptFile(char *fileName);
