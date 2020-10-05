#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>

#define LEN 26
static unsigned key;

void setKey();
char *encrypt(char *str);
char *dencrypt(char *str);
void encryptFile(char *filename);
void dencryptFile(char *filename);