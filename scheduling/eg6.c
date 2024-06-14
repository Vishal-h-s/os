/* 6.A local library system incorporates several branches, each equipped with computers
used for catalog searches, digital archives access, and various educational programs.
During the peak hours of library operation, patrons often need to use computers for
tasks like research, document processing, or accessing public records. The library staff
sets up a system where each user is allotted a 2-minute slot. If a user’s task is not
completed within this period, they go back to the end of the queue for another turn.
identify the scheduling algorithm.
Process Id Arrival time Burst time
P1
0
5
P2
1
3
P3
2
1
P4
3
2
P5
4
3
// Identify the type of CPU scheduling algorithm for the scenario and implement the same
in C Language. Calculate Average Turn Around time and Average Waiting time for each of
the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with
the output of the program.*/


#include <stdio.h>
#include <stdlib.h>
void enqueue(int **queue, int *size, int *capacity, int *rear, int element)
{
    if (*size == *capacity)
    {
        *capacity *= 2;
        *queue = (int *)realloc(*queue, *capacity * sizeof(int));
    }
    *rear = (*rear + 1) % *capacity;
    (*queue)[*rear] = element;
    (*size)++;
}
int dequeue(int *queue, int *size, int *capacity, int *front, int *rear)
{
    if (*size == 0)
    {
        return -1;
    }
    int element = queue[*front];
    *front = (*front + 1) % *capacity;
    (*size)--;
    return element;
}
int main()
{
    int processes = 5;
    int time_q = 2;
    int arrivalTime[] = {0, 1, 2, 3, 4};
    int burstTime[] = {5, 3, 1, 2, 3};
    int remainingTime[] = {5, 3, 1, 2, 3};
    int completionTime[] = {-1, -1, -1, -1, -1};
    int TAT[processes], WT[processes];
    float totalTat = 0, totalWt = 0;
    int currentTime = 0;
    int completed = 0;
    // Ready queue
    int *queue = (int *)malloc(processes * sizeof(int));
    int queueSize = 0, queueCapacity = processes, front = 0, rear = -1;
    for (int i = 0; i < processes; i++)
    {
        if (arrivalTime[i] == 0)
        {
            enqueue(&queue, &queueSize, &queueCapacity, &rear, i);
        }
    }
    while (completed < processes)
    {
        if (queueSize == 0)
        {
            currentTime++;
            for (int i = 0; i < processes; i++)
            {
                if (arrivalTime[i] == currentTime)
                {
                    enqueue(&queue, &queueSize, &queueCapacity, &rear, i);
                }
            }
            continue;
        }
        int currentProcess = dequeue(queue, &queueSize, &queueCapacity, &front, &rear);
        if (remainingTime[currentProcess] > time_q)
        {
            remainingTime[currentProcess] -= time_q;
            currentTime += time_q;
        }
        else
        {
            currentTime += remainingTime[currentProcess];
            remainingTime[currentProcess] = 0;
            completionTime[currentProcess] = currentTime;
            TAT[currentProcess] = completionTime[currentProcess] - arrivalTime[currentProcess];
            WT[currentProcess] = TAT[currentProcess] - burstTime[currentProcess];
            totalTat += TAT[currentProcess];
            totalWt += WT[currentProcess];
            completed++;
        }
        for (int i = 0; i < processes; i++)
        {
            if (arrivalTime[i] > currentTime - time_q && arrivalTime[i] <= currentTime &&
                remainingTime[i] > 0)
            {
                int found = 0;
                for (int j = 0; j < queueSize; j++)
                {
                    if (queue[(front + j) % queueCapacity] == i)
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    enqueue(&queue, &queueSize, &queueCapacity, &rear, i);
                }
            }
        }
        if (remainingTime[currentProcess] > 0)
        {
            enqueue(&queue, &queueSize, &queueCapacity, &rear, currentProcess);
        }
    }
printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaitingTime\n");
for (int i = 0; i < processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, arrivalTime[i], burstTime[i],
               completionTime[i], TAT[i], WT[i]);
}
printf("Average Turnaround Time: %.2f\n", totalTat / processes);
printf("Average Waiting Time: %.2f\n", totalWt / processes);
free(queue);
return 0;
}