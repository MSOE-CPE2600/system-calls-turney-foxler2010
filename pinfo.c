/*
 * Filename: pinfo.c
 * Description: Demo of "Process Control" POSIX system calls
 * Author: Drew Malone <malonea@msoe.edu>
 * Course: CPE 2600 111
 * Assignment: Lab 9 - System Calls
 * Created: 10/30/25
 * Compile with: make
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    // determine pid to use
    pid_t pid;
    if (argc == 2) {
        if (sscanf(argv[1], "%d", &pid) < 1) {
            printf("error parsing argument.\n");
            exit(-1);
        }
    } else if (argc == 1) {
        pid = 0;
    } else {
        printf("invalid arguments.\n");
        exit(-1);
    }
    printf("PID: %d\n", pid);
    
    /*
     * getpriority()
     * returns the priority of the given process, process group, or user
     */
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (errno == ESRCH) {
        printf("process with pid %d could not be found.\n", pid);
        exit(-1);
    } else if (errno != 0) {
        printf("error getting information about pid %d.\n", pid);
        exit(-1);
    }
    printf("Priority: %d\n", priority);

    /*
     * sched_getscheduler()
     * returns the scheduling policy for the given process
     */
    int policy = sched_getscheduler(pid);
    if (policy == SCHED_OTHER) {
        printf("Scheduling Policy: SCHED_OTHER\n");
    } else if (policy == SCHED_BATCH) {
        printf("Scheduling Policy: SCHED_BATCH\n");
    } else if (policy == SCHED_IDLE) {
        printf("Scheduling Policy: SCHED_IDLE\n");
    } else {
        printf("Scheduling Policy not normal; number is %d\n", policy);
    }

    /*
     * EXTRA:
     * getpid(): returns the PID of the process that called this function
     * getcpu(): gets the number of the CPU that the process is running on
     * getrusage(): provides a structure with the amount of system resources the process is using
     * getrlimit(): provides the resource limit for a given process and resource
     */

    return EXIT_SUCCESS;
}