/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include "folders.h"

#define LOG_NAME_SIZE 256
#define ERROR_SIZE 256

void get_error(int err, char *str, size_t str_len)
{
    if (err < sys_nerr) {
        snprintf(str, str_len, "%s", sys_errlist[err]);
    }
    else {
        snprintf(str, str_len, "Unknown error %d", err);
    }
}

void log_error(char *additional_info) 
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char log_name[LOG_NAME_SIZE], error[ERROR_SIZE];    
    get_error(errno, error, ERROR_SIZE);
    snprintf(log_name, LOG_NAME_SIZE - 1, "%d_%d_%d_%d_%d_%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    char folderName[] = "logs/\0";
    char *path_to_file = calloc(strlen(log_name) + strlen(folderName) + 1, sizeof(char)); // im_calloc may lead to recursion
    if(path_to_file == NULL) {
        exit(EXIT_FAILURE);
    }
    
    strcpy(path_to_file, folderName);
    create_folder_if_not_exists(path_to_file); 
    strcat(path_to_file, log_name);
    path_to_file[strlen(folderName) + strlen(log_name)] = '\0';
    
    FILE *log_file = fopen(path_to_file, "w"); 
    if(log_file != NULL) {
        fwrite(error, strlen(error), sizeof(char), log_file);
        fwrite("\n", 1, sizeof(char), log_file);
        fwrite(additional_info, strlen(additional_info), sizeof(char), log_file);
        fclose(log_file);
    }
    
    free(path_to_file);
}