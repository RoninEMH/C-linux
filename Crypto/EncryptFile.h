#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>

#define LEN 26
static unsigned key;

void setKey();
char *encrypt(char *str);
void encryptFile(char *fileName);
