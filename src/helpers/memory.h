/* 
 * File:   memory.h
 * Author: kaloyan
 *
 * Created on May 4, 2016, 11:39 PM
 */

#ifndef MEMORY_H
#define MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

    void* im_calloc(size_t nitems, size_t size);
    void* im_realloc(void* ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H */

