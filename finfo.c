/*
 * Filename: finfo.c
 * Description: Demo of "File Management" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
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
    printf("Filename: %s\n", filename);
    free(filename);
    return EXIT_SUCCESS;
}