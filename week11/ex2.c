#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    DIR *d;
    struct dirent *dir;
    d = opendir("/");
    if (d == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((dir = readdir(d)) != NULL)
    {
        printf("%s\n", dir->d_name);
    }
    closedir(d);

    return EXIT_SUCCESS;
}