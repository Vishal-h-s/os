/*1.Let's consider a school computer lab where students use computers for various
educational activities, including research, programming assignments, and multimedia
projects based on their arrival times.Here are some example tasks (student activities)
that the lab server might receive throughout the day:
•
Student A needs to complete an online quiz: Burst Time = 15 minutes, Arrival Time
= 08:30 AM
•
Student B is working on a programming assignment: Burst Time = 40 minutes,
Arrival Time = 08:40 AM
•
Student C wants to edit a multimedia project: Burst Time = 25 minutes, Arrival
Time = 08:50 AM
•
Student D needs to research for a presentation: Burst Time = 30 minutes, Arrival
Time = 09:00 AM
Objective:Your task as a developer is to help the students to carry their tasks by using a
scheduling algorithm. Calculate the waiting time and turnaround time for each task, and
determine the average waiting and turnaround time for the day's tasks.
// Identify the type of CPU scheduling algorithm for the scenario and implement the same
in C Language. Calculate Average Turn Around time and Average Waiting time for each of
the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with
the output of the program.*/


#include <stdio.h>
int main()
{
    int n = 4;
    char tasks[] = {'A', 'B', 'C', 'D'};
    int burstTimes[] = {15, 40, 25, 30};
    int arrivalTimes[] = {510, 520, 530, 540};
    int waitingTimes[4];
    int turnaroundTimes[4];
    int completionTimes[4];
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < arrivalTimes[i])
        {
            currentTime = arrivalTimes[i];
        }
        waitingTimes[i] = currentTime - arrivalTimes[i];
        completionTimes[i] = currentTime + burstTimes[i];
        currentTime = completionTimes[i];
        turnaroundTimes[i] = completionTimes[i] - arrivalTimes[i];
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
    }
    printf("Task\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c\t%d\t\t%d\t\t%d\t\t%d\n", tasks[i], arrivalTimes[i], burstTimes[i], waitingTimes[i],
               turnaroundTimes[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
    return 0;
}