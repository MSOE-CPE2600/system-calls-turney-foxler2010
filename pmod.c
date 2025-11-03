/*
 * Filename: pmod.c
 * Description: Demo of "Process Modification" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

// enables XSI extension along with POSIX.1-2008 base features
// needed to use nice()
#define _XOPEN_SOURCE 700
// _XOPEN_SOURCE >= 700 implicitly defines _POSIX_C_SOURCE = 200809L
//#define _POSIX_C_SOURCE 200809L

#define DURATION 1837272638

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    /*
     * nice()
     * increments the "niceness" of the calling process by the given amount.
     * "niceness" is a number that the kernel's scheduler uses along with other factors
     * to determine how much CPU time to give the process. It is called "niceness" because
     * the higher the number is, the "nicer" the process is to other processes by being more flexible
     * with its CPU time requirements.
     */
    nice(10);

    /*
     * nanosleep()
     * puts the process into a sleep state for the given duration of time (in timespec format).
     * the following code has the process sleep for DURATION nanoseconds (1,837,272,638ns).
     * that's 1 second and 837,272,638 nanoseconds.
     */
    struct timespec *duration = calloc(1, sizeof(struct timespec));
    duration->tv_sec = DURATION / (int) 1e9; // integer division
    duration->tv_nsec = DURATION % (int) 1e9;
    nanosleep(duration, duration);
    free(duration);

    printf("Goodbye!\n");
    return EXIT_SUCCESS;
}