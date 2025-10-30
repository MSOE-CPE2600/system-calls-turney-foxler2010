/*
 * Filename: info.c
 * Description: Demo of "Information Maintenance" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{
    /*
     * Time of day (nanoseconds)
     */
    struct timespec *ts = malloc(sizeof(struct timespec));
    ts->tv_sec = 0;
    ts->tv_nsec = 0;
    clock_gettime(CLOCK_REALTIME, ts);
    long time = ((long) ts->tv_sec * 10^9) + ts->tv_nsec;
    printf("Time: %ldns\n", time);
    free(ts);

    /*
     * Hostname
     */

    /*
     * System name
     */
    
    /*
     * OS release/version
     */
    
    /*
     * Hardware type
     */
    
    /*
     * # of CPUs
     */
    
    /*
     * Physical memory (in bytes)
     */
    
    /*
     * Free memory (in bytes)
     */

    return EXIT_SUCCESS;
}