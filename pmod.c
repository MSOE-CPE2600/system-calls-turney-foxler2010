/*
 * Filename: pmod.c
 * Description: Demo of "Process Modification" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 199309L
#define DURATION 1837272638

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    nice(10);
    struct timespec *duration = calloc(1, sizeof(struct timespec));
    duration->tv_sec = DURATION / (int) 1e9;
    duration->tv_nsec = DURATION % (int) 1e9;
    nanosleep(duration, duration);
    free(duration);
    printf("Goodbye!\n");
    return EXIT_SUCCESS;
}