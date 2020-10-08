#include "app.h"

void createCharacter(char *name, char *type, char *description, char *abilties)
{
    FILE *fd;
    char *fileName = (char *)malloc((strlen(name) + strlen(".txt")) * sizeof(char));
    char *buffer = (char *)malloc(FILE_SIZE * sizeof(char));
    char *path;

    strcpy(fileName, name);
    strcat(fileName, ".txt");

    strcpy(buffer, name);
    strcat(buffer, "\n\n");
    strcat(buffer,"Race: ");
    strcat(buffer, type);
    strcat(buffer, "\n\n");
    strcat(buffer,"Description: ");
    strcat(buffer, description);
    strcat(buffer, "\n\n");
    strcat(buffer,"Abilties: ");
    strcat(buffer, abilties);
    strcat(buffer, "\n\n");
    strcat(buffer, "Gather all the 7 Dragon Balls.");

    path = (char *)malloc(sizeof(char) * (strlen(fileName) + strlen("../Characters/")));

    strcpy(path, "../Characters/");
    strcat(path, fileName);

    printf("%s\n", path);
    fd = fopen(path, "w");
    fwrite(buffer, sizeof(char), strlen(buffer), fd);

    fclose(fd);
    free(fd);
    free(fileName);
    free(buffer);
}

int main(int argc, char *argv[])
{
    char *name = (char *)malloc(10 * sizeof(char));
    char *type = (char *)malloc(10 * sizeof(char));
    char *description = (char *)malloc(50 * sizeof(char));
    char *abilities = (char *)malloc(50 * sizeof(char));
    char space;
    printf("Enter all details: \n");
    printf("Name = ");
    scanf("%s", name);
    printf("Type = ");
    scanf("%s", type);
    scanf("%c", &space);
    printf("Description = ");
    if (fgets(description, 50, stdin) == NULL)
    {
        perror("error in input\n");
        exit(1);
    }

    printf("Abilties = ");
    scanf("%s", abilities);
    createCharacter(name, type, description, abilities);
    //printf("%s , %ld", name, strlen(name));
    return 0;
}