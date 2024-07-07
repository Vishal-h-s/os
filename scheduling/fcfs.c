/* FCFS Scheduling
Enter the number of processes: 3
Assuming Arrival time is 0 for all processes.
Process number 0
Burst Time:24
Process number 1
Burst Time:3
Process number 2
Burst Time:4
The Table is:
PID AT BT WT TAT
0    0 24  0  24
1    0  3 24  27
2    0  4 27  31
Average Waiting Time = 17.000000
Average TurnAround Time = 27.333334 */

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Assuming Arrival time is 0 for all processes\n");
    size_t int_size=sizeof(int);
    int * bursttime=(int*)calloc(n,int_size), * turnaroundtime=(int*)calloc(n,int_size), * waitingtime=(int*)calloc(n,int_size);
    int totalwaitingtime = 0;
    int totalturnaroundtime = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Process number %d\n", i);
        printf("Burst Time:");
        scanf("%d", &bursttime[i]);
    }
    waitingtime[0] = 0;
    for (int i = 1; i < n; i++)
    {
        waitingtime[i] = waitingtime[i - 1] + bursttime[i - 1];
        totalwaitingtime += waitingtime[i];
    }
    for (int i = 0; i < n; i++)
    {
        turnaroundtime[i] = waitingtime[i] + bursttime[i];
        totalturnaroundtime += turnaroundtime[i];
    }
    printf("\nThe Table is:\n\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t0\t%d\t%d\t%d\n", i, bursttime[i], waitingtime[i], turnaroundtime[i]);
    }

    free(bursttime);
    free(turnaroundtime);
    free(waitingtime);

    float avgwaitingtime = (float)totalwaitingtime / n;
    float avgturnaroundtime = (float)totalturnaroundtime / n;
    printf("\nAverage Waiting Time = %f\n", avgwaitingtime);
    printf("Average TurnAround Time = %f\n", avgturnaroundtime);
    return 0;
}

/*$ gcc scheduling/fcfs.c 
wishall@fedora:~/os$ ./a.out 
Enter the number of processes: 3
Assuming Arrival time is 0 for all processes
Process number 0
Burst Time:24
Process number 1
Burst Time:3
Process number 2
Burst Time:4

The Table is:

PID     AT      BT      WT      TAT
0       0       24      0       24
1       0       3       24      27
2       0       4       27      31

Average Waiting Time = 17.000000
Average TurnAround Time = 27.333334
wishall@fedora:~/os$ */