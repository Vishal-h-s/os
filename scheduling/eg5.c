/* 5. An IT help desk in a large corporation handles a range of technical issues and
requests from employees. Given the varied nature and urgency of these issues, which
scheduling system is employed to ensure that critical IT support requests are handled
promptly, while less urgent issues are addressed in an orderly fashion. IT staff can
switch between tasks based on real-time reevaluation of priorities as new tickets arrive.
Considering this as the inputs: Calculate Average Turn Around time and Average Waiting
time
Process Id Priority
Arrival Time Burst Time
1
2(L)
0
1
2
6
1
7
3
3
2
3
4
5
3
6
5
4
4
5
6
10(H)
5
15
7
9
15
8 



//Identify the type of CPU scheduling algorithm for the scenario and implement the same
in C Language. Calculate Average Turn Around time and Average Waiting time for each of
the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with
the output of the program.*/

#include <stdio.h>
int main()
{
    int processes = 7;
    int processNames[] = {1, 2, 3, 4, 5, 6, 7};
    int priority[] = {2, 6, 3, 5, 4, 10, 9};
    int arrivalTime[] = {0, 1, 2, 3, 4, 5, 15};
    int burstTime[] = {1, 7, 3, 6, 5, 15, 8};
    int remainingBurst[] = {1, 7, 3, 6, 5, 15, 8};
    int completionTime[processes], TAT[processes], WT[processes];
    float totalTat = 0, totalWt = 0;
    int currentTime = 0;
    int completed = 0;
    while (completed < processes)
    {
        int highestPriority = -1;
        int highestPrIndex = -1;
        for (int i = 0; i < processes; i++)
        {
            if (arrivalTime[i] <= currentTime && remainingBurst[i] > 0 && priority[i] > highestPriority)
            {
                highestPriority = priority[i];
                highestPrIndex = i;
            }
        }
        if (highestPrIndex == -1)
        {
            currentTime++;
            continue;
        }
        remainingBurst[highestPrIndex]--;
        currentTime++;
        if (remainingBurst[highestPrIndex] == 0)
        {
            completionTime[highestPrIndex] = currentTime;
            TAT[highestPrIndex] = completionTime[highestPrIndex] - arrivalTime[highestPrIndex];
            WT[highestPrIndex] = TAT[highestPrIndex] - burstTime[highestPrIndex];
            totalTat += TAT[highestPrIndex];
            totalWt += WT[highestPrIndex];
            completed++;
        }
    }
printf("Process\tPriority\tBurst Time\tArrival Time\tCompletion Time\tTurnaroundTime\tWaiting Time\n");
for(int i = 0;i<processes;i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processNames[i], priority[i], burstTime[i], arrivalTime[i], completionTime[i], TAT[i], WT[i]);
}
printf("Average Turn Around Time : %.2f\n",totalTat/processes);printf("Average Waiting Time : %.2f\n",totalWt/processes);
return 0;
}