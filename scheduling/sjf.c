/* Write a program for SJF
Enter the number of process:4
Enter process name, arrival time& burst time:1
1
3
Enter process name, arrival time& burst time:2
2
4
Enter process name, arrival time& burst time:3
1
2
Enter process name, arrival time& burst time:4
4
4
Processnamearrivaltime bursttime waitingtime turnaroundtime
3 1 2 0 2
1 1 3 2 5
2 2 4 4 8
4 4 4 6 10
Average waiting time: 3.000000
Average turnaroundtime: 6.250000 */

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    printf("Enter the number of process:");
    scanf("%d", &n);
    int *processName = (int *)calloc(n, sizeof(int)), *arrivalTime = (int *)calloc(n, sizeof(int)), *burstTime = (int *)calloc(n, sizeof(int));
    printf("Enter process name, arrival time & burst time\n");
    for (int i = 0; i < n; i++)
    {
        printf("for Process %d:\n", i + 1);
        scanf("%d %d %d", &processName[i], &arrivalTime[i], &burstTime[i]);
    }
    printf("\n");

    int temp;
    int burstSum = __INT_MAX__;
    //bubble sort based on burst time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (
                (arrivalTime[j] > arrivalTime[j + 1] || arrivalTime[j] == arrivalTime[j + 1])
                && burstTime[j] > burstTime[j + 1])
            {
                temp = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j + 1];
                arrivalTime[j + 1] = temp;
                temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;
                temp = processName[j];
                processName[j] = processName[j + 1];
                processName[j + 1] = temp;
            }
        }
        if (burstSum > arrivalTime[i])
            burstSum = arrivalTime[i];
    }

    int *completionTime = (int *)calloc(n, sizeof(int)), *waitingTime = (int *)calloc(n, sizeof(int)), *turnaroundTime = (int *)calloc(n, sizeof(int));

    float totalTat = 0;
    float totalWt = 0;
    printf("ProcessName\tarrivaltime\tbursttime\twaitingtime\tturnaroundtime\n");
    for (int i = 0; i < n; i++)
    {
        burstSum += burstTime[i];
        completionTime[i] = burstSum;
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        totalTat += turnaroundTime[i];
        totalWt += waitingTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processName[i], arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    free(processName);
    free(arrivalTime);
    free(burstTime);
    free(completionTime);
    free(waitingTime);
    free(turnaroundTime);

    printf("Average waiting time: %f\n", totalWt / n);
    printf("Average turnaroundtime: %f\n", totalTat / n);
    return 0;
}