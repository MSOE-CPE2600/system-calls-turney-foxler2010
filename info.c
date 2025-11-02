/*
 * Filename: info.c
 * Description: Demo of "Information Maintenance" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

#define _POSIX_C_SOURCE 200112L
#define HOSTNAME_STRING_SIZE 30

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    /*
     * Time of day (nanoseconds)
     */
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    clock_gettime(CLOCK_REALTIME, &ts);
    struct tm *time = localtime(&ts.tv_sec);
    time_t time_in_secs = (time->tm_hour * 3600) + (time->tm_min * 60) + time->tm_sec;
    printf("Time of day (seconds w/ nanosecond resolution): %lu.%lus\n", time_in_secs, ts.tv_nsec);

    /*
     * Hostname
     *
     * gethostname() writes the network hostname of the system to the given string with the given length
     */
    char hostname[HOSTNAME_STRING_SIZE];
    gethostname(hostname, HOSTNAME_STRING_SIZE);
    printf("Hostname: %s\n", hostname);

    /*
     * System name
     *
     * uname() writes some information about the system to the given "struct utsname".
     * One of these pieces of information is the name of the operating system, which is what we're looking for in this section.
     * So, uname() is the right system call to use in this scenario.
     */

    // calloc clears all the different parts of the struct for me so I don't have to do it manually.
    struct utsname *name = calloc(1, sizeof(struct utsname));
    uname(name);
    printf("Operating System Name: %s\n", name->sysname);
    
    /*
     * OS release/version
     *
     * We can continue to use uname()'s output for this section.
     */
    printf("OS Release: %s\n", name->release);
    printf("OS Version: %s\n", name->version);
    
    /*
     * Hardware type
     *
     * We can continue to use uname()'s output for this section.
     */
    printf("Hardware Type: %s\n", name->machine);
    free(name);
    
    /*
     * # of CPUs
     *
     * There are two syscalls to get the # of processors:
     * - get_nprocs_conf(), which returns the number of physical CPU chips plugged into the computer, and
     * - get_nprocs(), which returns the number of CPUs that are able to be used by the system.
     */
    printf("The system has %d processors installed/configured,\n", get_nprocs_conf());
    printf("and %d processors active and ready to use.\n", get_nprocs());
    
    /*
     * Physical memory (in bytes)
     *
     * sysinfo() returns useful constants regarding the system, similar to uname().
     * It can be used to get information about the amount of memory in the system.
     */
    struct sysinfo *info = calloc(1, sizeof(struct sysinfo));
    sysinfo(info);
    printf("Physical Memory: %lu B\n", info->totalram);
    
    /*
     * Free memory (in bytes)
     *
     * We can continue to use sysinfo()'s output for this section.
     */
    printf("Available Memory: %lu B\n", info->freeram);
    free(info);

    return EXIT_SUCCESS;
}