/* 
 * File:   folders.h
 * Author: kaloyan
 *
 * Created on May 7, 2016, 12:00 PM
 */

#ifndef FOLDERS_H
#define FOLDERS_H

#ifdef __cplusplus
extern "C" {
#endif
    void create_folder_if_not_exists(const char *path);
    int file_exist (char *filename);
#ifdef __cplusplus
}
#endif

#endif /* FOLDERS_H */

