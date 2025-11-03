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
#include <time.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    /*
     * Parse filename
     */
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

    /*
     * Get stat info for filename
     */
    struct stat *finfo = calloc(1, sizeof(struct stat));
    if (lstat(filename, finfo) != 0) {
        printf("error accessing filename %s\n", filename);
        free(filename);
        free(finfo);
        exit(-1);
    }

    /*
     * Print info in user-friendly format
     * Filename:
     */
    printf("Filename: %s\n", filename);
    // filename is no longer needed
    free(filename);

    /*
     * File type:
     */
    printf("Type: ");
    // values of type_char were pulled from the "ls" info page
    char type_char;
    if (S_ISREG(finfo->st_mode)) {
        // S_ISREG(m)  is it a regular file?
        printf("Regular file\n");
        type_char = '-';
    } else if (S_ISDIR(finfo->st_mode)) {
        // S_ISDIR(m)  directory?
        printf("Directory\n");
        type_char = 'd';
    } else if (S_ISCHR(finfo->st_mode)) {
         // S_ISCHR(m)  character device?
        printf("Charatcer Device\n");
        type_char = 'c';
    } else if (S_ISBLK(finfo->st_mode)) {
        // S_ISBLK(m)  block device?
        printf("Block Device\n");
        type_char = 'b';
    } else if (S_ISFIFO(finfo->st_mode)) {
         // S_ISFIFO(m) FIFO (named pipe)?
        printf("FIFO (named pipe)\n");
        type_char = 'p';
    } else if (S_ISLNK(finfo->st_mode)) {
        // S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
        printf("Symbolic Link\n");
        type_char = 'l';
    } else if (S_ISSOCK(finfo->st_mode)) {
        // S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
        printf("Socket\n");
        type_char = 's';
    } else {
        printf("Unrecognized type\n");
    }

    /*
     * File permissions:
     */
    printf("Perms: %c", type_char);
    if (finfo->st_mode & S_IRUSR) printf("r"); else printf("-");
    if (finfo->st_mode & S_IWUSR) printf("w"); else printf("-");
    if (finfo->st_mode & S_IXUSR) printf("x"); else printf("-");
    if (finfo->st_mode & S_IRGRP) printf("r"); else printf("-");
    if (finfo->st_mode & S_IWGRP) printf("w"); else printf("-");
    if (finfo->st_mode & S_IXGRP) printf("x"); else printf("-");
    if (finfo->st_mode & S_IROTH) printf("r"); else printf("-");
    if (finfo->st_mode & S_IWOTH) printf("w"); else printf("-");
    if (finfo->st_mode & S_IXOTH) printf("x"); else printf("-");
    printf("\n");

    /*
     * UID of file's owner:
     */
    printf("Owner UID: %d\n", finfo->st_uid);

    /*
     * Size of file in bytes:
     */
    printf("Size: %ld B\n", finfo->st_size);

    /*
     * File's last modified time:
     */
    struct tm *time = localtime(&(finfo->st_mtim.tv_sec));
    if (time->tm_hour <= 12) {
        printf("Last Modified: %d/%d/%d %02d:%02d:%02dAM\n", time->tm_mon + 1, time->tm_mday, time->tm_year + 1900,
                                                           time->tm_hour, time->tm_min, time->tm_sec);
    } else {
        printf("Last Modified: %d/%d/%d %02d:%02d:%02dPM\n", time->tm_mon + 1, time->tm_mday, time->tm_year + 1900,
                                                           time->tm_hour - 12, time->tm_min, time->tm_sec);
    }

    free(finfo);
    return EXIT_SUCCESS;
}