#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define DIR_PATH "./tmp/"
#define SEP " ---- "

unsigned int i_node;
char *file_name;

int filter(const struct dirent *entry) {
    if (entry->d_ino == i_node)
        return 1;
    return 0;
}

int main() {
    DIR *tmp;
    struct dirent *dir;
    tmp = opendir(DIR_PATH);
    if (tmp) {
        printf("File"SEP"Hard Links\n");
        while ((dir = readdir(tmp)) != NULL) {
            struct dirent **files = NULL;
            i_node = dir->d_ino;
            file_name = dir->d_name;
            int len = scandir(DIR_PATH, &files, filter, NULL);
            if (len >= 2) {
                printf("%s"SEP, file_name);
                while (len--) {
                    printf("%s", files[len]->d_name);
                    if (len) {
                        printf(", ");
                    }
                }
                printf("\n");
            }
            free(files);
        }
        closedir(tmp);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}