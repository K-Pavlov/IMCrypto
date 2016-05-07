#include <string.h>
#include <stdlib.h>

#if __unix__ 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void create_folder_if_not_exists(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }      
}

int file_exist (char *filename)
{
    struct stat buffer;   
    return (stat (filename, &buffer) == 0);
}

#else
#include <windows.h>

void create_folder_if_not_exists(char *path) {
    CreateDirectory(path, NULL);
}
#endif