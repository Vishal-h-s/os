/* 3. Imagine an Emergency Medical Dispatch Center (EMDC) tasked with coordinating
emergency medical responses across a large urban area. The center receives calls about
various emergencies—accidents, medical crises, and urgent patient transfers. Identify
the algorithm helps prioritize shorter-duration tasks, allowing the center to quickly
dispatch assistance for multiple emergencies, potentially saving more lives by reducing
the response time.
Task Simulation:
Here are some examples of calls received by the EMDC one morning:
1.
Call A - Rapid response for a cardiac arrest at a home: Initial Burst Time = 7
minutes, Arrival Time = 08:00 AM
2.
Call B - Ambulance dispatch for a minor car accident: Initial Burst Time = 5
minutes, Arrival Time = 08:01 AM3.
Call C - Coordinate a helicopter for a critical transfer from a rural area: Initial Burst
Time = 3 minutes, Arrival Time = 08:02 AM
4.
Call D - Send paramedics to a multiple injury accident on a highway: Initial Burst
Time = 20 minutes, Arrival Time = 08:15 AM
5.
Call E - Dispatch an ambulance for a sudden stroke case: Initial Burst Time = 10
minutes, Arrival Time = 08:20 AM

// Identify the type of CPU scheduling algorithm for the scenario and implement the same
in C Language. Calculate Average Turn Around time and Average Waiting time for each of
the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with
the output of the program.*/


#include <stdio.h>
#define MAX 100
int main()
{
    int n = 5;
    int burstTime[] = {7, 5, 3, 20, 10};
    int arrivalTime[] = {8 * 60, 8 * 60 + 1, 8 * 60 + 2, 8 * 60 + 15, 8 * 60 + 20};
    int remainingTime[MAX];
    int waitingTime[MAX], turnAroundTime[MAX], completionTime[MAX];
    int isCompleted[MAX];
    int currentTime = 0;
    int completedTasks = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = burstTime[i];
        isCompleted[i] = 0;
    }
    while (completedTasks < n)
    {
        int minRemainingTime = MAX;
        int shortestTask = -1;
        for (int i = 0; i < n; i++)
        {
            if (arrivalTime[i] <= currentTime && isCompleted[i] == 0 && remainingTime[i] < minRemainingTime)
            {
                minRemainingTime = remainingTime[i];
                shortestTask = i;
            }
        }
        if (shortestTask == -1)
        {
            currentTime++;
            continue;
        }
        currentTime++;
        remainingTime[shortestTask]--;
        if (remainingTime[shortestTask] == 0)
        {
            completionTime[shortestTask] = currentTime;
            turnAroundTime[shortestTask] = completionTime[shortestTask] -
                                           arrivalTime[shortestTask];
            waitingTime[shortestTask] = turnAroundTime[shortestTask] - burstTime[shortestTask];
            totalWaitingTime += waitingTime[shortestTask];
            totalTurnAroundTime += turnAroundTime[shortestTask];
            isCompleted[shortestTask] = 1;
            completedTasks++;
        }
    }
    printf("Task\tBurst Time\tArrival Time\tWaiting Time\tTurn Around Time\tCompletion Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c\t%d\t\t%d:%02d\t\t%d\t\t%d\t\t\t%d:%02d\n", 'A' + i, burstTime[i], arrivalTime[i] / 60, arrivalTime[i] % 60, waitingTime[i], turnAroundTime[i], completionTime[i] / 60,
               completionTime[i] % 60);
    }
    printf("Average Waiting Time: %.2f minutes\n", (float)totalWaitingTime / n);
    printf("Average Turn Around Time: %.2f minutes\n", (float)totalTurnAroundTime / n);
    return 0;
}