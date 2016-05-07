/* 
 * File:   memory.c
 * Author: kaloyan
 *
 * Created on May 4, 2016, 11:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "memory.h"

void* im_calloc(size_t nitems, size_t size) 
{
    void* res = calloc(nitems, size);
    if(res == NULL) {
        log_error("im_calloc");
        exit(EXIT_FAILURE);
    }
    
    return res;
}

void* im_realloc(void *ptr, size_t size) 
{
    void* res = realloc(ptr, size);
    if(res == NULL) {
        log_error("im_realloc");
        exit(EXIT_FAILURE);
    }
    
    return res;
}


