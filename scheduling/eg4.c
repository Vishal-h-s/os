/* 4. Airlines categorize passengers into different groups based on various criteria such
as frequent flyer status, class of service, special needs, and more. Each group is
assigned a priority level, and within that priority, boarding is handled in the order that
passengers arrive at the gate
•
Priority Assignment:
1.
First Priority: First-class passengers, high-tier frequent flyers, and passengers
requiring special assistance (e.g., wheelchair users).Arrival time: 3 and assistance time:
5min
2.
Second Priority: Business class and mid-tier frequent flyers. Arrival time: 0 and
assistance time: 10min
3.
Third Priority: Premium economy passengers. Arrival time: 4 and assistance time:
7min
4.
Fourth Priority: Economy class passengers. Arrival time: 1 and assistance time:
8min
5.
Final Priority: Basic economy or last-minute ticket purchasers, Arrival time: 5 and
assistance time: 6min
*/ 


#include<stdio.h>
int main()
{
    int processes = 5;
    int processNames[] = {1, 2, 3, 4, 5};
    int arrivalTime[] = {3, 0, 4, 1, 5};
    int burstTime[] = {5, 10, 7, 8, 6};
    int remainingTime[] = {5, 10, 7, 8, 6};
    int priority[] = {1, 2, 3, 4, 5};
    int TAT[processes], WT[processes], completionTime[processes];
    float totalTat = 0, totalWt = 0;
    int currentTime = 0;
    for (int i = 0; i < processes; i++)
    {
        int highestPriority = 20;
        int highestPrIndex = -1;
        for (int j = 0; j < processes; j++)
        {
            if (arrivalTime[j] <= currentTime && remainingTime[j] > 0 && priority[j] < highestPriority)
            {
                highestPriority = priority[j];
                highestPrIndex = j;
            }
        }
        if (highestPrIndex == -1)
        {
            currentTime++;
            i--;
            continue;
        }
        while (remainingTime[highestPrIndex] > 0)
        {
            remainingTime[highestPrIndex]--;
            currentTime++;
        }
        completionTime[highestPrIndex] = currentTime;
        TAT[highestPrIndex] = completionTime[highestPrIndex] - arrivalTime[highestPrIndex];
        WT[highestPrIndex] = TAT[highestPrIndex] - burstTime[highestPrIndex];
        totalTat += TAT[highestPrIndex];
        totalWt += WT[highestPrIndex];
    }printf("Process\tPriority\tBurst Time\tArrival Time\tCompletion Time\tTurnaroundTime\tWaiting Time\n");
for(int i = 0;i<processes;i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processNames[i], priority[i], burstTime[i], arrivalTime[i], completionTime[i], TAT[i], WT[i]);
}
printf("Average Turn Around Time : %.2f\n",totalTat/processes);
printf("Average Waiting Time : %.2f\n",totalWt/processes);
return 0;
}