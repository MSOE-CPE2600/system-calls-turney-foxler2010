/*
 * Filename: finfo.c
 * Description: Demo of "File Management" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    // parse filename
    char *filename;
    if (argc == 2) {
        if (sscanf(argv[1], "%ms", &filename) < 1) {
            printf("error parsing argument.\n");
            exit(-1);
        }
    } else {
        printf("invalid argument(s).\n");
        exit(-1);
    }

    // get stat info for filename
    struct stat *finfo = calloc(1, sizeof(struct stat));
    if (lstat(filename, finfo) != 0) {
        printf("error accessing filename %s\n", filename);
        exit(-1);
    }

    // print info in user-friendly format
    printf("Filename: %s\n", filename);
    free(filename);

    printf("Type: ");
    if (S_ISREG(finfo->st_mode)) {
        // S_ISREG(m)  is it a regular file?
        printf("Regular file\n");
    } else if (S_ISDIR(finfo->st_mode)) {
        // S_ISDIR(m)  directory?
        printf("Directory\n");
    } else if (S_ISCHR(finfo->st_mode)) {
         // S_ISCHR(m)  character device?
        printf("Charatcer Device\n");
    } else if (S_ISBLK(finfo->st_mode)) {
        // S_ISBLK(m)  block device?
        printf("Block Device\n");
    } else if (S_ISFIFO(finfo->st_mode)) {
         // S_ISFIFO(m) FIFO (named pipe)?
        printf("FIFO (named pipe)\n");
    } else if (S_ISLNK(finfo->st_mode)) {
        // S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
        printf("Symbolic Link\n");
    } else if (S_ISSOCK(finfo->st_mode)) {
        // S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
        printf("Socket\n");
    } else {
        printf("Unrecognized type\n");
    }

    printf("Perms:\n");
    printf("Owner:\n");
    printf("Size:\n");
    printf("Last Modified:\n"); 
    
    free(finfo);
    return EXIT_SUCCESS;
}