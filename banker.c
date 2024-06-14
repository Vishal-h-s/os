#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 4

bool isSafeState(int processes, int resources, int available[], int allocation[][R], int need[][R], int safeSequence[])
{
    int work[R];
    bool finish[processes]; // Dynamic size

    for (int i = 0; i < resources; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++)
    {
        finish[i] = false;
    }

    int count = 0;
    while (count < processes)
    {
        bool found = false;
        for (int p = 0; p < processes; p++)
        {
            if (!finish[p])
            {
                bool canAllocate = true;
                for (int j = 0; j < resources; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int k = 0; k < resources; k++)
                    {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

bool canGrantRequest(int processes, int resources, int available[], int allocation[][R], int need[][R], int request[], int safeSequence[])
{
    // Validate request
    for (int i = 0; i < resources; i++)
    {
        if (request[i] > available[i])
        {
            return false;
        }
    }

    // Temporarily allocate resources to the new process
    int newAllocation[processes][R];
    int newNeed[processes][R];
    int newAvailable[R];

    // Copy existing allocations and needs
    for (int i = 0; i < processes - 1; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            newAllocation[i][j] = allocation[i][j];
            newNeed[i][j] = need[i][j];
        }
    }

    // Add the new process' request to allocation and calculate its new need
    for (int j = 0; j < resources; j++)
    {
        newAllocation[processes - 1][j] = request[j];
        newNeed[processes - 1][j] = 0;
        newAvailable[j] = available[j] - request[j];
    }

    // Check if the system is in a safe state with the new process
    bool safe = isSafeState(processes, resources, newAvailable, newAllocation, newNeed, safeSequence);

    return safe;
}

int main()
{
    int processes = P + 1; // Including the new process
    int resources = R;

    // Hard-coded Allocation Matrix
    int allocation[P][R] = {
        {2, 0, 0, 1},
        {3, 1, 2, 1},
        {2, 1, 0, 3},
        {1, 3, 1, 2},
        {1, 4, 3, 2}};

    // Hard-coded Maximum Matrix
    int max[P][R] = {
        {4, 2, 1, 2},
        {5, 2, 5, 2},
        {2, 3, 1, 6},
        {1, 4, 2, 4},
        {3, 6, 6, 5}};

    // Hard-coded Available Resources
    int available[R] = {3, 3, 2, 1};

    // Calculate Need Matrix
    int need[P][R];
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int safeSequence[processes];

    // Check if system is in a safe state
    if (isSafeState(P, resources, available, allocation, need, safeSequence))
    {
        printf("System is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < P; i++)
        {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is not in a safe state.\n");
    }

    // Hard-coded request from a new process
    int newRequest[R] = {1, 1, 0, 0}; // Request for resources

    if (canGrantRequest(processes, resources, available, allocation, need, newRequest, safeSequence))
    {
        printf("New process request can be granted. System is in a safe state after granting the request.\n");
        printf("Safe sequence after granting the new request is: ");
        for (int i = 0; i < processes; i++)
        {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("New process request cannot be granted. System would not be in a safe state.\n");
    }

    return 0;
}
