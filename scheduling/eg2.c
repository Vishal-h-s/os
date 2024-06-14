/*2.Imagine an animation studio, Pixie Animations, which specializes in creating short
animated films and digital commercials. Due to the studio’s growing popularity and
increased client demands, the animation rendering tasks have piled up. Throughout a
typical day, various rendering tasks are submitted to the server. Each task has a specific
duration determined by the complexity of the animation scenes involved. The goal is to
minimize the overall waiting time and maximize resource utilization by strategically
scheduling the tasks based on their duration. Write the Corresponding CPU Scheduling
algorithm.
Here are some example tasks that the server might receive on a typical day:
•
Task A - Rendering a simple character animation: Burst Time = 15 minutes, Arrival
Time = 09:00 AM
•
Task B - Rendering a complex explosion scene: Burst Time = 30 minutes, Arrival
Time = 09:10 AM
•
Task C - Rendering a detailed background scene: Burst Time = 20 minutes, Arrival
Time = 09:15 AM
•
Task D - Rendering a short dialogue scene: Burst Time = 10 minutes, Arrival Time
= 09:30 AM

// Identify the type of CPU scheduling algorithm for the scenario and implement the same
in C Language. Calculate Average Turn Around time and Average Waiting time for each of
the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with
the output of the program.*/


#include <stdio.h>
int main()
{
    int n = 4;
    int burstTime[] = {15, 30, 20, 10};
    int arrivalTime[] = {540, 550, 555, 570};
    int waitingTime[n], turnAroundTime[n], completionTime[n];
    int isCompleted[n];
    int currentTime = 0;
    int completedTasks = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
    }
    while (completedTasks < n)
    {
        int minBurstTime = 1000000;
        int shortestTask = -1;
        for (int i = 0; i < n; i++)
        {
            if (arrivalTime[i] <= currentTime && isCompleted[i] == 0)
            {
                if (burstTime[i] < minBurstTime)
                {
                    minBurstTime = burstTime[i];
                    shortestTask = i;
                }
            }
        }
        if (shortestTask == -1)
        {
            currentTime++;
            continue;
        }
        currentTime += burstTime[shortestTask];
        completionTime[shortestTask] = currentTime;
        turnAroundTime[shortestTask] = completionTime[shortestTask] - arrivalTime[shortestTask];
        waitingTime[shortestTask] = turnAroundTime[shortestTask] - burstTime[shortestTask];
        totalWaitingTime += waitingTime[shortestTask];
        totalTurnAroundTime += turnAroundTime[shortestTask];
        isCompleted[shortestTask] = 1;
        completedTasks++;
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